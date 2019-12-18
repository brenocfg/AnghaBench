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
 int /*<<< orphan*/  rgblight_effect_knight (int) ; 
 int /*<<< orphan*/  rgblight_enable () ; 
 int /*<<< orphan*/  rgblight_init () ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void matrix_init_user(void)
{

  ergodox_led_all_on();
  rgblight_init();
  rgblight_enable();
  rgblight_setrgb(255, 0, 0);
  for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--)
  {
    ergodox_led_all_set(i);
    wait_ms(5);
  }
  rgblight_setrgb(255, 255, 0);
  wait_ms(1000);
  for (int i = LED_BRIGHTNESS_LO; i > 0; i--)
  {
    ergodox_led_all_set(i);
    wait_ms(10);
  }
  rgblight_setrgb(0, 255, 255);
  ergodox_led_all_off();
  wait_ms(1000);

  rgblight_effect_knight(50);
}