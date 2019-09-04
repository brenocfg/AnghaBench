#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_inode_item {int dummy; } ;
struct TYPE_4__ {struct btrfs_inode_item inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  objectid; int /*<<< orphan*/  offset; } ;
struct btrfs_root {int log_transid_committed; scalar_t__ last_log_commit; scalar_t__ log_transid; struct btrfs_root* log_root; int /*<<< orphan*/  node; TYPE_2__ root_item; TYPE_1__ root_key; int /*<<< orphan*/  last_trans; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  nodesize; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct btrfs_root*) ; 
 int PTR_ERR (struct btrfs_root*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  WARN_ON (struct btrfs_root*) ; 
 struct btrfs_root* alloc_log_tree (struct btrfs_trans_handle*,struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_set_root_node (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_generation (struct btrfs_inode_item*,int) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_mode (struct btrfs_inode_item*,int) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_nbytes (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_nlink (struct btrfs_inode_item*,int) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_size (struct btrfs_inode_item*,int) ; 

int btrfs_add_log_tree(struct btrfs_trans_handle *trans,
		       struct btrfs_root *root)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_root *log_root;
	struct btrfs_inode_item *inode_item;

	log_root = alloc_log_tree(trans, fs_info);
	if (IS_ERR(log_root))
		return PTR_ERR(log_root);

	log_root->last_trans = trans->transid;
	log_root->root_key.offset = root->root_key.objectid;

	inode_item = &log_root->root_item.inode;
	btrfs_set_stack_inode_generation(inode_item, 1);
	btrfs_set_stack_inode_size(inode_item, 3);
	btrfs_set_stack_inode_nlink(inode_item, 1);
	btrfs_set_stack_inode_nbytes(inode_item,
				     fs_info->nodesize);
	btrfs_set_stack_inode_mode(inode_item, S_IFDIR | 0755);

	btrfs_set_root_node(&log_root->root_item, log_root->node);

	WARN_ON(root->log_root);
	root->log_root = log_root;
	root->log_transid = 0;
	root->log_transid_committed = -1;
	root->last_log_commit = 0;
	return 0;
}