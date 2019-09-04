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
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  cleanup_work_sem; int /*<<< orphan*/  cleaner_kthread; int /*<<< orphan*/  cleaner_mutex; struct btrfs_root* tree_root; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int btrfs_commit_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_run_delayed_iputs (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

int btrfs_commit_super(struct btrfs_fs_info *fs_info)
{
	struct btrfs_root *root = fs_info->tree_root;
	struct btrfs_trans_handle *trans;

	mutex_lock(&fs_info->cleaner_mutex);
	btrfs_run_delayed_iputs(fs_info);
	mutex_unlock(&fs_info->cleaner_mutex);
	wake_up_process(fs_info->cleaner_kthread);

	/* wait until ongoing cleanup work done */
	down_write(&fs_info->cleanup_work_sem);
	up_write(&fs_info->cleanup_work_sem);

	trans = btrfs_join_transaction(root);
	if (IS_ERR(trans))
		return PTR_ERR(trans);
	return btrfs_commit_transaction(trans);
}