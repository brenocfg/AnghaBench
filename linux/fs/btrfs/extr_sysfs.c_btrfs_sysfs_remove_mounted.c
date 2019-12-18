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
struct btrfs_fs_info {TYPE_1__* fs_devices; int /*<<< orphan*/ * space_info_kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  fsid_kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  addrm_unknown_feature_attrs (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  allocation_attrs ; 
 int /*<<< orphan*/  btrfs_attrs ; 
 int /*<<< orphan*/  btrfs_feature_attr_group ; 
 int /*<<< orphan*/  btrfs_reset_fs_info_ptr (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_sysfs_rm_device_link (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void btrfs_sysfs_remove_mounted(struct btrfs_fs_info *fs_info)
{
	btrfs_reset_fs_info_ptr(fs_info);

	if (fs_info->space_info_kobj) {
		sysfs_remove_files(fs_info->space_info_kobj, allocation_attrs);
		kobject_del(fs_info->space_info_kobj);
		kobject_put(fs_info->space_info_kobj);
	}
	addrm_unknown_feature_attrs(fs_info, false);
	sysfs_remove_group(&fs_info->fs_devices->fsid_kobj, &btrfs_feature_attr_group);
	sysfs_remove_files(&fs_info->fs_devices->fsid_kobj, btrfs_attrs);
	btrfs_sysfs_rm_device_link(fs_info->fs_devices, NULL);
}