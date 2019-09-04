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
struct kobject {int dummy; } ;
struct TYPE_4__ {int (* create ) (struct kobject*,struct mdev_device*) ;int /*<<< orphan*/  (* remove ) (struct mdev_device*) ;int /*<<< orphan*/  mdev_attr_groups; } ;

/* Variables and functions */
 int stub1 (struct kobject*,struct mdev_device*) ; 
 int /*<<< orphan*/  stub2 (struct mdev_device*) ; 
 int sysfs_create_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdev_device_create_ops(struct kobject *kobj,
				  struct mdev_device *mdev)
{
	struct mdev_parent *parent = mdev->parent;
	int ret;

	ret = parent->ops->create(kobj, mdev);
	if (ret)
		return ret;

	ret = sysfs_create_groups(&mdev->dev.kobj,
				  parent->ops->mdev_attr_groups);
	if (ret)
		parent->ops->remove(mdev);

	return ret;
}