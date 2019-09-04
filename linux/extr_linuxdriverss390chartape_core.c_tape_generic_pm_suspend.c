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
struct tape_device {scalar_t__ medium_state; int tape_state; int /*<<< orphan*/  cdev_id; int /*<<< orphan*/  cdev; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_LH (int,char*,int /*<<< orphan*/ ,...) ; 
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ MS_UNLOADED ; 
#define  TS_INIT 130 
#define  TS_NOT_OPER 129 
#define  TS_UNUSED 128 
 struct tape_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

int tape_generic_pm_suspend(struct ccw_device *cdev)
{
	struct tape_device *device;

	device = dev_get_drvdata(&cdev->dev);
	if (!device) {
		return -ENODEV;
	}

	DBF_LH(3, "(%08x): tape_generic_pm_suspend(%p)\n",
		device->cdev_id, device);

	if (device->medium_state != MS_UNLOADED) {
		pr_err("A cartridge is loaded in tape device %s, "
		       "refusing to suspend\n", dev_name(&cdev->dev));
		return -EBUSY;
	}

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	switch (device->tape_state) {
		case TS_INIT:
		case TS_NOT_OPER:
		case TS_UNUSED:
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			break;
		default:
			pr_err("Tape device %s is busy, refusing to "
			       "suspend\n", dev_name(&cdev->dev));
			spin_unlock_irq(get_ccwdev_lock(device->cdev));
			return -EBUSY;
	}

	DBF_LH(3, "(%08x): Drive suspended.\n", device->cdev_id);
	return 0;
}