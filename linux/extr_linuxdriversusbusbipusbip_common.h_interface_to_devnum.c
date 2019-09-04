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
struct usb_interface {int dummy; } ;
struct usb_device {int devnum; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 

__attribute__((used)) static inline int interface_to_devnum(struct usb_interface *interface)
{
	struct usb_device *udev = interface_to_usbdev(interface);

	return udev->devnum;
}