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
struct rpmsg_eptdev {int /*<<< orphan*/  dev; int /*<<< orphan*/  readq; int /*<<< orphan*/  ept_lock; int /*<<< orphan*/ * ept; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct rpmsg_eptdev* dev_to_eptdev (struct device*) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmsg_destroy_ept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpmsg_eptdev_destroy(struct device *dev, void *data)
{
	struct rpmsg_eptdev *eptdev = dev_to_eptdev(dev);

	mutex_lock(&eptdev->ept_lock);
	if (eptdev->ept) {
		rpmsg_destroy_ept(eptdev->ept);
		eptdev->ept = NULL;
	}
	mutex_unlock(&eptdev->ept_lock);

	/* wake up any blocked readers */
	wake_up_interruptible(&eptdev->readq);

	device_del(&eptdev->dev);
	put_device(&eptdev->dev);

	return 0;
}