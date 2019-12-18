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
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  led_set_user (int) ; 
 int /*<<< orphan*/  set_rgb (int,int,int,int) ; 

void led_set_kb(uint8_t usb_led)
{
    // Set capslock LED to Blue
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        set_rgb(31, 0x00, 0x00, 0x7F);
    }else{
        set_rgb(31, 0x00, 0x00, 0x00);
    }
    led_set_user(usb_led);
}