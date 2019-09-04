#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int dummy; } ;
struct ocfs2_move_extents_context {struct inode* inode; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_ctime_nsec; int /*<<< orphan*/  i_ctime; } ;
struct TYPE_3__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {TYPE_1__ i_ctime; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip_alloc_sem; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ocfs2_move_extents_range (struct buffer_head*,struct ocfs2_move_extents_context*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 TYPE_1__ current_time (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_inode_lock (struct inode*,struct buffer_head**,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_is_soft_readonly (struct ocfs2_super*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_rw_lock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_rw_unlock (struct inode*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_move_extents(struct ocfs2_move_extents_context *context)
{
	int status;
	handle_t *handle;
	struct inode *inode = context->inode;
	struct ocfs2_dinode *di;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	if (ocfs2_is_hard_readonly(osb) || ocfs2_is_soft_readonly(osb))
		return -EROFS;

	inode_lock(inode);

	/*
	 * This prevents concurrent writes from other nodes
	 */
	status = ocfs2_rw_lock(inode, 1);
	if (status) {
		mlog_errno(status);
		goto out;
	}

	status = ocfs2_inode_lock(inode, &di_bh, 1);
	if (status) {
		mlog_errno(status);
		goto out_rw_unlock;
	}

	/*
	 * rememer ip_xattr_sem also needs to be held if necessary
	 */
	down_write(&OCFS2_I(inode)->ip_alloc_sem);

	status = __ocfs2_move_extents_range(di_bh, context);

	up_write(&OCFS2_I(inode)->ip_alloc_sem);
	if (status) {
		mlog_errno(status);
		goto out_inode_unlock;
	}

	/*
	 * We update ctime for these changes
	 */
	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out_inode_unlock;
	}

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status) {
		mlog_errno(status);
		goto out_commit;
	}

	di = (struct ocfs2_dinode *)di_bh->b_data;
	inode->i_ctime = current_time(inode);
	di->i_ctime = cpu_to_le64(inode->i_ctime.tv_sec);
	di->i_ctime_nsec = cpu_to_le32(inode->i_ctime.tv_nsec);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

	ocfs2_journal_dirty(handle, di_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);

out_inode_unlock:
	brelse(di_bh);
	ocfs2_inode_unlock(inode, 1);
out_rw_unlock:
	ocfs2_rw_unlock(inode, 1);
out:
	inode_unlock(inode);

	return status;
}