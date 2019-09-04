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
 unsigned int FS_BLOCK ; 
 unsigned int HS_BLOCK ; 
 unsigned int SS_BLOCK ; 
#define  USB_SPEED_FULL 134 
#define  USB_SPEED_HIGH 133 
#define  USB_SPEED_LOW 132 
#define  USB_SPEED_SUPER 131 
#define  USB_SPEED_SUPER_PLUS 130 
#define  USB_SPEED_UNKNOWN 129 
#define  USB_SPEED_WIRELESS 128 

__attribute__((used)) static unsigned int xhci_get_block_size(struct usb_device *udev)
{
	switch (udev->speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
		return FS_BLOCK;
	case USB_SPEED_HIGH:
		return HS_BLOCK;
	case USB_SPEED_SUPER:
	case USB_SPEED_SUPER_PLUS:
		return SS_BLOCK;
	case USB_SPEED_UNKNOWN:
	case USB_SPEED_WIRELESS:
	default:
		/* Should never happen */
		return 1;
	}
}