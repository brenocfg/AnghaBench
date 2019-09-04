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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ccw_device {TYPE_1__* private; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  onoff; int /*<<< orphan*/  todo_work; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_DISCONNECTED ; 
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_fsm_final_state (struct ccw_device*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int online_store_handle_offline (struct ccw_device*) ; 
 int online_store_handle_online (struct ccw_device*,int) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t online_store (struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	int force, ret;
	unsigned long i;

	/* Prevent conflict between multiple on-/offline processing requests. */
	if (atomic_cmpxchg(&cdev->private->onoff, 0, 1) != 0)
		return -EAGAIN;
	/* Prevent conflict between internal I/Os and on-/offline processing. */
	if (!dev_fsm_final_state(cdev) &&
	    cdev->private->state != DEV_STATE_DISCONNECTED) {
		ret = -EAGAIN;
		goto out;
	}
	/* Prevent conflict between pending work and on-/offline processing.*/
	if (work_pending(&cdev->private->todo_work)) {
		ret = -EAGAIN;
		goto out;
	}
	if (!strncmp(buf, "force\n", count)) {
		force = 1;
		i = 1;
		ret = 0;
	} else {
		force = 0;
		ret = kstrtoul(buf, 16, &i);
	}
	if (ret)
		goto out;

	device_lock(dev);
	switch (i) {
	case 0:
		ret = online_store_handle_offline(cdev);
		break;
	case 1:
		ret = online_store_handle_online(cdev, force);
		break;
	default:
		ret = -EINVAL;
	}
	device_unlock(dev);

out:
	atomic_set(&cdev->private->onoff, 0);
	return (ret < 0) ? ret : count;
}