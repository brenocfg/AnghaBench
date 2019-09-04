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
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int USB_SPEED_UNKNOWN ; 
 char const** speed_names ; 

const char *usb_speed_string(enum usb_device_speed speed)
{
	if (speed < 0 || speed >= ARRAY_SIZE(speed_names))
		speed = USB_SPEED_UNKNOWN;
	return speed_names[speed];
}