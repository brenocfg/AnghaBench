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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  C4 ; 
 int /*<<< orphan*/  C5 ; 
 int /*<<< orphan*/  C6 ; 
 scalar_t__ IS_LED_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  USB_LED_NUM_LOCK ; 
 int /*<<< orphan*/  USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_OFF(usb_led, USB_LED_NUM_LOCK)) {
        writePinLow(C4);
    } else {
        writePinHigh(C4);
    }
    if (IS_LED_OFF(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(C5);
    } else {
        writePinHigh(C5);
    }
    if (IS_LED_OFF(usb_led, USB_LED_SCROLL_LOCK)) {
        writePinLow(C6);
    } else {
        writePinHigh(C6);
    }
}