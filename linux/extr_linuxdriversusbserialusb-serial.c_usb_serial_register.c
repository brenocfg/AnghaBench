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
struct TYPE_2__ {scalar_t__ name; } ;
struct usb_serial_driver {scalar_t__ description; int /*<<< orphan*/  driver_list; int /*<<< orphan*/  usb_driver; TYPE_1__ driver; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  WARN (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  table_lock ; 
 scalar_t__ usb_disabled () ; 
 int usb_serial_bus_register (struct usb_serial_driver*) ; 
 int /*<<< orphan*/  usb_serial_driver_list ; 
 int /*<<< orphan*/  usb_serial_operations_init (struct usb_serial_driver*) ; 

__attribute__((used)) static int usb_serial_register(struct usb_serial_driver *driver)
{
	int retval;

	if (usb_disabled())
		return -ENODEV;

	if (!driver->description)
		driver->description = driver->driver.name;
	if (!driver->usb_driver) {
		WARN(1, "Serial driver %s has no usb_driver\n",
				driver->description);
		return -EINVAL;
	}

	usb_serial_operations_init(driver);

	/* Add this device to our list of devices */
	mutex_lock(&table_lock);
	list_add(&driver->driver_list, &usb_serial_driver_list);

	retval = usb_serial_bus_register(driver);
	if (retval) {
		pr_err("problem %d when registering driver %s\n", retval, driver->description);
		list_del(&driver->driver_list);
	} else {
		pr_info("USB Serial support registered for %s\n", driver->description);
	}
	mutex_unlock(&table_lock);
	return retval;
}