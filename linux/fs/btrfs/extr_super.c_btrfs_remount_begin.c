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
struct btrfs_fs_info {unsigned long mount_opt; int /*<<< orphan*/  sb; int /*<<< orphan*/  defrag_running; int /*<<< orphan*/  transaction_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_DEFRAG ; 
 int SB_RDONLY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_raw_test_opt (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_filesystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void btrfs_remount_begin(struct btrfs_fs_info *fs_info,
				       unsigned long old_opts, int flags)
{
	if (btrfs_raw_test_opt(old_opts, AUTO_DEFRAG) &&
	    (!btrfs_raw_test_opt(fs_info->mount_opt, AUTO_DEFRAG) ||
	     (flags & SB_RDONLY))) {
		/* wait for any defraggers to finish */
		wait_event(fs_info->transaction_wait,
			   (atomic_read(&fs_info->defrag_running) == 0));
		if (flags & SB_RDONLY)
			sync_filesystem(fs_info->sb);
	}
}