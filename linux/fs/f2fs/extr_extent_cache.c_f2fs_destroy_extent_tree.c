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
struct inode {int /*<<< orphan*/  i_ino; scalar_t__ i_nlink; } ;
struct f2fs_sb_info {int /*<<< orphan*/  extent_tree_lock; int /*<<< orphan*/  total_ext_tree; int /*<<< orphan*/  extent_tree_root; int /*<<< orphan*/  total_zombie_tree; int /*<<< orphan*/  zombie_list; } ;
struct extent_tree {int /*<<< orphan*/  node_cnt; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct extent_tree* extent_tree; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_tree_slab ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,scalar_t__) ; 
 unsigned int f2fs_destroy_extent_node (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct extent_tree*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_destroy_extent_tree (struct inode*,unsigned int) ; 

void f2fs_destroy_extent_tree(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct extent_tree *et = F2FS_I(inode)->extent_tree;
	unsigned int node_cnt = 0;

	if (!et)
		return;

	if (inode->i_nlink && !is_bad_inode(inode) &&
					atomic_read(&et->node_cnt)) {
		mutex_lock(&sbi->extent_tree_lock);
		list_add_tail(&et->list, &sbi->zombie_list);
		atomic_inc(&sbi->total_zombie_tree);
		mutex_unlock(&sbi->extent_tree_lock);
		return;
	}

	/* free all extent info belong to this extent tree */
	node_cnt = f2fs_destroy_extent_node(inode);

	/* delete extent tree entry in radix tree */
	mutex_lock(&sbi->extent_tree_lock);
	f2fs_bug_on(sbi, atomic_read(&et->node_cnt));
	radix_tree_delete(&sbi->extent_tree_root, inode->i_ino);
	kmem_cache_free(extent_tree_slab, et);
	atomic_dec(&sbi->total_ext_tree);
	mutex_unlock(&sbi->extent_tree_lock);

	F2FS_I(inode)->extent_tree = NULL;

	trace_f2fs_destroy_extent_tree(inode, node_cnt);
}