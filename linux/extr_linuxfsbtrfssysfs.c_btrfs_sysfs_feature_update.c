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
typedef  int u64 ;
struct kobject {int /*<<< orphan*/  state_initialized; } ;
struct btrfs_fs_info {struct btrfs_fs_devices* fs_devices; } ;
struct btrfs_fs_devices {struct kobject fsid_kobj; } ;
typedef  enum btrfs_feature_set { ____Placeholder_btrfs_feature_set } btrfs_feature_set ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  btrfs_feature_attr_group ; 
 int get_features (struct btrfs_fs_info*,int) ; 
 int* supported_feature_masks ; 
 int sysfs_create_group (struct kobject*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (struct kobject*,int /*<<< orphan*/ *) ; 

void btrfs_sysfs_feature_update(struct btrfs_fs_info *fs_info,
		u64 bit, enum btrfs_feature_set set)
{
	struct btrfs_fs_devices *fs_devs;
	struct kobject *fsid_kobj;
	u64 features;
	int ret;

	if (!fs_info)
		return;

	features = get_features(fs_info, set);
	ASSERT(bit & supported_feature_masks[set]);

	fs_devs = fs_info->fs_devices;
	fsid_kobj = &fs_devs->fsid_kobj;

	if (!fsid_kobj->state_initialized)
		return;

	/*
	 * FIXME: this is too heavy to update just one value, ideally we'd like
	 * to use sysfs_update_group but some refactoring is needed first.
	 */
	sysfs_remove_group(fsid_kobj, &btrfs_feature_attr_group);
	ret = sysfs_create_group(fsid_kobj, &btrfs_feature_attr_group);
}