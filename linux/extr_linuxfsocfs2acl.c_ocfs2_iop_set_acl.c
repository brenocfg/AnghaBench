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
typedef  int /*<<< orphan*/  umode_t ;
struct posix_acl {int dummy; } ;
struct ocfs2_lock_holder {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int ocfs2_acl_set_mode (struct inode*,struct buffer_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock_tracker (struct inode*,struct buffer_head**,int,struct ocfs2_lock_holder*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock_tracker (struct inode*,int,struct ocfs2_lock_holder*,int) ; 
 int ocfs2_set_acl (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,int,struct posix_acl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int posix_acl_update_mode (struct inode*,int /*<<< orphan*/ *,struct posix_acl**) ; 

int ocfs2_iop_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	struct buffer_head *bh = NULL;
	int status, had_lock;
	struct ocfs2_lock_holder oh;

	had_lock = ocfs2_inode_lock_tracker(inode, &bh, 1, &oh);
	if (had_lock < 0)
		return had_lock;
	if (type == ACL_TYPE_ACCESS && acl) {
		umode_t mode;

		status = posix_acl_update_mode(inode, &mode, &acl);
		if (status)
			goto unlock;

		status = ocfs2_acl_set_mode(inode, bh, NULL, mode);
		if (status)
			goto unlock;
	}
	status = ocfs2_set_acl(NULL, inode, bh, type, acl, NULL, NULL);
unlock:
	ocfs2_inode_unlock_tracker(inode, 1, &oh, had_lock);
	brelse(bh);
	return status;
}