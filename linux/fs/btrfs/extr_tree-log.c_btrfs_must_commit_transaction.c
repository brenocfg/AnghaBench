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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_inode {scalar_t__ last_unlink_trans; int /*<<< orphan*/  log_mutex; TYPE_1__* root; } ;
struct btrfs_fs_info {scalar_t__ last_trans_committed; } ;
struct TYPE_2__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_set_log_full_commit (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool btrfs_must_commit_transaction(struct btrfs_trans_handle *trans,
					  struct btrfs_inode *inode)
{
	struct btrfs_fs_info *fs_info = inode->root->fs_info;
	bool ret = false;

	mutex_lock(&inode->log_mutex);
	if (inode->last_unlink_trans > fs_info->last_trans_committed) {
		/*
		 * Make sure any commits to the log are forced to be full
		 * commits.
		 */
		btrfs_set_log_full_commit(trans);
		ret = true;
	}
	mutex_unlock(&inode->log_mutex);

	return ret;
}