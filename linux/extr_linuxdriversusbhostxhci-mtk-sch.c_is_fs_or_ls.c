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
 int USB_SPEED_FULL ; 
 int USB_SPEED_LOW ; 

__attribute__((used)) static int is_fs_or_ls(enum usb_device_speed speed)
{
	return speed == USB_SPEED_FULL || speed == USB_SPEED_LOW;
}