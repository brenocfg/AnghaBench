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
struct notifier_block {int dummy; } ;
struct device {int /*<<< orphan*/ * type; } ;

/* Variables and functions */
#define  BUS_NOTIFY_ADD_DEVICE 129 
#define  BUS_NOTIFY_DEL_DEVICE 128 
 int /*<<< orphan*/  to_usb_device (struct device*) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 
 int /*<<< orphan*/  usb_create_sysfs_dev_files (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_create_sysfs_intf_files (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_type ; 
 int /*<<< orphan*/  usb_if_device_type ; 
 int /*<<< orphan*/  usb_remove_sysfs_dev_files (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_sysfs_intf_files (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_bus_notify(struct notifier_block *nb, unsigned long action,
		void *data)
{
	struct device *dev = data;

	switch (action) {
	case BUS_NOTIFY_ADD_DEVICE:
		if (dev->type == &usb_device_type)
			(void) usb_create_sysfs_dev_files(to_usb_device(dev));
		else if (dev->type == &usb_if_device_type)
			usb_create_sysfs_intf_files(to_usb_interface(dev));
		break;

	case BUS_NOTIFY_DEL_DEVICE:
		if (dev->type == &usb_device_type)
			usb_remove_sysfs_dev_files(to_usb_device(dev));
		else if (dev->type == &usb_if_device_type)
			usb_remove_sysfs_intf_files(to_usb_interface(dev));
		break;
	}
	return 0;
}