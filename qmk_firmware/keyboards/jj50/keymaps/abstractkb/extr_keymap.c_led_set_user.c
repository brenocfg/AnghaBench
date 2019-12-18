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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  RGBLIGHT_MODE_ALTERNATING ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  layer_state_set_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int /*<<< orphan*/ ) ; 

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    rgblight_mode_noeeprom(RGBLIGHT_MODE_ALTERNATING);
  } else {
    layer_state_set_user(layer_state);
  }
}