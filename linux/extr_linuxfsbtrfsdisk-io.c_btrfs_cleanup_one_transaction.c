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
struct btrfs_transaction {int /*<<< orphan*/  commit_wait; int /*<<< orphan*/  state; int /*<<< orphan*/  dirty_pages; int /*<<< orphan*/  io_bgs; int /*<<< orphan*/  dirty_bgs; } ;
struct btrfs_fs_info {int /*<<< orphan*/  pinned_extents; int /*<<< orphan*/  transaction_wait; int /*<<< orphan*/  transaction_blocked_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTENT_DIRTY ; 
 int /*<<< orphan*/  TRANS_STATE_COMMIT_START ; 
 int /*<<< orphan*/  TRANS_STATE_COMPLETED ; 
 int /*<<< orphan*/  TRANS_STATE_UNBLOCKED ; 
 int /*<<< orphan*/  btrfs_assert_delayed_root_empty (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_cleanup_dirty_bgs (struct btrfs_transaction*,struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_destroy_delayed_inodes (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_destroy_delayed_refs (struct btrfs_transaction*,struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_destroy_marked_extents (struct btrfs_fs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_destroy_pinned_extent (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void btrfs_cleanup_one_transaction(struct btrfs_transaction *cur_trans,
				   struct btrfs_fs_info *fs_info)
{
	btrfs_cleanup_dirty_bgs(cur_trans, fs_info);
	ASSERT(list_empty(&cur_trans->dirty_bgs));
	ASSERT(list_empty(&cur_trans->io_bgs));

	btrfs_destroy_delayed_refs(cur_trans, fs_info);

	cur_trans->state = TRANS_STATE_COMMIT_START;
	wake_up(&fs_info->transaction_blocked_wait);

	cur_trans->state = TRANS_STATE_UNBLOCKED;
	wake_up(&fs_info->transaction_wait);

	btrfs_destroy_delayed_inodes(fs_info);
	btrfs_assert_delayed_root_empty(fs_info);

	btrfs_destroy_marked_extents(fs_info, &cur_trans->dirty_pages,
				     EXTENT_DIRTY);
	btrfs_destroy_pinned_extent(fs_info,
				    fs_info->pinned_extents);

	cur_trans->state =TRANS_STATE_COMPLETED;
	wake_up(&cur_trans->commit_wait);
}