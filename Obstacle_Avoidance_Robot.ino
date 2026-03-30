 #include <Servo.h>
#include <NewPing.h>

// Motor driver pins
#define IN1 6
#define IN2 7
#define IN3 5
#define IN4 4

#define ENA 10
#define ENB 11

// Ultrasonic pins
#define TRIG A1
#define ECHO A2
#define MAX_DISTANCE 200

Servo servo_motor;
NewPing sonar(TRIG, ECHO, MAX_DISTANCE);

int distance = 100;
boolean goesForward = false;

void setup() {

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Motor speed
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  servo_motor.attach(9);
  servo_motor.write(90);

  delay(2000);

  distance = readPing();
}

void loop() {

  int distanceRight;
  int distanceLeft;

  delay(50);

  if (distance <= 20) {

    moveStop();
    delay(300);

    moveBackward();
    delay(400);

    moveStop();
    delay(300);

    distanceRight = lookRight();
    delay(300);

    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft) {
      turnRight();
    }
    else {
      turnLeft();
    }

  }
  else {
    moveForward();
  }

  distance = readPing();
}

int lookRight() {

  servo_motor.write(30);
  delay(500);

  int distance = readPing();

  delay(100);

  servo_motor.write(90);

  return distance;
}

int lookLeft() {

  servo_motor.write(150);
  delay(500);

  int distance = readPing();

  delay(100);

  servo_motor.write(90);

  return distance;
}

int readPing() {

  delay(70);

  int cm = sonar.ping_cm();

  if (cm == 0) {
    cm = 250;
  }

  return cm;
}

void moveStop() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveForward() {

  if (!goesForward) {

    goesForward = true;

    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);

    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
  }
}

void moveBackward() {

  goesForward = false;

  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);
}

void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH);

  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);

  delay(500);

  moveStop();
}

void turnLeft() {

  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);

  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);

  delay(500);

  moveStop();
}