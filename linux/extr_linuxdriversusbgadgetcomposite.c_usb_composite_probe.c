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
struct TYPE_2__ {char* name; } ;
struct usb_gadget_driver {char* function; int /*<<< orphan*/  max_speed; TYPE_1__ driver; } ;
struct usb_composite_driver {char* name; int /*<<< orphan*/  max_speed; struct usb_gadget_driver gadget_driver; int /*<<< orphan*/  bind; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 struct usb_gadget_driver composite_driver_template ; 
 int usb_gadget_probe_driver (struct usb_gadget_driver*) ; 

int usb_composite_probe(struct usb_composite_driver *driver)
{
	struct usb_gadget_driver *gadget_driver;

	if (!driver || !driver->dev || !driver->bind)
		return -EINVAL;

	if (!driver->name)
		driver->name = "composite";

	driver->gadget_driver = composite_driver_template;
	gadget_driver = &driver->gadget_driver;

	gadget_driver->function =  (char *) driver->name;
	gadget_driver->driver.name = driver->name;
	gadget_driver->max_speed = driver->max_speed;

	return usb_gadget_probe_driver(gadget_driver);
}