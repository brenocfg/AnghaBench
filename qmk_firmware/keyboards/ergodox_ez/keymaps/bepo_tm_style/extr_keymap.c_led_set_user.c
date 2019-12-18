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
 scalar_t__ LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSLEDS ; 
 int /*<<< orphan*/  led_1_off () ; 
 int /*<<< orphan*/  led_1_on () ; 
 int /*<<< orphan*/  led_2_off () ; 
 int /*<<< orphan*/  led_2_on () ; 
 int /*<<< orphan*/  led_3_off () ; 
 int /*<<< orphan*/  led_3_on () ; 
 int sys_led_mask_caps_lock ; 
 int sys_led_mask_num_lock ; 
 int sys_led_mask_scroll_lock ; 
 int sys_led_state ; 

void led_set_user(uint8_t usb_led) {
  sys_led_state = usb_led;
  if (LAYER_ON(SYSLEDS)) {
    if (sys_led_state & sys_led_mask_caps_lock) {
      led_1_on();
    } else {
      led_1_off();
    }
    if (sys_led_state & sys_led_mask_num_lock) {
      led_2_on();
    } else {
      led_2_off();
    }
    if (sys_led_state & sys_led_mask_scroll_lock) {
      led_3_on();
    } else {
      led_3_off();
    }
  }
}