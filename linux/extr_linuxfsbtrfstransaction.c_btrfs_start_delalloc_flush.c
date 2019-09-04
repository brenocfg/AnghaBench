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
struct btrfs_fs_info {int /*<<< orphan*/  sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLUSHONCOMMIT ; 
 int /*<<< orphan*/  WB_REASON_SYNC ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeback_inodes_sb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int btrfs_start_delalloc_flush(struct btrfs_fs_info *fs_info)
{
	/*
	 * We use writeback_inodes_sb here because if we used
	 * btrfs_start_delalloc_roots we would deadlock with fs freeze.
	 * Currently are holding the fs freeze lock, if we do an async flush
	 * we'll do btrfs_join_transaction() and deadlock because we need to
	 * wait for the fs freeze lock.  Using the direct flushing we benefit
	 * from already being in a transaction and our join_transaction doesn't
	 * have to re-take the fs freeze lock.
	 */
	if (btrfs_test_opt(fs_info, FLUSHONCOMMIT))
		writeback_inodes_sb(fs_info->sb, WB_REASON_SYNC);
	return 0;
}