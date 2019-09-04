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
struct posix_acl {int dummy; } ;
struct ocfs2_super {int s_mount_opt; } ;
struct ocfs2_lock_holder {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_xattr_sem; } ;

/* Variables and functions */
 struct posix_acl* ERR_PTR (int) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_MOUNT_POSIX_ACL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct posix_acl* ocfs2_get_acl_nolock (struct inode*,int,struct buffer_head*) ; 
 int ocfs2_inode_lock_tracker (struct inode*,struct buffer_head**,int /*<<< orphan*/ ,struct ocfs2_lock_holder*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock_tracker (struct inode*,int /*<<< orphan*/ ,struct ocfs2_lock_holder*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct posix_acl *ocfs2_iop_get_acl(struct inode *inode, int type)
{
	struct ocfs2_super *osb;
	struct buffer_head *di_bh = NULL;
	struct posix_acl *acl;
	int had_lock;
	struct ocfs2_lock_holder oh;

	osb = OCFS2_SB(inode->i_sb);
	if (!(osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACL))
		return NULL;

	had_lock = ocfs2_inode_lock_tracker(inode, &di_bh, 0, &oh);
	if (had_lock < 0)
		return ERR_PTR(had_lock);

	down_read(&OCFS2_I(inode)->ip_xattr_sem);
	acl = ocfs2_get_acl_nolock(inode, type, di_bh);
	up_read(&OCFS2_I(inode)->ip_xattr_sem);

	ocfs2_inode_unlock_tracker(inode, 0, &oh, had_lock);
	brelse(di_bh);
	return acl;
}