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
struct usb_device_driver {int /*<<< orphan*/  supports_autosuspend; int /*<<< orphan*/  (* disconnect ) (struct usb_device*) ;} ;
struct usb_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usb_device*) ; 
 struct usb_device* to_usb_device (struct device*) ; 
 struct usb_device_driver* to_usb_device_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autosuspend_device (struct usb_device*) ; 

__attribute__((used)) static int usb_unbind_device(struct device *dev)
{
	struct usb_device *udev = to_usb_device(dev);
	struct usb_device_driver *udriver = to_usb_device_driver(dev->driver);

	udriver->disconnect(udev);
	if (!udriver->supports_autosuspend)
		usb_autosuspend_device(udev);
	return 0;
}