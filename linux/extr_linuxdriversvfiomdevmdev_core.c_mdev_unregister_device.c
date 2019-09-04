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
struct mdev_parent {int /*<<< orphan*/  next; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mdev_parent* __find_parent_device (struct device*) ; 
 int /*<<< orphan*/  class_compat_remove_link (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  device_for_each_child (struct device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdev_bus_compat_class ; 
 int /*<<< orphan*/  mdev_device_remove_cb ; 
 int /*<<< orphan*/  mdev_put_parent (struct mdev_parent*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_list_lock ; 
 int /*<<< orphan*/  parent_remove_sysfs_files (struct mdev_parent*) ; 

void mdev_unregister_device(struct device *dev)
{
	struct mdev_parent *parent;
	bool force_remove = true;

	mutex_lock(&parent_list_lock);
	parent = __find_parent_device(dev);

	if (!parent) {
		mutex_unlock(&parent_list_lock);
		return;
	}
	dev_info(dev, "MDEV: Unregistering\n");

	list_del(&parent->next);
	class_compat_remove_link(mdev_bus_compat_class, dev, NULL);

	device_for_each_child(dev, (void *)&force_remove,
			      mdev_device_remove_cb);

	parent_remove_sysfs_files(parent);

	mutex_unlock(&parent_list_lock);
	mdev_put_parent(parent);
}