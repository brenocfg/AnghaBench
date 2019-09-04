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
struct btrfs_fs_devices {scalar_t__ device_dir_kobj; int /*<<< orphan*/  fsid_kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 

int btrfs_sysfs_add_device(struct btrfs_fs_devices *fs_devs)
{
	if (!fs_devs->device_dir_kobj)
		fs_devs->device_dir_kobj = kobject_create_and_add("devices",
						&fs_devs->fsid_kobj);

	if (!fs_devs->device_dir_kobj)
		return -ENOMEM;

	return 0;
}