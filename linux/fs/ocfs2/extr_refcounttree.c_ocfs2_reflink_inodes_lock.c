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
struct ocfs2_inode_info {scalar_t__ ip_blkno; } ;
struct inode {scalar_t__ i_ino; } ;
struct buffer_head {scalar_t__ i_ino; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOLCK ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OI_LS_REFLINK_TARGET ; 
 int /*<<< orphan*/  brelse (struct inode*) ; 
 int /*<<< orphan*/  lock_two_nondirectories (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_inode_lock_nested (struct inode*,struct inode**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int ocfs2_rw_lock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_rw_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  swap (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  trace_ocfs2_double_lock (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  trace_ocfs2_double_lock_end (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  unlock_two_nondirectories (struct inode*,struct inode*) ; 

int ocfs2_reflink_inodes_lock(struct inode *s_inode,
			      struct buffer_head **bh_s,
			      struct inode *t_inode,
			      struct buffer_head **bh_t)
{
	struct inode *inode1 = s_inode;
	struct inode *inode2 = t_inode;
	struct ocfs2_inode_info *oi1;
	struct ocfs2_inode_info *oi2;
	struct buffer_head *bh1 = NULL;
	struct buffer_head *bh2 = NULL;
	bool same_inode = (s_inode == t_inode);
	bool need_swap = (inode1->i_ino > inode2->i_ino);
	int status;

	/* First grab the VFS and rw locks. */
	lock_two_nondirectories(s_inode, t_inode);
	if (need_swap)
		swap(inode1, inode2);

	status = ocfs2_rw_lock(inode1, 1);
	if (status) {
		mlog_errno(status);
		goto out_i1;
	}
	if (!same_inode) {
		status = ocfs2_rw_lock(inode2, 1);
		if (status) {
			mlog_errno(status);
			goto out_i2;
		}
	}

	/* Now go for the cluster locks */
	oi1 = OCFS2_I(inode1);
	oi2 = OCFS2_I(inode2);

	trace_ocfs2_double_lock((unsigned long long)oi1->ip_blkno,
				(unsigned long long)oi2->ip_blkno);

	/* We always want to lock the one with the lower lockid first. */
	if (oi1->ip_blkno > oi2->ip_blkno)
		mlog_errno(-ENOLCK);

	/* lock id1 */
	status = ocfs2_inode_lock_nested(inode1, &bh1, 1,
					 OI_LS_REFLINK_TARGET);
	if (status < 0) {
		if (status != -ENOENT)
			mlog_errno(status);
		goto out_rw2;
	}

	/* lock id2 */
	if (!same_inode) {
		status = ocfs2_inode_lock_nested(inode2, &bh2, 1,
						 OI_LS_REFLINK_TARGET);
		if (status < 0) {
			if (status != -ENOENT)
				mlog_errno(status);
			goto out_cl1;
		}
	} else {
		bh2 = bh1;
	}

	/*
	 * If we swapped inode order above, we have to swap the buffer heads
	 * before passing them back to the caller.
	 */
	if (need_swap)
		swap(bh1, bh2);
	*bh_s = bh1;
	*bh_t = bh2;

	trace_ocfs2_double_lock_end(
			(unsigned long long)oi1->ip_blkno,
			(unsigned long long)oi2->ip_blkno);

	return 0;

out_cl1:
	ocfs2_inode_unlock(inode1, 1);
	brelse(bh1);
out_rw2:
	ocfs2_rw_unlock(inode2, 1);
out_i2:
	ocfs2_rw_unlock(inode1, 1);
out_i1:
	unlock_two_nondirectories(s_inode, t_inode);
	return status;
}