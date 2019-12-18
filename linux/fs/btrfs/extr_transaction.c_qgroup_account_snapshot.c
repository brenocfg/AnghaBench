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
struct btrfs_trans_handle {int /*<<< orphan*/  transaction; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct btrfs_fs_info* fs_info; } ;
struct btrfs_qgroup_inherit {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_log_mutex; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int /*<<< orphan*/  btrfs_handle_fs_error (struct btrfs_fs_info*,int,char*) ; 
 int btrfs_qgroup_account_extents (struct btrfs_trans_handle*) ; 
 int btrfs_qgroup_inherit (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_qgroup_inherit*) ; 
 int btrfs_write_and_wait_transaction (struct btrfs_trans_handle*) ; 
 int commit_cowonly_roots (struct btrfs_trans_handle*) ; 
 int commit_fs_roots (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_root_in_trans (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 int /*<<< orphan*/  switch_commit_roots (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qgroup_account_snapshot(struct btrfs_trans_handle *trans,
				   struct btrfs_root *src,
				   struct btrfs_root *parent,
				   struct btrfs_qgroup_inherit *inherit,
				   u64 dst_objectid)
{
	struct btrfs_fs_info *fs_info = src->fs_info;
	int ret;

	/*
	 * Save some performance in the case that qgroups are not
	 * enabled. If this check races with the ioctl, rescan will
	 * kick in anyway.
	 */
	if (!test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags))
		return 0;

	/*
	 * Ensure dirty @src will be committed.  Or, after coming
	 * commit_fs_roots() and switch_commit_roots(), any dirty but not
	 * recorded root will never be updated again, causing an outdated root
	 * item.
	 */
	record_root_in_trans(trans, src, 1);

	/*
	 * We are going to commit transaction, see btrfs_commit_transaction()
	 * comment for reason locking tree_log_mutex
	 */
	mutex_lock(&fs_info->tree_log_mutex);

	ret = commit_fs_roots(trans);
	if (ret)
		goto out;
	ret = btrfs_qgroup_account_extents(trans);
	if (ret < 0)
		goto out;

	/* Now qgroup are all updated, we can inherit it to new qgroups */
	ret = btrfs_qgroup_inherit(trans, src->root_key.objectid, dst_objectid,
				   inherit);
	if (ret < 0)
		goto out;

	/*
	 * Now we do a simplified commit transaction, which will:
	 * 1) commit all subvolume and extent tree
	 *    To ensure all subvolume and extent tree have a valid
	 *    commit_root to accounting later insert_dir_item()
	 * 2) write all btree blocks onto disk
	 *    This is to make sure later btree modification will be cowed
	 *    Or commit_root can be populated and cause wrong qgroup numbers
	 * In this simplified commit, we don't really care about other trees
	 * like chunk and root tree, as they won't affect qgroup.
	 * And we don't write super to avoid half committed status.
	 */
	ret = commit_cowonly_roots(trans);
	if (ret)
		goto out;
	switch_commit_roots(trans->transaction);
	ret = btrfs_write_and_wait_transaction(trans);
	if (ret)
		btrfs_handle_fs_error(fs_info, ret,
			"Error while writing out transaction for qgroup");

out:
	mutex_unlock(&fs_info->tree_log_mutex);

	/*
	 * Force parent root to be updated, as we recorded it before so its
	 * last_trans == cur_transid.
	 * Or it won't be committed again onto disk after later
	 * insert_dir_item()
	 */
	if (!ret)
		record_root_in_trans(trans, parent, 1);
	return ret;
}