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
 int DDRB ; 
 int DDRD ; 
 int PORTB ; 
 int PORTD ; 
 int /*<<< orphan*/  breathing_disable () ; 
 int /*<<< orphan*/  matrix_init_keymap () ; 

void matrix_init_user(void) {
//turn off pro micro LEDs
#if defined(KEYBOARD_lets_split_rev2)
  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
#endif

//disable backlight breathing for keyboard using random flashing RGB LEDs for backlight
//(breathing provides insufficient power to integrated LED IC)
#if defined(KEYBOARD_kbdfans_kbd6x) && defined(BACKLIGHT_BREATHING)
  breathing_disable();
#endif
  matrix_init_keymap();
}