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
 int DDRE ; 
 int DDRF ; 
 int LED_CAPS_LOCK ; 
 int LED_FN ; 
 int LED_MOUSE_LOCK ; 
 int LED_NAS ; 
 int LED_NUM_LOCK ; 
 int LED_SCROLL_LOCK ; 
 int LED_TENKEY ; 
 int PORTB ; 
 int PORTF ; 
 int /*<<< orphan*/  matrix_init_user () ; 

void matrix_init(void) {
  /* See datahand.h for more detail on pins. */

  /* 7 - matrix scan; 6-3 - mode LEDs */
  DDRB = 0b11111000;

  /* 1-0 - matrix scan */
  DDRD = 0b00000011;

  /* 6 - matrix scan */
  DDRE = 0b01000000;

  /* 7-4 - lock LEDs */
  DDRF = 0b11110000;

  /* Turn off the non-Normal LEDs (they're active low). */
  PORTB |= LED_TENKEY | LED_FN | LED_NAS;

  /* Turn off the lock LEDs. */
  PORTF |= LED_CAPS_LOCK | LED_NUM_LOCK | LED_SCROLL_LOCK | LED_MOUSE_LOCK;

  matrix_init_user();
}