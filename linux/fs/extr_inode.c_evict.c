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
struct super_operations {int /*<<< orphan*/  (* evict_inode ) (struct inode*) ;} ;
struct inode {int i_state; int /*<<< orphan*/  i_lock; scalar_t__ i_cdev; int /*<<< orphan*/  i_mode; scalar_t__ i_bdev; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_io_list; int /*<<< orphan*/  i_lru; TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct super_operations* s_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int I_CLEAR ; 
 int I_FREEING ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __I_NEW ; 
 int /*<<< orphan*/  bd_forget (struct inode*) ; 
 int /*<<< orphan*/  cd_forget (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  destroy_inode (struct inode*) ; 
 int /*<<< orphan*/  inode_io_list_del (struct inode*) ; 
 int /*<<< orphan*/  inode_sb_list_del (struct inode*) ; 
 int /*<<< orphan*/  inode_wait_for_writeback (struct inode*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void evict(struct inode *inode)
{
	const struct super_operations *op = inode->i_sb->s_op;

	BUG_ON(!(inode->i_state & I_FREEING));
	BUG_ON(!list_empty(&inode->i_lru));

	if (!list_empty(&inode->i_io_list))
		inode_io_list_del(inode);

	inode_sb_list_del(inode);

	/*
	 * Wait for flusher thread to be done with the inode so that filesystem
	 * does not start destroying it while writeback is still running. Since
	 * the inode has I_FREEING set, flusher thread won't start new work on
	 * the inode.  We just have to wait for running writeback to finish.
	 */
	inode_wait_for_writeback(inode);

	if (op->evict_inode) {
		op->evict_inode(inode);
	} else {
		truncate_inode_pages_final(&inode->i_data);
		clear_inode(inode);
	}
	if (S_ISBLK(inode->i_mode) && inode->i_bdev)
		bd_forget(inode);
	if (S_ISCHR(inode->i_mode) && inode->i_cdev)
		cd_forget(inode);

	remove_inode_hash(inode);

	spin_lock(&inode->i_lock);
	wake_up_bit(&inode->i_state, __I_NEW);
	BUG_ON(inode->i_state != (I_FREEING | I_CLEAR));
	spin_unlock(&inode->i_lock);

	destroy_inode(inode);
}