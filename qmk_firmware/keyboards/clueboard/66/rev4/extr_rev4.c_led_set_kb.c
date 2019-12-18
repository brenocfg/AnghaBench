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
 int /*<<< orphan*/  GPIOA ; 
 int /*<<< orphan*/  GPIOB ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  palClearPad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  palSetPad (int /*<<< orphan*/ ,int) ; 

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        palSetPad(GPIOB, 13);    // LED1
    } else {
        palClearPad(GPIOB, 13);  // LED1
    }

    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        palSetPad(GPIOA, 0);     // Capslock LED
        palSetPad(GPIOB, 14);    // LED2
    } else {
        palClearPad(GPIOA, 0);   // Capslock LED
        palClearPad(GPIOB, 14);  // LED2
    }

    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        palSetPad(GPIOA, 8);     // LED3
    } else {
        palClearPad(GPIOA, 8);   // LED3
    }
}