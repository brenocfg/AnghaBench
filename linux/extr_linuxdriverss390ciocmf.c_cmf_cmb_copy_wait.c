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
struct copy_block_struct {int ret; int /*<<< orphan*/  wait; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_2__ {scalar_t__ state; struct copy_block_struct* cmb_wait; int /*<<< orphan*/  cmb; } ;

/* Variables and functions */
 int CMF_PENDING ; 
 scalar_t__ DEV_STATE_CMFUPDATE ; 
 scalar_t__ DEV_STATE_ONLINE ; 
 int EBUSY ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int cmf_copy_block (struct ccw_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cmf_cmb_copy_wait(struct ccw_device *cdev)
{
	struct copy_block_struct copy_block;
	int ret = -ENODEV;

	spin_lock_irq(cdev->ccwlock);
	if (!cdev->private->cmb)
		goto out;

	ret = cmf_copy_block(cdev);
	if (ret != -EBUSY)
		goto out;

	if (cdev->private->state != DEV_STATE_ONLINE)
		goto out;

	init_waitqueue_head(&copy_block.wait);
	copy_block.ret = CMF_PENDING;

	cdev->private->state = DEV_STATE_CMFUPDATE;
	cdev->private->cmb_wait = &copy_block;
	spin_unlock_irq(cdev->ccwlock);

	ret = wait_event_interruptible(copy_block.wait,
				       copy_block.ret != CMF_PENDING);
	spin_lock_irq(cdev->ccwlock);
	if (ret) {
		if (copy_block.ret == CMF_PENDING) {
			copy_block.ret = -ERESTARTSYS;
			if (cdev->private->state == DEV_STATE_CMFUPDATE)
				cdev->private->state = DEV_STATE_ONLINE;
		}
	}
	cdev->private->cmb_wait = NULL;
	ret = copy_block.ret;
out:
	spin_unlock_irq(cdev->ccwlock);
	return ret;
}