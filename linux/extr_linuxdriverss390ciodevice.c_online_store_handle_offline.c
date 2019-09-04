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
struct ccw_device {TYPE_2__* drv; int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct TYPE_4__ {scalar_t__ set_offline; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_TODO_UNREG_EVAL ; 
 scalar_t__ DEV_STATE_DISCONNECTED ; 
 int EINVAL ; 
 int /*<<< orphan*/  ccw_device_sched_todo (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int ccw_device_set_offline (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int online_store_handle_offline(struct ccw_device *cdev)
{
	if (cdev->private->state == DEV_STATE_DISCONNECTED) {
		spin_lock_irq(cdev->ccwlock);
		ccw_device_sched_todo(cdev, CDEV_TODO_UNREG_EVAL);
		spin_unlock_irq(cdev->ccwlock);
		return 0;
	}
	if (cdev->drv && cdev->drv->set_offline)
		return ccw_device_set_offline(cdev);
	return -EINVAL;
}