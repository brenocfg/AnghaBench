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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  commit_root; int /*<<< orphan*/  node; int /*<<< orphan*/  dirty_list; int /*<<< orphan*/  root_key; } ;
struct btrfs_fs_info {int /*<<< orphan*/  qgroup_ioctl_lock; int /*<<< orphan*/  qgroup_lock; int /*<<< orphan*/  qgroup_flags; struct btrfs_root* quota_root; int /*<<< orphan*/  flags; int /*<<< orphan*/  tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int /*<<< orphan*/  BTRFS_QGROUP_STATUS_FLAG_ON ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 int btrfs_clean_quota_tree (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_clean_tree_block (int /*<<< orphan*/ ) ; 
 int btrfs_del_root (struct btrfs_trans_handle*,int /*<<< orphan*/ *) ; 
 int btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_free_qgroup_config (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_free_tree_block (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_qgroup_wait_for_completion (struct btrfs_fs_info*,int) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_tree_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_tree_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_extent_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btrfs_root*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_quota_disable(struct btrfs_fs_info *fs_info)
{
	struct btrfs_root *quota_root;
	struct btrfs_trans_handle *trans = NULL;
	int ret = 0;

	mutex_lock(&fs_info->qgroup_ioctl_lock);
	if (!fs_info->quota_root)
		goto out;

	/*
	 * 1 For the root item
	 *
	 * We should also reserve enough items for the quota tree deletion in
	 * btrfs_clean_quota_tree but this is not done.
	 */
	trans = btrfs_start_transaction(fs_info->tree_root, 1);
	if (IS_ERR(trans)) {
		ret = PTR_ERR(trans);
		goto out;
	}

	clear_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags);
	btrfs_qgroup_wait_for_completion(fs_info, false);
	spin_lock(&fs_info->qgroup_lock);
	quota_root = fs_info->quota_root;
	fs_info->quota_root = NULL;
	fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_ON;
	spin_unlock(&fs_info->qgroup_lock);

	btrfs_free_qgroup_config(fs_info);

	ret = btrfs_clean_quota_tree(trans, quota_root);
	if (ret) {
		btrfs_abort_transaction(trans, ret);
		goto end_trans;
	}

	ret = btrfs_del_root(trans, &quota_root->root_key);
	if (ret) {
		btrfs_abort_transaction(trans, ret);
		goto end_trans;
	}

	list_del(&quota_root->dirty_list);

	btrfs_tree_lock(quota_root->node);
	btrfs_clean_tree_block(quota_root->node);
	btrfs_tree_unlock(quota_root->node);
	btrfs_free_tree_block(trans, quota_root, quota_root->node, 0, 1);

	free_extent_buffer(quota_root->node);
	free_extent_buffer(quota_root->commit_root);
	kfree(quota_root);

end_trans:
	ret = btrfs_end_transaction(trans);
out:
	mutex_unlock(&fs_info->qgroup_ioctl_lock);
	return ret;
}