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
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  root_item; int /*<<< orphan*/  root_key; TYPE_1__* node; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {struct btrfs_root* tree_root; } ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ btrfs_root_bytenr (int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_root_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_set_root_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int btrfs_update_root (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_cowonly_root(struct btrfs_trans_handle *trans,
			       struct btrfs_root *root)
{
	int ret;
	u64 old_root_bytenr;
	u64 old_root_used;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_root *tree_root = fs_info->tree_root;

	old_root_used = btrfs_root_used(&root->root_item);

	while (1) {
		old_root_bytenr = btrfs_root_bytenr(&root->root_item);
		if (old_root_bytenr == root->node->start &&
		    old_root_used == btrfs_root_used(&root->root_item))
			break;

		btrfs_set_root_node(&root->root_item, root->node);
		ret = btrfs_update_root(trans, tree_root,
					&root->root_key,
					&root->root_item);
		if (ret)
			return ret;

		old_root_used = btrfs_root_used(&root->root_item);
	}

	return 0;
}