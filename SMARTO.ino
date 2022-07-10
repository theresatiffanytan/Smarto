#include <WiFi.h>                                                
#include <IOXhop_FirebaseESP32.h>      

#define ROW_NUM     4  // four rows
#define COLUMN_NUM  4  // four columns

#define RELAY_PIN   21 // ESP32 pin GIOP32 connected to relay's  pin
#define  TOUCH_SENSOR_PIN  23 // ESP32 pin GIOP34 connected to touch sensor's pin
#define led_1  18

#define RELAY_PIN2        19 // ESP32 pin GIOP33 connected to relay's 2 pin
#define  TOUCH_SENSOR2_PIN  22// ESP32 pin GIOP35 connected to touch sensor's 2 pin
#define led_2  5

#define FIREBASE_Host "https://smarto-project-default-rtdb.asia-southeast1.firebasedatabase.app/"  // replace with your Firebase Host
#define FIREBASE_authorization_key "CQ8qIttXIf1dN57U98xp5CNY0WCa0qbIO9ltnLKm" // replace with your secret key
#define Your_SSID "wifi.id"       // replace with your SSID
#define Your_PASSWORD "50ribu1jam"          //replace with your Password


String door1_state = ""; // pintu 1
String door2_state = "";  // pintu 2

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(RELAY_PIN, OUTPUT);  // set ESP32 pin to output mode
  pinMode(TOUCH_SENSOR_PIN, INPUT); // set ESP32 pin to input mode
  pinMode (led_1, OUTPUT);
  
  pinMode(RELAY_PIN2, OUTPUT);       // set ESP32 pin to output mode
  pinMode(TOUCH_SENSOR2_PIN, INPUT); // set ESP32 pin to input mode
  pinMode (led_2, OUTPUT);

  WiFi.begin(Your_SSID, Your_PASSWORD);                                      
  Serial.print("Connecting to WIFI");
  while (WiFi.status() != WL_CONNECTED){ 
  Serial.print(".");
  delay(500);
  }
  Serial.println();
  Serial.print("Connected to WIFI!");
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); //print local IP address
  Firebase.begin(FIREBASE_Host, FIREBASE_authorization_key);  // connect to firebase
  
}

void loop() {
  int touchState = digitalRead(TOUCH_SENSOR_PIN); // read new state
  int touchState_2 = digitalRead(TOUCH_SENSOR2_PIN); // read new state

  door1_state =  Firebase.getString("/room/1/Door"); 
  door2_state =  Firebase.getString("/room/2/Door");
  Serial.println(door1_state);
  Serial.println(door2_state);
  
  if (door1_state == "1")  {
    Serial.println("pintu kamar 1 terbuka dari luar");
    digitalWrite(RELAY_PIN, HIGH);  // unlock the door for 20 seconds
    digitalWrite(led_1, HIGH);
  }
  else if (door1_state == "0"){
    digitalWrite(RELAY_PIN, LOW); // lock the door
    digitalWrite(led_1, LOW);
     }

     
  if (door2_state == "1")  {
     Serial.println("pintu kamar 2 terbuka dari luar");
     digitalWrite(RELAY_PIN2, HIGH);  // unlock the door for 20 seconds
     digitalWrite(led_2, HIGH);
  }
  else if (door2_state == "0"){
     digitalWrite(RELAY_PIN2, LOW); // lock the door
     digitalWrite(led_2, LOW);
      } 

      
  if (touchState == HIGH) {
    Serial.println("pintu kamar 1 terbuka dari dalam");
    digitalWrite(RELAY_PIN, HIGH); // turn on
    digitalWrite(led_1, HIGH);
    delay(10000);
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(led_1, LOW);
    }
  else if (touchState_2 == HIGH) {
    Serial.println("pintu kamar 2 terbuka dari dalam");
    digitalWrite(RELAY_PIN2, HIGH); // turn on
    digitalWrite(led_2, HIGH);
    delay(10000);
    digitalWrite(RELAY_PIN2, LOW);
    digitalWrite(led_2, LOW);
    }
}
