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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_super_block {int dummy; } ;
struct btrfs_fs_info {struct btrfs_super_block* super_copy; } ;
typedef  enum btrfs_feature_set { ____Placeholder_btrfs_feature_set } btrfs_feature_set ;

/* Variables and functions */
 int FEAT_COMPAT ; 
 int FEAT_COMPAT_RO ; 
 int /*<<< orphan*/  btrfs_set_super_compat_flags (struct btrfs_super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_super_compat_ro_flags (struct btrfs_super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_super_incompat_flags (struct btrfs_super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_features(struct btrfs_fs_info *fs_info,
			 enum btrfs_feature_set set, u64 features)
{
	struct btrfs_super_block *disk_super = fs_info->super_copy;
	if (set == FEAT_COMPAT)
		btrfs_set_super_compat_flags(disk_super, features);
	else if (set == FEAT_COMPAT_RO)
		btrfs_set_super_compat_ro_flags(disk_super, features);
	else
		btrfs_set_super_incompat_flags(disk_super, features);
}