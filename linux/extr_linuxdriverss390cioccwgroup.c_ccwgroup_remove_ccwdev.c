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
struct ccwgroup_device {int /*<<< orphan*/  dev; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_device_set_offline (struct ccw_device*) ; 
 int /*<<< orphan*/  ccwgroup_ungroup (struct ccwgroup_device*) ; 
 struct ccwgroup_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

void ccwgroup_remove_ccwdev(struct ccw_device *cdev)
{
	struct ccwgroup_device *gdev;

	/* Ignore offlining errors, device is gone anyway. */
	ccw_device_set_offline(cdev);
	/* If one of its devices is gone, the whole group is done for. */
	spin_lock_irq(cdev->ccwlock);
	gdev = dev_get_drvdata(&cdev->dev);
	if (!gdev) {
		spin_unlock_irq(cdev->ccwlock);
		return;
	}
	/* Get ccwgroup device reference for local processing. */
	get_device(&gdev->dev);
	spin_unlock_irq(cdev->ccwlock);
	/* Unregister group device. */
	ccwgroup_ungroup(gdev);
	/* Release ccwgroup device reference for local processing. */
	put_device(&gdev->dev);
}