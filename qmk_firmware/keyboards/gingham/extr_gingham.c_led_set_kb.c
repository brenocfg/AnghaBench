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
 scalar_t__ IS_LED_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PORT_EXPANDER_ADDRESS ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  i2c_writeReg (int,int,int*,int,int) ; 
 int /*<<< orphan*/  led_set_user (int /*<<< orphan*/ ) ; 
 int send_data ; 

void led_set_kb(uint8_t usb_led) {
    // Bit 3 is Green LED, bit 4 is Red LED.
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        send_data = 0x18;
    } else {
        send_data = 0x10;
    }
    i2c_writeReg((PORT_EXPANDER_ADDRESS << 1), 0x09, &send_data, 1, 20);

    led_set_user(usb_led);
}