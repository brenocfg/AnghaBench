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
struct btrfs_fs_info {unsigned long mount_opt; int /*<<< orphan*/  fs_state; int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_DEFRAG ; 
 int /*<<< orphan*/  BTRFS_FS_STATE_REMOUNTING ; 
 int /*<<< orphan*/  btrfs_cleanup_defrag_inodes (struct btrfs_fs_info*) ; 
 scalar_t__ btrfs_raw_test_opt (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sb_rdonly (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void btrfs_remount_cleanup(struct btrfs_fs_info *fs_info,
					 unsigned long old_opts)
{
	/*
	 * We need to cleanup all defragable inodes if the autodefragment is
	 * close or the filesystem is read only.
	 */
	if (btrfs_raw_test_opt(old_opts, AUTO_DEFRAG) &&
	    (!btrfs_raw_test_opt(fs_info->mount_opt, AUTO_DEFRAG) || sb_rdonly(fs_info->sb))) {
		btrfs_cleanup_defrag_inodes(fs_info);
	}

	clear_bit(BTRFS_FS_STATE_REMOUNTING, &fs_info->fs_state);
}