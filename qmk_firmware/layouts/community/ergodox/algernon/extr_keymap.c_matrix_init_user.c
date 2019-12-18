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
typedef  unsigned long uint8_t ;

/* Variables and functions */
 unsigned long ADORE ; 
 int LED_BRIGHTNESS_HI ; 
 int LED_BRIGHTNESS_LO ; 
 int /*<<< orphan*/  UC_LNX ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 unsigned long eeconfig_read_default_layer () ; 
 int /*<<< orphan*/  ergodox_led_all_off () ; 
 int /*<<< orphan*/  ergodox_led_all_on () ; 
 int /*<<< orphan*/  ergodox_led_all_set (int) ; 
 int is_adore ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void matrix_init_user(void) {
  uint8_t dl;

  set_unicode_input_mode(UC_LNX);

  ergodox_led_all_on();
  for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--) {
    ergodox_led_all_set (i);
    wait_ms (5);
  }
  wait_ms(1000);
  for (int i = LED_BRIGHTNESS_LO; i > 0; i--) {
    ergodox_led_all_set (i);
    wait_ms (10);
  }
  ergodox_led_all_off();

  if (!eeconfig_is_enabled())
    eeconfig_init();
  dl = eeconfig_read_default_layer ();
  if (dl == (1UL << ADORE)) {
    is_adore = 1;
  }
}