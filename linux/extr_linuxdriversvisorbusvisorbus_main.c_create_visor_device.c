#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int /*<<< orphan*/  release; int /*<<< orphan*/  groups; int /*<<< orphan*/ * bus; } ;
struct TYPE_8__ {int created; } ;
struct visor_device {TYPE_2__ device; TYPE_1__ state; int /*<<< orphan*/  list_all; int /*<<< orphan*/  timer; int /*<<< orphan*/  visordriver_callback_lock; int /*<<< orphan*/  chipset_dev_no; int /*<<< orphan*/  chipset_bus_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLVM_DEVICE_CREATE ; 
 int /*<<< orphan*/  channel_groups ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_periodic_work ; 
 int dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  get_device (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_all_device_instances ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visorbus_release_device ; 
 int /*<<< orphan*/  visorbus_response (struct visor_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visorbus_type ; 

int create_visor_device(struct visor_device *dev)
{
	int err;
	u32 chipset_bus_no = dev->chipset_bus_no;
	u32 chipset_dev_no = dev->chipset_dev_no;

	mutex_init(&dev->visordriver_callback_lock);
	dev->device.bus = &visorbus_type;
	dev->device.groups = channel_groups;
	device_initialize(&dev->device);
	dev->device.release = visorbus_release_device;
	/* keep a reference just for us (now 2) */
	get_device(&dev->device);
	timer_setup(&dev->timer, dev_periodic_work, 0);
	/*
	 * bus_id must be a unique name with respect to this bus TYPE (NOT bus
	 * instance).  That's why we need to include the bus number within the
	 * name.
	 */
	err = dev_set_name(&dev->device, "vbus%u:dev%u",
			   chipset_bus_no, chipset_dev_no);
	if (err)
		goto err_put;
	/*
	 * device_add does this:
	 *    bus_add_device(dev)
	 *    ->device_attach(dev)
	 *      ->for each driver drv registered on the bus that dev is on
	 *          if (dev.drv)  **  device already has a driver **
	 *            ** not sure we could ever get here... **
	 *          else
	 *            if (bus.match(dev,drv)) [visorbus_match]
	 *              dev.drv = drv
	 *              if (!drv.probe(dev))  [visordriver_probe_device]
	 *                dev.drv = NULL
	 *
	 * Note that device_add does NOT fail if no driver failed to claim the
	 * device.  The device will be linked onto bus_type.klist_devices
	 * regardless (use bus_for_each_dev).
	 */
	err = device_add(&dev->device);
	if (err < 0)
		goto err_put;
	list_add_tail(&dev->list_all, &list_all_device_instances);
	dev->state.created = 1;
	visorbus_response(dev, err, CONTROLVM_DEVICE_CREATE);
	/* success: reference kept via unmatched get_device() */
	return 0;

err_put:
	put_device(&dev->device);
	dev_err(&dev->device, "Creating visor device failed. %d\n", err);
	return err;
}