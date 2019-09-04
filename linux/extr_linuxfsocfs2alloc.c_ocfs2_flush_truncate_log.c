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
struct ocfs2_super {struct inode* osb_tl_inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int __ocfs2_flush_truncate_log (struct ocfs2_super*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

int ocfs2_flush_truncate_log(struct ocfs2_super *osb)
{
	int status;
	struct inode *tl_inode = osb->osb_tl_inode;

	inode_lock(tl_inode);
	status = __ocfs2_flush_truncate_log(osb);
	inode_unlock(tl_inode);

	return status;
}