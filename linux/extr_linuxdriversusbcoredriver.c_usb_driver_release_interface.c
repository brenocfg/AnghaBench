#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/ * driver; } ;
struct usb_interface {scalar_t__ condition; struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct usb_driver {TYPE_1__ drvwrap; } ;

/* Variables and functions */
 scalar_t__ USB_INTERFACE_BOUND ; 
 scalar_t__ USB_INTERFACE_UNBINDING ; 
 scalar_t__ device_is_registered (struct device*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_release_driver (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  usb_unbind_interface (struct device*) ; 

void usb_driver_release_interface(struct usb_driver *driver,
					struct usb_interface *iface)
{
	struct device *dev = &iface->dev;

	/* this should never happen, don't release something that's not ours */
	if (!dev->driver || dev->driver != &driver->drvwrap.driver)
		return;

	/* don't release from within disconnect() */
	if (iface->condition != USB_INTERFACE_BOUND)
		return;
	iface->condition = USB_INTERFACE_UNBINDING;

	/* Release via the driver core only if the interface
	 * has already been registered
	 */
	if (device_is_registered(dev)) {
		device_release_driver(dev);
	} else {
		device_lock(dev);
		usb_unbind_interface(dev);
		dev->driver = NULL;
		device_unlock(dev);
	}
}