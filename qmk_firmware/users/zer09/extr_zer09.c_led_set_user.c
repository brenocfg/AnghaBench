#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {void* status; } ;

/* Variables and functions */
 void* DISABLED ; 
 void* ENABLED ; 
 size_t RBW_LCAP ; 
 size_t RBW_RCAP ; 
 size_t RBW_SCRL ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  led_set_keymap (int) ; 
 TYPE_1__* rbw_led_keys ; 

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    rbw_led_keys[RBW_LCAP].status = ENABLED;
    rbw_led_keys[RBW_RCAP].status = ENABLED;
  } else {
    rbw_led_keys[RBW_LCAP].status = DISABLED;
    rbw_led_keys[RBW_RCAP].status = DISABLED;
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    rbw_led_keys[RBW_SCRL].status = ENABLED;
  } else {
    rbw_led_keys[RBW_SCRL].status = DISABLED;
  }

  led_set_keymap(usb_led);
}