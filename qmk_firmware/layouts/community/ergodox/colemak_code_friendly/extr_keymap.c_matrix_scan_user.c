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
 scalar_t__ LAYER_NUM ; 
 scalar_t__ biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int /*<<< orphan*/  layer_state ; 
 scalar_t__ recording_dynamic_macro ; 

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  //led 1, RED, Caps-Lock ON
  //if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ergodox_right_led_1_on();

  //led 2, GREEN
  if (layer == LAYER_NUM) 
      ergodox_right_led_2_on();
  else
      ergodox_right_led_2_off();

  //led 3, BLUE
  if (recording_dynamic_macro) 
      ergodox_right_led_3_on();
  else
      ergodox_right_led_3_off();
}