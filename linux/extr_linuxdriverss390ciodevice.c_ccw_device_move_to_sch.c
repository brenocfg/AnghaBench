#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {int /*<<< orphan*/  ssid; } ;
struct TYPE_9__ {int ena; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_3__ pmcw; } ;
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_6__ schid; TYPE_4__ schib; int /*<<< orphan*/  reg_mutex; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_2__* private; TYPE_5__ dev; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_8__ {TYPE_1__ dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPM_ORDER_PARENT_BEFORE_DEV ; 
 int EBUSY ; 
 int ENODEV ; 
 int cio_disable_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  css_schedule_eval (TYPE_6__) ; 
 int /*<<< orphan*/  css_update_ssd_info (struct subchannel*) ; 
 int device_move (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sch_is_pseudo_sch (struct subchannel*) ; 
 int /*<<< orphan*/  sch_set_cdev (struct subchannel*,struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccw_device_move_to_sch(struct ccw_device *cdev,
				  struct subchannel *sch)
{
	struct subchannel *old_sch;
	int rc, old_enabled = 0;

	old_sch = to_subchannel(cdev->dev.parent);
	/* Obtain child reference for new parent. */
	if (!get_device(&sch->dev))
		return -ENODEV;

	if (!sch_is_pseudo_sch(old_sch)) {
		spin_lock_irq(old_sch->lock);
		old_enabled = old_sch->schib.pmcw.ena;
		rc = 0;
		if (old_enabled)
			rc = cio_disable_subchannel(old_sch);
		spin_unlock_irq(old_sch->lock);
		if (rc == -EBUSY) {
			/* Release child reference for new parent. */
			put_device(&sch->dev);
			return rc;
		}
	}

	mutex_lock(&sch->reg_mutex);
	rc = device_move(&cdev->dev, &sch->dev, DPM_ORDER_PARENT_BEFORE_DEV);
	mutex_unlock(&sch->reg_mutex);
	if (rc) {
		CIO_MSG_EVENT(0, "device_move(0.%x.%04x,0.%x.%04x)=%d\n",
			      cdev->private->dev_id.ssid,
			      cdev->private->dev_id.devno, sch->schid.ssid,
			      sch->schib.pmcw.dev, rc);
		if (old_enabled) {
			/* Try to reenable the old subchannel. */
			spin_lock_irq(old_sch->lock);
			cio_enable_subchannel(old_sch, (u32)(addr_t)old_sch);
			spin_unlock_irq(old_sch->lock);
		}
		/* Release child reference for new parent. */
		put_device(&sch->dev);
		return rc;
	}
	/* Clean up old subchannel. */
	if (!sch_is_pseudo_sch(old_sch)) {
		spin_lock_irq(old_sch->lock);
		sch_set_cdev(old_sch, NULL);
		spin_unlock_irq(old_sch->lock);
		css_schedule_eval(old_sch->schid);
	}
	/* Release child reference for old parent. */
	put_device(&old_sch->dev);
	/* Initialize new subchannel. */
	spin_lock_irq(sch->lock);
	cdev->ccwlock = sch->lock;
	if (!sch_is_pseudo_sch(sch))
		sch_set_cdev(sch, cdev);
	spin_unlock_irq(sch->lock);
	if (!sch_is_pseudo_sch(sch))
		css_update_ssd_info(sch);
	return 0;
}