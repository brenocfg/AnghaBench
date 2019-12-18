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
struct ocfs2_inode_info {int /*<<< orphan*/  ip_flags; scalar_t__ ip_blkno; } ;
struct inode {int i_state; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 int I_NEW ; 
 int I_WILL_FREE ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_drop_inode (unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_inode_now (struct inode*,int) ; 

int ocfs2_drop_inode(struct inode *inode)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);

	trace_ocfs2_drop_inode((unsigned long long)oi->ip_blkno,
				inode->i_nlink, oi->ip_flags);

	assert_spin_locked(&inode->i_lock);
	inode->i_state |= I_WILL_FREE;
	spin_unlock(&inode->i_lock);
	write_inode_now(inode, 1);
	spin_lock(&inode->i_lock);
	WARN_ON(inode->i_state & I_NEW);
	inode->i_state &= ~I_WILL_FREE;

	return 1;
}