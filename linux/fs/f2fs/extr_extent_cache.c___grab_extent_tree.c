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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct f2fs_sb_info {int /*<<< orphan*/  extent_tree_lock; int /*<<< orphan*/  total_zombie_tree; int /*<<< orphan*/  total_ext_tree; int /*<<< orphan*/  extent_tree_root; } ;
struct extent_tree {int /*<<< orphan*/  list; int /*<<< orphan*/  node_cnt; int /*<<< orphan*/  lock; int /*<<< orphan*/ * cached_en; int /*<<< orphan*/  root; int /*<<< orphan*/  ino; } ;
typedef  int /*<<< orphan*/  nid_t ;
struct TYPE_2__ {struct extent_tree* extent_tree; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_tree_slab ; 
 struct extent_tree* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct extent_tree*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct extent_tree*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct extent_tree* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct extent_tree *__grab_extent_tree(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct extent_tree *et;
	nid_t ino = inode->i_ino;

	mutex_lock(&sbi->extent_tree_lock);
	et = radix_tree_lookup(&sbi->extent_tree_root, ino);
	if (!et) {
		et = f2fs_kmem_cache_alloc(extent_tree_slab, GFP_NOFS);
		f2fs_radix_tree_insert(&sbi->extent_tree_root, ino, et);
		memset(et, 0, sizeof(struct extent_tree));
		et->ino = ino;
		et->root = RB_ROOT_CACHED;
		et->cached_en = NULL;
		rwlock_init(&et->lock);
		INIT_LIST_HEAD(&et->list);
		atomic_set(&et->node_cnt, 0);
		atomic_inc(&sbi->total_ext_tree);
	} else {
		atomic_dec(&sbi->total_zombie_tree);
		list_del_init(&et->list);
	}
	mutex_unlock(&sbi->extent_tree_lock);

	/* never died until evict_inode */
	F2FS_I(inode)->extent_tree = et;

	return et;
}