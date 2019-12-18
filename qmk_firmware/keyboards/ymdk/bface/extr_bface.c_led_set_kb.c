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
 int /*<<< orphan*/  D1 ; 
 scalar_t__ IS_LED_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  led_set_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void led_set_kb(uint8_t usb_led){
    //control the caps lock LED
    if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)){
        //set led pin to high
        writePinHigh(D1);
    } else {
        //set to low
        writePinLow(D1);
    }
    //call any user LED functions
    led_set_user(usb_led);
}