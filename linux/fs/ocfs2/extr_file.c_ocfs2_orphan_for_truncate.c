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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_mtime_nsec; int /*<<< orphan*/  i_ctime_nsec; void* i_mtime; void* i_ctime; void* i_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {TYPE_1__ i_ctime; TYPE_1__ i_mtime; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_INODE_UPDATE_CREDITS ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 TYPE_1__ current_time (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_align_bytes_to_clusters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_cow_file_pos (struct inode*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_zero_range_for_truncate (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_orphan_for_truncate(struct ocfs2_super *osb,
				     struct inode *inode,
				     struct buffer_head *fe_bh,
				     u64 new_i_size)
{
	int status;
	handle_t *handle;
	struct ocfs2_dinode *di;
	u64 cluster_bytes;

	/*
	 * We need to CoW the cluster contains the offset if it is reflinked
	 * since we will call ocfs2_zero_range_for_truncate later which will
	 * write "0" from offset to the end of the cluster.
	 */
	status = ocfs2_cow_file_pos(inode, fe_bh, new_i_size);
	if (status) {
		mlog_errno(status);
		return status;
	}

	/* TODO: This needs to actually orphan the inode in this
	 * transaction. */

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		mlog_errno(status);
		goto out;
	}

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), fe_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto out_commit;
	}

	/*
	 * Do this before setting i_size.
	 */
	cluster_bytes = ocfs2_align_bytes_to_clusters(inode->i_sb, new_i_size);
	status = ocfs2_zero_range_for_truncate(inode, handle, new_i_size,
					       cluster_bytes);
	if (status) {
		mlog_errno(status);
		goto out_commit;
	}

	i_size_write(inode, new_i_size);
	inode->i_ctime = inode->i_mtime = current_time(inode);

	di = (struct ocfs2_dinode *) fe_bh->b_data;
	di->i_size = cpu_to_le64(new_i_size);
	di->i_ctime = di->i_mtime = cpu_to_le64(inode->i_ctime.tv_sec);
	di->i_ctime_nsec = di->i_mtime_nsec = cpu_to_le32(inode->i_ctime.tv_nsec);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

	ocfs2_journal_dirty(handle, fe_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	return status;
}