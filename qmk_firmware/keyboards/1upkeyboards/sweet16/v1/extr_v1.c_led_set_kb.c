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
 int /*<<< orphan*/  B0 ; 
 int /*<<< orphan*/  D5 ; 
 scalar_t__ IS_LED_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  USB_LED_NUM_LOCK ; 
 int /*<<< orphan*/  setPinInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void led_set_kb(uint8_t usb_led) {
#ifndef CONVERT_TO_PROTON_C
    /* Map RXLED to USB_LED_NUM_LOCK */
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        setPinOutput(B0);
        writePinLow(B0);
    } else {
        setPinInput(B0);
    }

    /* Map TXLED to USB_LED_CAPS_LOCK */
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        setPinOutput(D5);
        writePinLow(D5);
    } else {
        setPinInput(D5);
    }
#endif
}