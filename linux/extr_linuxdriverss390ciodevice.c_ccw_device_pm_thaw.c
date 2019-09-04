#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct subchannel {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_2__* drv; TYPE_1__* private; int /*<<< orphan*/  online; TYPE_3__ dev; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_5__ {int (* thaw ) (struct ccw_device*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * cmb; } ;

/* Variables and functions */
 int ccw_set_cmf (struct ccw_device*,int) ; 
 int cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int stub1 (struct ccw_device*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccw_device_pm_thaw(struct device *dev)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct subchannel *sch = to_subchannel(cdev->dev.parent);
	int ret, cm_enabled;

	if (!cdev->online)
		return 0;

	spin_lock_irq(sch->lock);
	/* Allow device driver I/O again. */
	ret = cio_enable_subchannel(sch, (u32)(addr_t)sch);
	cm_enabled = cdev->private->cmb != NULL;
	spin_unlock_irq(sch->lock);
	if (ret)
		return ret;

	if (cm_enabled) {
		ret = ccw_set_cmf(cdev, 1);
		if (ret)
			return ret;
	}

	if (cdev->drv && cdev->drv->thaw)
		ret = cdev->drv->thaw(cdev);

	return ret;
}