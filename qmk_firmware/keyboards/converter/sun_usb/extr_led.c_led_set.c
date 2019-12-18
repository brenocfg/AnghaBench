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
 int USB_LED_COMPOSE ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  serial_send (int) ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void led_set(uint8_t usb_led)
{
    uint8_t sun_led = 0;
    if (usb_led & (1<<USB_LED_NUM_LOCK))    sun_led |= (1<<0);
    if (usb_led & (1<<USB_LED_COMPOSE))     sun_led |= (1<<1);
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) sun_led |= (1<<2);
    if (usb_led & (1<<USB_LED_CAPS_LOCK))   sun_led |= (1<<3);
    xprintf("LED: %02X\n", usb_led);

    serial_send(0x0E);
    serial_send(sun_led);
}