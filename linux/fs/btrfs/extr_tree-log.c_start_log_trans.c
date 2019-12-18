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
struct btrfs_root {scalar_t__ log_start_pid; int log_transid; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/ * log_ctxs; int /*<<< orphan*/  log_writers; int /*<<< orphan*/  log_batch; int /*<<< orphan*/  state; scalar_t__ log_root; struct btrfs_fs_info* fs_info; } ;
struct btrfs_log_ctx {int log_transid; int /*<<< orphan*/  list; } ;
struct btrfs_fs_info {int /*<<< orphan*/  tree_log_mutex; int /*<<< orphan*/  log_root_tree; } ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_MULTI_LOG_TASKS ; 
 int EAGAIN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int btrfs_add_log_tree (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int btrfs_init_log_root_tree (struct btrfs_trans_handle*,struct btrfs_fs_info*) ; 
 scalar_t__ btrfs_need_log_full_commit (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_log_trans(struct btrfs_trans_handle *trans,
			   struct btrfs_root *root,
			   struct btrfs_log_ctx *ctx)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	int ret = 0;

	mutex_lock(&root->log_mutex);

	if (root->log_root) {
		if (btrfs_need_log_full_commit(trans)) {
			ret = -EAGAIN;
			goto out;
		}

		if (!root->log_start_pid) {
			clear_bit(BTRFS_ROOT_MULTI_LOG_TASKS, &root->state);
			root->log_start_pid = current->pid;
		} else if (root->log_start_pid != current->pid) {
			set_bit(BTRFS_ROOT_MULTI_LOG_TASKS, &root->state);
		}
	} else {
		mutex_lock(&fs_info->tree_log_mutex);
		if (!fs_info->log_root_tree)
			ret = btrfs_init_log_root_tree(trans, fs_info);
		mutex_unlock(&fs_info->tree_log_mutex);
		if (ret)
			goto out;

		ret = btrfs_add_log_tree(trans, root);
		if (ret)
			goto out;

		clear_bit(BTRFS_ROOT_MULTI_LOG_TASKS, &root->state);
		root->log_start_pid = current->pid;
	}

	atomic_inc(&root->log_batch);
	atomic_inc(&root->log_writers);
	if (ctx) {
		int index = root->log_transid % 2;
		list_add_tail(&ctx->list, &root->log_ctxs[index]);
		ctx->log_transid = root->log_transid;
	}

out:
	mutex_unlock(&root->log_mutex);
	return ret;
}