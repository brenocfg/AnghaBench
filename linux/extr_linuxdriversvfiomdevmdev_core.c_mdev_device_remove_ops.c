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
struct mdev_parent {TYPE_2__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct mdev_device {TYPE_1__ dev; struct mdev_parent* parent; } ;
struct TYPE_4__ {int (* remove ) (struct mdev_device*) ;int /*<<< orphan*/  mdev_attr_groups; } ;

/* Variables and functions */
 int EBUSY ; 
 int stub1 (struct mdev_device*) ; 
 int /*<<< orphan*/  sysfs_remove_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdev_device_remove_ops(struct mdev_device *mdev, bool force_remove)
{
	struct mdev_parent *parent = mdev->parent;
	int ret;

	/*
	 * Vendor driver can return error if VMM or userspace application is
	 * using this mdev device.
	 */
	ret = parent->ops->remove(mdev);
	if (ret && !force_remove)
		return -EBUSY;

	sysfs_remove_groups(&mdev->dev.kobj, parent->ops->mdev_attr_groups);
	return 0;
}