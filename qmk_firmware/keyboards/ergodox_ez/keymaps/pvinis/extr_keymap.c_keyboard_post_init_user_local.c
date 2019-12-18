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
 int LED_BRIGHTNESS_HI ; 
 int LED_BRIGHTNESS_LO ; 
 int /*<<< orphan*/  ergodox_led_all_off () ; 
 int /*<<< orphan*/  ergodox_led_all_on () ; 
 int /*<<< orphan*/  ergodox_led_all_set (int) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void keyboard_post_init_user_local(void) {
  ergodox_led_all_on();
  for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--) {
    ergodox_led_all_set(i);
    wait_ms(5);
  }
  wait_ms(1000);
  for (int i = LED_BRIGHTNESS_LO; i > 0; i--) {
    ergodox_led_all_set(i);
    wait_ms(10);
  }
  ergodox_led_all_off();

  // restore default brightness for future use
  ergodox_led_all_set(LED_BRIGHTNESS_HI);
}