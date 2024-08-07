// This optional setting causes Encoder to use more optimized code,
// It must be defined before Encoder.h is included.
//#define ENCODER_OPTIMIZE_INTERRUPTS
//#include <Encoder.h>
#include "EncoderTool.h"
//#include <Bounce.h>


#define BassBoost 14
#define CS_HC595 36
#define PWM1     28
#define PWM2     29
#define PWM3     19
#define PWM4     18
#define PWM5     25
#define ENCODER_PINA 5
#define ENCODER_PINB 4
#define PAGE_SW 17
#define QUANTISE_FACTOR 32	// 16 Sets a tolerance of noise on the ADC
#define Prev_Factor 4		// 4
#define DEBOUNCE 30

// static byte muxInput = 0;
static int16_t mux1ValuesPrev = 0;
static int16_t mux2ValuesPrev = 0;
static int16_t mux3ValuesPrev = 0;
static int16_t mux4ValuesPrev = 0;
//static int16_t mux5ValuesPrev = 0;
// static int mux6ValuesPrev = 0;
// static int muxVCFValuesPrev = 0;
// static int volumeRead = 0;
// static int volumePrevious = 0;
static int32_t encPrevMenuNo = 0;
static int32_t encPrevPatchNo = 0;

//Encoder encoder(ENCODER_PINB, ENCODER_PINA);//This often needs the pins swapping depending on the encoder
using namespace EncoderTool;
PolledEncoder encoder;



FLASHMEM void setupHardware() {
  //Switches
  pinMode(PAGE_SW, INPUT_PULLUP);
  //LEDs
  pinMode(CS_HC595, OUTPUT);
  //Switches  
  pinMode(BassBoost, OUTPUT);
  digitalWrite(BassBoost,HIGH);  // Boost off
  // PWM Fx
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(PWM3, OUTPUT);
  pinMode(PWM4, OUTPUT);
  pinMode(PWM5, OUTPUT);
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
  analogWrite(PWM3, 0);
  analogWrite(PWM4, 0); // Fx out mute
  analogWrite(PWM5, 0);
}


