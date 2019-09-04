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
struct TYPE_4__ {int /*<<< orphan*/  ena; } ;
struct TYPE_5__ {TYPE_1__ pmcw; } ;
struct subchannel {int /*<<< orphan*/  lock; TYPE_2__ schib; int /*<<< orphan*/  schid; } ;
struct ccw_device {TYPE_3__* private; int /*<<< orphan*/  (* handler ) (struct ccw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ state; int iretry; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  intparm; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_QUIESCE ; 
 int EBUSY ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int ccw_device_cancel_halt_clear (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int) ; 
 int cio_disable_subchannel (struct subchannel*) ; 
 scalar_t__ cio_is_console (int /*<<< orphan*/ ) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void io_subchannel_quiesce(struct subchannel *sch)
{
	struct ccw_device *cdev;
	int ret;

	spin_lock_irq(sch->lock);
	cdev = sch_get_cdev(sch);
	if (cio_is_console(sch->schid))
		goto out_unlock;
	if (!sch->schib.pmcw.ena)
		goto out_unlock;
	ret = cio_disable_subchannel(sch);
	if (ret != -EBUSY)
		goto out_unlock;
	if (cdev->handler)
		cdev->handler(cdev, cdev->private->intparm, ERR_PTR(-EIO));
	while (ret == -EBUSY) {
		cdev->private->state = DEV_STATE_QUIESCE;
		cdev->private->iretry = 255;
		ret = ccw_device_cancel_halt_clear(cdev);
		if (ret == -EBUSY) {
			ccw_device_set_timeout(cdev, HZ/10);
			spin_unlock_irq(sch->lock);
			wait_event(cdev->private->wait_q,
				   cdev->private->state != DEV_STATE_QUIESCE);
			spin_lock_irq(sch->lock);
		}
		ret = cio_disable_subchannel(sch);
	}
out_unlock:
	spin_unlock_irq(sch->lock);
}