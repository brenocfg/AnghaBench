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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_ALPHAS ; 
 int /*<<< orphan*/  BACKLIGHT_FKEYS ; 
 int /*<<< orphan*/  BACKLIGHT_MODNUM ; 
 int /*<<< orphan*/  BACKLIGHT_NUMPAD ; 
 int /*<<< orphan*/  PORTB ; 
 int /*<<< orphan*/  PORTE ; 

void backlight_set(uint8_t level) {
  if (level > 0) {
    // Turn on leds
    PORTB &= ~BACKLIGHT_ALPHAS;
    PORTB &= ~BACKLIGHT_FKEYS;
    PORTB &= ~BACKLIGHT_MODNUM;
    PORTE &= ~BACKLIGHT_NUMPAD;
  } else {
    // Turn off leds
    PORTB |= BACKLIGHT_ALPHAS;
    PORTB |= BACKLIGHT_FKEYS;
    PORTB |= BACKLIGHT_MODNUM;
    PORTE |= BACKLIGHT_NUMPAD;
  }
}