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
struct nilfs_transaction_info {int dummy; } ;
struct nilfs_mdt_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 struct nilfs_mdt_info* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  __nilfs_mark_inode_dirty (struct inode*,int) ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nilfs_transaction_begin (int /*<<< orphan*/ ,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_transaction_commit (int /*<<< orphan*/ ) ; 

void nilfs_dirty_inode(struct inode *inode, int flags)
{
	struct nilfs_transaction_info ti;
	struct nilfs_mdt_info *mdi = NILFS_MDT(inode);

	if (is_bad_inode(inode)) {
		nilfs_msg(inode->i_sb, KERN_WARNING,
			  "tried to mark bad_inode dirty. ignored.");
		dump_stack();
		return;
	}
	if (mdi) {
		nilfs_mdt_mark_dirty(inode);
		return;
	}
	nilfs_transaction_begin(inode->i_sb, &ti, 0);
	__nilfs_mark_inode_dirty(inode, flags);
	nilfs_transaction_commit(inode->i_sb); /* never fails */
}