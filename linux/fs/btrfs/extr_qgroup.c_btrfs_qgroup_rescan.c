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
struct btrfs_fs_info {int /*<<< orphan*/  qgroup_rescan_work; int /*<<< orphan*/  qgroup_rescan_workers; int /*<<< orphan*/  qgroup_flags; int /*<<< orphan*/  fs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_QGROUP_STATUS_FLAG_RESCAN ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qgroup_rescan_init (struct btrfs_fs_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qgroup_rescan_zero_tracking (struct btrfs_fs_info*) ; 

int
btrfs_qgroup_rescan(struct btrfs_fs_info *fs_info)
{
	int ret = 0;
	struct btrfs_trans_handle *trans;

	ret = qgroup_rescan_init(fs_info, 0, 1);
	if (ret)
		return ret;

	/*
	 * We have set the rescan_progress to 0, which means no more
	 * delayed refs will be accounted by btrfs_qgroup_account_ref.
	 * However, btrfs_qgroup_account_ref may be right after its call
	 * to btrfs_find_all_roots, in which case it would still do the
	 * accounting.
	 * To solve this, we're committing the transaction, which will
	 * ensure we run all delayed refs and only after that, we are
	 * going to clear all tracking information for a clean start.
	 */

	trans = btrfs_join_transaction(fs_info->fs_root);
	if (IS_ERR(trans)) {
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_RESCAN;
		return PTR_ERR(trans);
	}
	ret = btrfs_commit_transaction(trans);
	if (ret) {
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_RESCAN;
		return ret;
	}

	qgroup_rescan_zero_tracking(fs_info);

	btrfs_queue_work(fs_info->qgroup_rescan_workers,
			 &fs_info->qgroup_rescan_work);

	return 0;
}