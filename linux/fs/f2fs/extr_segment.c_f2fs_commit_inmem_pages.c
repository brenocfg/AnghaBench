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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_inode_info {int /*<<< orphan*/ * i_gc_rwsem; int /*<<< orphan*/  inmem_lock; } ;

/* Variables and functions */
 struct f2fs_inode_info* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_ATOMIC_COMMIT ; 
 size_t WRITE ; 
 int __f2fs_commit_inmem_pages (struct inode*) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int f2fs_commit_inmem_pages(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct f2fs_inode_info *fi = F2FS_I(inode);
	int err;

	f2fs_balance_fs(sbi, true);

	down_write(&fi->i_gc_rwsem[WRITE]);

	f2fs_lock_op(sbi);
	set_inode_flag(inode, FI_ATOMIC_COMMIT);

	mutex_lock(&fi->inmem_lock);
	err = __f2fs_commit_inmem_pages(inode);
	mutex_unlock(&fi->inmem_lock);

	clear_inode_flag(inode, FI_ATOMIC_COMMIT);

	f2fs_unlock_op(sbi);
	up_write(&fi->i_gc_rwsem[WRITE]);

	return err;
}