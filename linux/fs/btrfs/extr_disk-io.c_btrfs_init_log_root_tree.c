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
struct btrfs_fs_info {struct btrfs_root* log_root_tree; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 int PTR_ERR (struct btrfs_root*) ; 
 int /*<<< orphan*/  WARN_ON (struct btrfs_root*) ; 
 struct btrfs_root* alloc_log_tree (struct btrfs_trans_handle*,struct btrfs_fs_info*) ; 

int btrfs_init_log_root_tree(struct btrfs_trans_handle *trans,
			     struct btrfs_fs_info *fs_info)
{
	struct btrfs_root *log_root;

	log_root = alloc_log_tree(trans, fs_info);
	if (IS_ERR(log_root))
		return PTR_ERR(log_root);
	WARN_ON(fs_info->log_root_tree);
	fs_info->log_root_tree = log_root;
	return 0;
}