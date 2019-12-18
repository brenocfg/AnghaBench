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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {struct btrfs_root* log_root; } ;
struct btrfs_inode {int /*<<< orphan*/  log_mutex; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 int btrfs_del_inode_ref (struct btrfs_trans_handle*,struct btrfs_root*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_end_log_trans (struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_set_log_full_commit (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  inode_logged (struct btrfs_trans_handle*,struct btrfs_inode*) ; 
 int join_running_log_trans (struct btrfs_root*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int btrfs_del_inode_ref_in_log(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root,
			       const char *name, int name_len,
			       struct btrfs_inode *inode, u64 dirid)
{
	struct btrfs_root *log;
	u64 index;
	int ret;

	if (!inode_logged(trans, inode))
		return 0;

	ret = join_running_log_trans(root);
	if (ret)
		return 0;
	log = root->log_root;
	mutex_lock(&inode->log_mutex);

	ret = btrfs_del_inode_ref(trans, log, name, name_len, btrfs_ino(inode),
				  dirid, &index);
	mutex_unlock(&inode->log_mutex);
	if (ret == -ENOSPC) {
		btrfs_set_log_full_commit(trans);
		ret = 0;
	} else if (ret < 0 && ret != -ENOENT)
		btrfs_abort_transaction(trans, ret);
	btrfs_end_log_trans(root);

	return ret;
}