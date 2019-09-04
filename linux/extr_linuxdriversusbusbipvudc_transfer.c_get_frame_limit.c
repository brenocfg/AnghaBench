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
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_SUPER 128 

__attribute__((used)) static int get_frame_limit(enum usb_device_speed speed)
{
	switch (speed) {
	case USB_SPEED_LOW:
		return 8 /*bytes*/ * 12 /*packets*/;
	case USB_SPEED_FULL:
		return 64 /*bytes*/ * 19 /*packets*/;
	case USB_SPEED_HIGH:
		return 512 /*bytes*/ * 13 /*packets*/ * 8 /*uframes*/;
	case USB_SPEED_SUPER:
		/* Bus speed is 500000 bytes/ms, so use a little less */
		return 490000;
	default:
		/* error */
		return -1;
	}

}