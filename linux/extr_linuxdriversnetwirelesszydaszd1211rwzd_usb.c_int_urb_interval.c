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
struct usb_device {int speed; } ;

/* Variables and functions */
#define  USB_SPEED_FULL 130 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 

__attribute__((used)) static inline int int_urb_interval(struct usb_device *udev)
{
	switch (udev->speed) {
	case USB_SPEED_HIGH:
		return 4;
	case USB_SPEED_LOW:
		return 10;
	case USB_SPEED_FULL:
	default:
		return 1;
	}
}