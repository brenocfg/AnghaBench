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
 int /*<<< orphan*/  host_keyboard_leds () ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  layer_state_set_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_set_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_disable_noeeprom () ; 
 int /*<<< orphan*/  rgblight_enable_noeeprom () ; 
 int rgbon ; 

void myrgb_toggle(void) {
  if (rgbon) {
    rgblight_disable_noeeprom();
    rgbon = false;
  } else {
    rgblight_enable_noeeprom();
    layer_state_set_user(layer_state);
    led_set_user(host_keyboard_leds());
    rgbon = true;
  }
}