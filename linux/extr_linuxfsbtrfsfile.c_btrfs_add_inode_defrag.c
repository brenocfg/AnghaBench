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
typedef  int /*<<< orphan*/  u64 ;
struct inode_defrag {int /*<<< orphan*/  root; int /*<<< orphan*/  transid; int /*<<< orphan*/  ino; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; int /*<<< orphan*/  last_trans; struct btrfs_fs_info* fs_info; } ;
struct btrfs_inode {int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;
struct btrfs_fs_info {int /*<<< orphan*/  defrag_inodes_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_INODE_IN_DEFRAG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int __btrfs_add_inode_defrag (struct btrfs_inode*,struct inode_defrag*) ; 
 int /*<<< orphan*/  __need_auto_defrag (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_inode_defrag_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct inode_defrag*) ; 
 struct inode_defrag* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_add_inode_defrag(struct btrfs_trans_handle *trans,
			   struct btrfs_inode *inode)
{
	struct btrfs_root *root = inode->root;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct inode_defrag *defrag;
	u64 transid;
	int ret;

	if (!__need_auto_defrag(fs_info))
		return 0;

	if (test_bit(BTRFS_INODE_IN_DEFRAG, &inode->runtime_flags))
		return 0;

	if (trans)
		transid = trans->transid;
	else
		transid = inode->root->last_trans;

	defrag = kmem_cache_zalloc(btrfs_inode_defrag_cachep, GFP_NOFS);
	if (!defrag)
		return -ENOMEM;

	defrag->ino = btrfs_ino(inode);
	defrag->transid = transid;
	defrag->root = root->root_key.objectid;

	spin_lock(&fs_info->defrag_inodes_lock);
	if (!test_bit(BTRFS_INODE_IN_DEFRAG, &inode->runtime_flags)) {
		/*
		 * If we set IN_DEFRAG flag and evict the inode from memory,
		 * and then re-read this inode, this new inode doesn't have
		 * IN_DEFRAG flag. At the case, we may find the existed defrag.
		 */
		ret = __btrfs_add_inode_defrag(inode, defrag);
		if (ret)
			kmem_cache_free(btrfs_inode_defrag_cachep, defrag);
	} else {
		kmem_cache_free(btrfs_inode_defrag_cachep, defrag);
	}
	spin_unlock(&fs_info->defrag_inodes_lock);
	return 0;
}