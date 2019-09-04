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
struct usb_interface {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct usb_driver {TYPE_1__ drvwrap; } ;
struct find_interface_arg {int minor; int /*<<< orphan*/ * drv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __find_interface ; 
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct find_interface_arg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  usb_bus_type ; 

struct usb_interface *usb_find_interface(struct usb_driver *drv, int minor)
{
	struct find_interface_arg argb;
	struct device *dev;

	argb.minor = minor;
	argb.drv = &drv->drvwrap.driver;

	dev = bus_find_device(&usb_bus_type, NULL, &argb, __find_interface);

	/* Drop reference count from bus_find_device */
	put_device(dev);

	return dev ? to_usb_interface(dev) : NULL;
}