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
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {scalar_t__ pending_changes; TYPE_1__* btree_inode; struct btrfs_root* tree_root; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  U64_MAX ; 
 struct btrfs_trans_handle* btrfs_attach_transaction_barrier (struct btrfs_root*) ; 
 int btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_wait_ordered_roots (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_end_write (struct super_block*) ; 
 scalar_t__ sb_start_write_trylock (struct super_block*) ; 
 int /*<<< orphan*/  trace_btrfs_sync_fs (struct btrfs_fs_info*,int) ; 

int btrfs_sync_fs(struct super_block *sb, int wait)
{
	struct btrfs_trans_handle *trans;
	struct btrfs_fs_info *fs_info = btrfs_sb(sb);
	struct btrfs_root *root = fs_info->tree_root;

	trace_btrfs_sync_fs(fs_info, wait);

	if (!wait) {
		filemap_flush(fs_info->btree_inode->i_mapping);
		return 0;
	}

	btrfs_wait_ordered_roots(fs_info, U64_MAX, 0, (u64)-1);

	trans = btrfs_attach_transaction_barrier(root);
	if (IS_ERR(trans)) {
		/* no transaction, don't bother */
		if (PTR_ERR(trans) == -ENOENT) {
			/*
			 * Exit unless we have some pending changes
			 * that need to go through commit
			 */
			if (fs_info->pending_changes == 0)
				return 0;
			/*
			 * A non-blocking test if the fs is frozen. We must not
			 * start a new transaction here otherwise a deadlock
			 * happens. The pending operations are delayed to the
			 * next commit after thawing.
			 */
			if (sb_start_write_trylock(sb))
				sb_end_write(sb);
			else
				return 0;
			trans = btrfs_start_transaction(root, 0);
		}
		if (IS_ERR(trans))
			return PTR_ERR(trans);
	}
	return btrfs_commit_transaction(trans);
}