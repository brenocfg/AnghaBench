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
struct usb_serial_driver {int /*<<< orphan*/  driver_list; int /*<<< orphan*/  description; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_lock ; 
 int /*<<< orphan*/  usb_serial_bus_deregister (struct usb_serial_driver*) ; 

__attribute__((used)) static void usb_serial_deregister(struct usb_serial_driver *device)
{
	pr_info("USB Serial deregistering driver %s\n", device->description);

	mutex_lock(&table_lock);
	list_del(&device->driver_list);
	mutex_unlock(&table_lock);

	usb_serial_bus_deregister(device);
}