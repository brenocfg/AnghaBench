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
 int /*<<< orphan*/  activateLED (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  led_set_user (int) ; 

void led_set_kb(uint8_t usb_led)
{
    // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
#ifdef ISSI_ENABLE
#ifdef CAPSLOCK_LED
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        activateLED(0, 3, 7, 255);
    }else{
        activateLED(0, 3, 7, 0);
    }
#endif // CAPSLOCK_LED
#endif // ISS_ENABLE
    led_set_user(usb_led);
}