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
struct btrfs_fs_info {int /*<<< orphan*/ * log_root_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_log_tree (struct btrfs_trans_handle*,int /*<<< orphan*/ *) ; 

int btrfs_free_log_root_tree(struct btrfs_trans_handle *trans,
			     struct btrfs_fs_info *fs_info)
{
	if (fs_info->log_root_tree) {
		free_log_tree(trans, fs_info->log_root_tree);
		fs_info->log_root_tree = NULL;
	}
	return 0;
}