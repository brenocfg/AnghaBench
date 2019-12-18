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
struct btrfs_root_item {int dummy; } ;
struct btrfs_root {int log_transid; int /*<<< orphan*/  root_key; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  log_root_tree; } ;

/* Variables and functions */
 int btrfs_insert_root (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct btrfs_root_item*) ; 
 int btrfs_update_root (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct btrfs_root_item*) ; 

__attribute__((used)) static int update_log_root(struct btrfs_trans_handle *trans,
			   struct btrfs_root *log,
			   struct btrfs_root_item *root_item)
{
	struct btrfs_fs_info *fs_info = log->fs_info;
	int ret;

	if (log->log_transid == 1) {
		/* insert root item on the first sync */
		ret = btrfs_insert_root(trans, fs_info->log_root_tree,
				&log->root_key, root_item);
	} else {
		ret = btrfs_update_root(trans, fs_info->log_root_tree,
				&log->root_key, root_item);
	}
	return ret;
}