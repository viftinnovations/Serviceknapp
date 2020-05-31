int knapp = 12; //Port til knapp for lys
int reset = 4; // Port til reset knapp
int lysKunde = 11; //Port til lys
int lysAnsatt = 13; //Port til de ansatte sitt lys
int buzzer = 7; // port til piezo (lyd)
int variabel = LOW; //variabel som brukes til piezo-komponentet
unsigned long tidVentet; //variabel for tid ventet

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Start serial
  pinMode(lysKunde, OUTPUT);
  pinMode(knapp, INPUT);
  pinMode(reset, INPUT);
  digitalWrite(lysKunde, LOW);
  pinMode(lysAnsatt, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  int tidSomSkalHaGaatt = 180000;
  // put your main code here, to run repeatedly:
  int tilstandKnapp = digitalRead(knapp);
  int tilstandReset = digitalRead(reset);
  // Sjekk om knappen trykkes paa
  if (tilstandKnapp == HIGH) {
    endreLysPaa();
  }
  int variabelLys = millis();
  if ((millis() - variabelLys) >= tidSomSkalHaGaatt) {
        //endreLysAv();
        digitalWrite(lysKunde, LOW);
        digitalWrite(lysAnsatt, LOW);
        Serial.println("tid ferdig");
    } 
  if (tilstandReset == HIGH) {
      endreLysReset();
      Serial.println("LYS RESET");
  }
}


/*Lyset paa kundens ting skal skru seg paa nar deres knapp (port 12)
trykkes paa. Da skal piezoen pipe i et antall sekunder. Lyset skal 
bli staaende paa selv om den slutter aa pipe.*/
void endreLysPaa() {
  int tilstandReset = digitalRead(reset);
  digitalWrite(lysKunde, HIGH);
  digitalWrite(lysAnsatt, HIGH);
  variabel = HIGH;
  Serial.println("LYS PAA +++");
  femSekunder();
}  


/*Naar reset knappen trykkes paa skal lys paa begge tingene
skru seg av, og eventuelt piezoen ogsaa.*/
void endreLysReset() {
  digitalWrite(lysKunde, LOW);
  digitalWrite(lysAnsatt, LOW);
  //Serial.println("LYS RESET");
}

/*Dersom ingen ansatt kommer for aa hjelpe og reset-knappen
ikke blir trykket paa, vil den begge lysene automatisk skru
seg av etter tre minutter.*/
void endreLysAv() {
  digitalWrite(lysKunde, LOW);
  digitalWrite(lysAnsatt, LOW);
  Serial.println("LYS AV ---");
}

/*Koden for lyd paa piezoen, flettes inn med endreLysPaa().*/
void lyd() {
   noTone(buzzer);
   tone(buzzer, 500);
   delay(500);
   noTone(buzzer);
   delay(500);
}

/*Metoden skrur piezo-komponentet av. Kjores i sammenheng
med at reset-knappen trykkes paa.*/
void lydAv() {
  noTone(buzzer);
  Serial.println("LYD AV");
}

/*Metoden kjorer for-loopen som skrur paa piezo-komponentet
og sjekker samtidig om reset-knappen trykkes. Kjores i 
sammenheng med endreLysPaa().*/
void femSekunder() {
  for (int x=0; x<5; x++) {
      int tilstandReset = digitalRead(reset);
      if (tilstandReset == LOW) {
        lyd();
        Serial.println(x); 
      }
      else if (tilstandReset == HIGH) {
        digitalWrite(lysKunde, LOW);
        digitalWrite(lysAnsatt, LOW);
        Serial.println("LYS RESET2");
        lydAv();   
    }
  }
}
