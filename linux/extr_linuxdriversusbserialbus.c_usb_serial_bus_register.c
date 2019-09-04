#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct usb_serial_driver {TYPE_2__ driver; TYPE_1__ dynids; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int driver_register (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_serial_bus_type ; 

int usb_serial_bus_register(struct usb_serial_driver *driver)
{
	int retval;

	driver->driver.bus = &usb_serial_bus_type;
	spin_lock_init(&driver->dynids.lock);
	INIT_LIST_HEAD(&driver->dynids.list);

	retval = driver_register(&driver->driver);

	return retval;
}