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
struct inode {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * inode_lock; } ;
struct f2fs_inode_info {int /*<<< orphan*/  inmem_ilist; scalar_t__* i_gc_failures; int /*<<< orphan*/  inmem_lock; int /*<<< orphan*/  inmem_pages; } ;

/* Variables and functions */
 size_t ATOMIC_FILE ; 
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_ATOMIC_FILE ; 
 size_t GC_FAILURE_ATOMIC ; 
 int /*<<< orphan*/  __revoke_inmem_pages (struct inode*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_dec_atomic_write (struct inode*) ; 

void f2fs_drop_inmem_pages(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct f2fs_inode_info *fi = F2FS_I(inode);

	while (!list_empty(&fi->inmem_pages)) {
		mutex_lock(&fi->inmem_lock);
		__revoke_inmem_pages(inode, &fi->inmem_pages,
						true, false, true);
		mutex_unlock(&fi->inmem_lock);
	}

	clear_inode_flag(inode, FI_ATOMIC_FILE);
	fi->i_gc_failures[GC_FAILURE_ATOMIC] = 0;
	stat_dec_atomic_write(inode);

	spin_lock(&sbi->inode_lock[ATOMIC_FILE]);
	if (!list_empty(&fi->inmem_ilist))
		list_del_init(&fi->inmem_ilist);
	spin_unlock(&sbi->inode_lock[ATOMIC_FILE]);
}