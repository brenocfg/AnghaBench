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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_inode_info {struct inode vfs_inode; int /*<<< orphan*/  i_dir_level; int /*<<< orphan*/  i_xattr_sem; int /*<<< orphan*/  i_mmap_sem; int /*<<< orphan*/ * i_gc_rwsem; int /*<<< orphan*/  inmem_lock; int /*<<< orphan*/  inmem_pages; int /*<<< orphan*/  inmem_ilist; int /*<<< orphan*/  gdirty_list; int /*<<< orphan*/  dirty_list; int /*<<< orphan*/  i_sem; int /*<<< orphan*/  dirty_pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir_level; } ;

/* Variables and functions */
 TYPE_1__* F2FS_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_F2FS_ZERO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_inode_cachep ; 
 int /*<<< orphan*/  init_once (void*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct f2fs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct inode *f2fs_alloc_inode(struct super_block *sb)
{
	struct f2fs_inode_info *fi;

	fi = kmem_cache_alloc(f2fs_inode_cachep, GFP_F2FS_ZERO);
	if (!fi)
		return NULL;

	init_once((void *) fi);

	/* Initialize f2fs-specific inode info */
	atomic_set(&fi->dirty_pages, 0);
	init_rwsem(&fi->i_sem);
	INIT_LIST_HEAD(&fi->dirty_list);
	INIT_LIST_HEAD(&fi->gdirty_list);
	INIT_LIST_HEAD(&fi->inmem_ilist);
	INIT_LIST_HEAD(&fi->inmem_pages);
	mutex_init(&fi->inmem_lock);
	init_rwsem(&fi->i_gc_rwsem[READ]);
	init_rwsem(&fi->i_gc_rwsem[WRITE]);
	init_rwsem(&fi->i_mmap_sem);
	init_rwsem(&fi->i_xattr_sem);

	/* Will be used by directory only */
	fi->i_dir_level = F2FS_SB(sb)->dir_level;

	return &fi->vfs_inode;
}