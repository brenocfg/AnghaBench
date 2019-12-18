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
struct super_block {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; struct btrfs_root* tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_FROZEN ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_attach_transaction_barrier (struct btrfs_root*) ; 
 int btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_fs_info* btrfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_freeze(struct super_block *sb)
{
	struct btrfs_trans_handle *trans;
	struct btrfs_fs_info *fs_info = btrfs_sb(sb);
	struct btrfs_root *root = fs_info->tree_root;

	set_bit(BTRFS_FS_FROZEN, &fs_info->flags);
	/*
	 * We don't need a barrier here, we'll wait for any transaction that
	 * could be in progress on other threads (and do delayed iputs that
	 * we want to avoid on a frozen filesystem), or do the commit
	 * ourselves.
	 */
	trans = btrfs_attach_transaction_barrier(root);
	if (IS_ERR(trans)) {
		/* no transaction, don't bother */
		if (PTR_ERR(trans) == -ENOENT)
			return 0;
		return PTR_ERR(trans);
	}
	return btrfs_commit_transaction(trans);
}