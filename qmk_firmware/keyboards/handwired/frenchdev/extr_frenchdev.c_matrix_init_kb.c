#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int DDRD ; 
 int DDRE ; 
 int PORTD ; 
 int PORTE ; 
 int TCCR1A ; 
 int TCCR1B ; 
 int /*<<< orphan*/  frenchdev_blink_all_leds () ; 
 int /*<<< orphan*/  matrix_init_user () ; 

void matrix_init_kb(void) {
   // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM



    // unused pins - D4, D5, D7, E6
    // set as input with internal pull-ip enabled
    DDRD  &= ~(1<<5 | 1<<4);
    DDRE  &= ~(1<<6);
    PORTD |=  (1<<5 | 1<<4);
    PORTE |=  (1<<6);

    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();
    frenchdev_blink_all_leds();

    matrix_init_user();
}