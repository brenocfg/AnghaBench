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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ rgb_matrix_enable; scalar_t__ led_level; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 int DDRB ; 
 int DDRC ; 
 int DDRD ; 
 int DDRE ; 
 int /*<<< orphan*/  LED_FLAG_ALL ; 
 int /*<<< orphan*/  LED_FLAG_NONE ; 
 int PORTB ; 
 int PORTC ; 
 int PORTD ; 
 int PORTE ; 
 int TCCR1A ; 
 int TCCR1B ; 
 int /*<<< orphan*/  eeconfig_read_kb () ; 
 int /*<<< orphan*/  ergodox_blink_all_leds () ; 
 int /*<<< orphan*/  ergodox_led_all_set (int) ; 
 TYPE_1__ keyboard_config ; 
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  rgb_matrix_set_flags (int /*<<< orphan*/ ) ; 

void matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    // (tied to Vcc for hardware convenience)
    DDRB  &= ~(1<<4);  // set B(4) as input
    PORTB &= ~(1<<4);  // set B(4) internal pull-up disabled

    // unused pins - C7, D4, D5, D7, E6
    // set as input with internal pull-up enabled
    DDRC  &= ~(1<<7);
    DDRD  &= ~(1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTC |=  (1<<7);
    PORTD |=  (1<<5 | 1<<4);
    PORTE |=  (1<<6);

    keyboard_config.raw = eeconfig_read_kb();
    ergodox_led_all_set((uint8_t)keyboard_config.led_level * 255 / 4 );
#ifdef RGB_MATRIX_ENABLE
    if (keyboard_config.rgb_matrix_enable) {
        rgb_matrix_set_flags(LED_FLAG_ALL);
    } else {
        rgb_matrix_set_flags(LED_FLAG_NONE);
    }
#endif

    ergodox_blink_all_leds();

    matrix_init_user();
}