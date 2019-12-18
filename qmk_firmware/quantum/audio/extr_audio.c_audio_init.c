#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_2__ {scalar_t__ enable; int /*<<< orphan*/  raw; } ;
typedef  int INIT_AUDIO_COUNTER_3 ;
typedef  int INIT_AUDIO_COUNTER_1 ;
typedef  int /*<<< orphan*/  CPIN_SET_DIRECTION ;
typedef  int /*<<< orphan*/  BPIN_SET_DIRECTION ;

/* Variables and functions */
 int CPU_PRESCALER ; 
 int CS10 ; 
 int CS11 ; 
 int CS12 ; 
 int CS30 ; 
 int CS31 ; 
 int CS32 ; 
 scalar_t__ F_CPU ; 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 void* TIMER_1_DUTY_CYCLE ; 
 void* TIMER_1_PERIOD ; 
 void* TIMER_3_DUTY_CYCLE ; 
 void* TIMER_3_PERIOD ; 
 int WGM12 ; 
 int WGM13 ; 
 int WGM32 ; 
 int WGM33 ; 
 TYPE_1__ audio_config ; 
 int audio_initialized ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_audio () ; 
 float note_timbre ; 
 int /*<<< orphan*/  startup_song ; 

void audio_init() {
    // Check EEPROM
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }
    audio_config.raw = eeconfig_read_audio();

    if (!audio_initialized) {
// Set audio ports as output
#ifdef CPIN_AUDIO
        CPIN_SET_DIRECTION
        DISABLE_AUDIO_COUNTER_3_ISR;
#endif
#ifdef BPIN_AUDIO
        BPIN_SET_DIRECTION
        DISABLE_AUDIO_COUNTER_1_ISR;
#endif

// TCCR3A / TCCR3B: Timer/Counter #3 Control Registers TCCR3A/TCCR3B, TCCR1A/TCCR1B
// Compare Output Mode (COM3An and COM1An) = 0b00 = Normal port operation
//   OC3A -- PC6
//   OC3B -- PC5
//   OC3C -- PC4
//   OC1A -- PB5
//   OC1B -- PB6
//   OC1C -- PB7

// Waveform Generation Mode (WGM3n) = 0b1110 = Fast PWM Mode 14. Period = ICR3, Duty Cycle OCR3A)
//   OCR3A - PC6
//   OCR3B - PC5
//   OCR3C - PC4
//   OCR1A - PB5
//   OCR1B - PB6
//   OCR1C - PB7

// Clock Select (CS3n) = 0b010 = Clock / 8
#ifdef CPIN_AUDIO
        INIT_AUDIO_COUNTER_3
        TCCR3B             = (1 << WGM33) | (1 << WGM32) | (0 << CS32) | (1 << CS31) | (0 << CS30);
        TIMER_3_PERIOD     = (uint16_t)(((float)F_CPU) / (440 * CPU_PRESCALER));
        TIMER_3_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (440 * CPU_PRESCALER)) * note_timbre);
#endif
#ifdef BPIN_AUDIO
        INIT_AUDIO_COUNTER_1
        TCCR1B             = (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (0 << CS10);
        TIMER_1_PERIOD     = (uint16_t)(((float)F_CPU) / (440 * CPU_PRESCALER));
        TIMER_1_DUTY_CYCLE = (uint16_t)((((float)F_CPU) / (440 * CPU_PRESCALER)) * note_timbre);
#endif

        audio_initialized = true;
    }

    if (audio_config.enable) {
        PLAY_SONG(startup_song);
    }
}