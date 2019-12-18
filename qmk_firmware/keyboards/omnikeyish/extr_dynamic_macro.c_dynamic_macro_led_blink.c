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
 int /*<<< orphan*/  backlight_toggle () ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  led_set (int) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void dynamic_macro_led_blink(void) {
#ifdef BACKLIGHT_ENABLE
  backlight_toggle();
  wait_ms(100);
  backlight_toggle();
#else
  led_set(host_keyboard_leds() ^ 0xFF);
  wait_ms(100);
  led_set(host_keyboard_leds());
#endif
}