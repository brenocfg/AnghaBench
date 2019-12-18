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
struct btrfs_super_block {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  super_lock; struct btrfs_super_block* super_copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_info (struct btrfs_fs_info*,char*,char const*,int) ; 
 int /*<<< orphan*/  btrfs_set_super_incompat_flags (struct btrfs_super_block*,int) ; 
 int btrfs_super_incompat_flags (struct btrfs_super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __btrfs_clear_fs_incompat(struct btrfs_fs_info *fs_info,
					     u64 flag, const char* name)
{
	struct btrfs_super_block *disk_super;
	u64 features;

	disk_super = fs_info->super_copy;
	features = btrfs_super_incompat_flags(disk_super);
	if (features & flag) {
		spin_lock(&fs_info->super_lock);
		features = btrfs_super_incompat_flags(disk_super);
		if (features & flag) {
			features &= ~flag;
			btrfs_set_super_incompat_flags(disk_super, features);
			btrfs_info(fs_info,
				"clearing incompat feature flag for %s (0x%llx)",
				name, flag);
		}
		spin_unlock(&fs_info->super_lock);
	}
}