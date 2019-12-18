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
struct ocfs2_super {int dummy; } ;
struct ocfs2_dinode {scalar_t__ i_clusters; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_begin_ordered_truncate (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_commit_truncate (struct ocfs2_super*,struct inode*,struct buffer_head*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 scalar_t__ ocfs2_should_order_data (struct inode*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_truncate_for_delete(struct ocfs2_super *osb,
				     struct inode *inode,
				     struct buffer_head *fe_bh)
{
	int status = 0;
	struct ocfs2_dinode *fe;
	handle_t *handle = NULL;

	fe = (struct ocfs2_dinode *) fe_bh->b_data;

	/*
	 * This check will also skip truncate of inodes with inline
	 * data and fast symlinks.
	 */
	if (fe->i_clusters) {
		if (ocfs2_should_order_data(inode))
			ocfs2_begin_ordered_truncate(inode, 0);

		handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
		if (IS_ERR(handle)) {
			status = PTR_ERR(handle);
			handle = NULL;
			mlog_errno(status);
			goto out;
		}

		status = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
						 fe_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		if (status < 0) {
			mlog_errno(status);
			goto out;
		}

		i_size_write(inode, 0);

		status = ocfs2_mark_inode_dirty(handle, inode, fe_bh);
		if (status < 0) {
			mlog_errno(status);
			goto out;
		}

		ocfs2_commit_trans(osb, handle);
		handle = NULL;

		status = ocfs2_commit_truncate(osb, inode, fe_bh);
		if (status < 0)
			mlog_errno(status);
	}

out:
	if (handle)
		ocfs2_commit_trans(osb, handle);
	return status;
}