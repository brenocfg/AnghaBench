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
struct kobject {int dummy; } ;
struct btrfs_fs_info {struct kobject* space_info_kobj; struct btrfs_fs_devices* fs_devices; } ;
struct btrfs_fs_devices {struct kobject fsid_kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int addrm_unknown_feature_attrs (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  allocation_attrs ; 
 int /*<<< orphan*/  btrfs_attrs ; 
 int /*<<< orphan*/  btrfs_debug_feature_attr_group ; 
 int /*<<< orphan*/  btrfs_feature_attr_group ; 
 int /*<<< orphan*/  btrfs_set_fs_info_ptr (struct btrfs_fs_info*) ; 
 int btrfs_sysfs_add_device_link (struct btrfs_fs_devices*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_sysfs_remove_mounted (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_sysfs_rm_device_link (struct btrfs_fs_devices*,int /*<<< orphan*/ *) ; 
 struct kobject* kobject_create_and_add (char*,struct kobject*) ; 
 int sysfs_create_files (struct kobject*,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (struct kobject*,int /*<<< orphan*/ *) ; 

int btrfs_sysfs_add_mounted(struct btrfs_fs_info *fs_info)
{
	int error;
	struct btrfs_fs_devices *fs_devs = fs_info->fs_devices;
	struct kobject *fsid_kobj = &fs_devs->fsid_kobj;

	btrfs_set_fs_info_ptr(fs_info);

	error = btrfs_sysfs_add_device_link(fs_devs, NULL);
	if (error)
		return error;

	error = sysfs_create_files(fsid_kobj, btrfs_attrs);
	if (error) {
		btrfs_sysfs_rm_device_link(fs_devs, NULL);
		return error;
	}

	error = sysfs_create_group(fsid_kobj,
				   &btrfs_feature_attr_group);
	if (error)
		goto failure;

#ifdef CONFIG_BTRFS_DEBUG
	error = sysfs_create_group(fsid_kobj,
				   &btrfs_debug_feature_attr_group);
	if (error)
		goto failure;
#endif

	error = addrm_unknown_feature_attrs(fs_info, true);
	if (error)
		goto failure;

	fs_info->space_info_kobj = kobject_create_and_add("allocation",
						  fsid_kobj);
	if (!fs_info->space_info_kobj) {
		error = -ENOMEM;
		goto failure;
	}

	error = sysfs_create_files(fs_info->space_info_kobj, allocation_attrs);
	if (error)
		goto failure;

	return 0;
failure:
	btrfs_sysfs_remove_mounted(fs_info);
	return error;
}