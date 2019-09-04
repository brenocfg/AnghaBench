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
struct mdev_type {int /*<<< orphan*/ * devices_kobj; int /*<<< orphan*/  kobj; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  mdev_device_attrs ; 
 int sysfs_create_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

int  mdev_create_sysfs_files(struct device *dev, struct mdev_type *type)
{
	int ret;

	ret = sysfs_create_link(type->devices_kobj, &dev->kobj, dev_name(dev));
	if (ret)
		return ret;

	ret = sysfs_create_link(&dev->kobj, &type->kobj, "mdev_type");
	if (ret)
		goto type_link_failed;

	ret = sysfs_create_files(&dev->kobj, mdev_device_attrs);
	if (ret)
		goto create_files_failed;

	return ret;

create_files_failed:
	sysfs_remove_link(&dev->kobj, "mdev_type");
type_link_failed:
	sysfs_remove_link(type->devices_kobj, dev_name(dev));
	return ret;
}