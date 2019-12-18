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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_rw_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_two_nondirectories (struct inode*,struct inode*) ; 

void ocfs2_reflink_inodes_unlock(struct inode *s_inode,
				 struct buffer_head *s_bh,
				 struct inode *t_inode,
				 struct buffer_head *t_bh)
{
	ocfs2_inode_unlock(s_inode, 1);
	ocfs2_rw_unlock(s_inode, 1);
	brelse(s_bh);
	if (s_inode != t_inode) {
		ocfs2_inode_unlock(t_inode, 1);
		ocfs2_rw_unlock(t_inode, 1);
		brelse(t_bh);
	}
	unlock_two_nondirectories(s_inode, t_inode);
}