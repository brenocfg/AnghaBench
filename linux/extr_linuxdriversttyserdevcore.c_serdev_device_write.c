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
struct serdev_device {int /*<<< orphan*/  write_lock; int /*<<< orphan*/  write_comp; TYPE_1__* ops; struct serdev_controller* ctrl; } ;
struct serdev_controller {TYPE_2__* ops; } ;
struct TYPE_4__ {int (* write_buf ) (struct serdev_controller*,unsigned char const*,size_t) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  write_wakeup; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct serdev_controller*,unsigned char const*,size_t) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

int serdev_device_write(struct serdev_device *serdev,
			const unsigned char *buf, size_t count,
			unsigned long timeout)
{
	struct serdev_controller *ctrl = serdev->ctrl;
	int ret;

	if (!ctrl || !ctrl->ops->write_buf ||
	    (timeout && !serdev->ops->write_wakeup))
		return -EINVAL;

	mutex_lock(&serdev->write_lock);
	do {
		reinit_completion(&serdev->write_comp);

		ret = ctrl->ops->write_buf(ctrl, buf, count);
		if (ret < 0)
			break;

		buf += ret;
		count -= ret;

	} while (count &&
		 (timeout = wait_for_completion_timeout(&serdev->write_comp,
							timeout)));
	mutex_unlock(&serdev->write_lock);
	return ret < 0 ? ret : (count ? -ETIMEDOUT : 0);
}