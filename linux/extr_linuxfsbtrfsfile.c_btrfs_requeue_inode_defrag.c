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
struct inode_defrag {int dummy; } ;
struct btrfs_inode {TYPE_1__* root; } ;
struct btrfs_fs_info {int /*<<< orphan*/  defrag_inodes_lock; } ;
struct TYPE_2__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int __btrfs_add_inode_defrag (struct btrfs_inode*,struct inode_defrag*) ; 
 int /*<<< orphan*/  __need_auto_defrag (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_inode_defrag_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct inode_defrag*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_requeue_inode_defrag(struct btrfs_inode *inode,
				       struct inode_defrag *defrag)
{
	struct btrfs_fs_info *fs_info = inode->root->fs_info;
	int ret;

	if (!__need_auto_defrag(fs_info))
		goto out;

	/*
	 * Here we don't check the IN_DEFRAG flag, because we need merge
	 * them together.
	 */
	spin_lock(&fs_info->defrag_inodes_lock);
	ret = __btrfs_add_inode_defrag(inode, defrag);
	spin_unlock(&fs_info->defrag_inodes_lock);
	if (ret)
		goto out;
	return;
out:
	kmem_cache_free(btrfs_inode_defrag_cachep, defrag);
}