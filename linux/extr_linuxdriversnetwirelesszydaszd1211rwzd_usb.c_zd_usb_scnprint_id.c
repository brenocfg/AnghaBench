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
struct zd_usb {int /*<<< orphan*/  intf; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int scnprint_id (struct usb_device*,char*,size_t) ; 

int zd_usb_scnprint_id(struct zd_usb *usb, char *buffer, size_t size)
{
	struct usb_device *udev = interface_to_usbdev(usb->intf);
	return scnprint_id(udev, buffer, size);
}