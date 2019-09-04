#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct ocfs2_super {TYPE_2__* journal; } ;
struct ocfs2_inode_info {int /*<<< orphan*/  i_sync_tid; int /*<<< orphan*/  i_datasync_tid; int /*<<< orphan*/  ip_blkno; } ;
struct inode {TYPE_9__* i_sb; } ;
struct TYPE_13__ {TYPE_6__* dentry; } ;
struct file {TYPE_4__ f_path; TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_14__ {int j_flags; } ;
typedef  TYPE_5__ journal_t ;
struct TYPE_16__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct TYPE_15__ {TYPE_3__ d_name; } ;
struct TYPE_11__ {TYPE_5__* j_journal; } ;
struct TYPE_10__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int EROFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int JBD2_BARRIER ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (TYPE_9__*) ; 
 int blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jbd2_complete_transaction (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_trans_will_send_data_barrier (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_is_soft_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  trace_ocfs2_sync_file (struct inode*,struct file*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static int ocfs2_sync_file(struct file *file, loff_t start, loff_t end,
			   int datasync)
{
	int err = 0;
	struct inode *inode = file->f_mapping->host;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	journal_t *journal = osb->journal->j_journal;
	int ret;
	tid_t commit_tid;
	bool needs_barrier = false;

	trace_ocfs2_sync_file(inode, file, file->f_path.dentry,
			      oi->ip_blkno,
			      file->f_path.dentry->d_name.len,
			      file->f_path.dentry->d_name.name,
			      (unsigned long long)datasync);

	if (ocfs2_is_hard_readonly(osb) || ocfs2_is_soft_readonly(osb))
		return -EROFS;

	err = file_write_and_wait_range(file, start, end);
	if (err)
		return err;

	commit_tid = datasync ? oi->i_datasync_tid : oi->i_sync_tid;
	if (journal->j_flags & JBD2_BARRIER &&
	    !jbd2_trans_will_send_data_barrier(journal, commit_tid))
		needs_barrier = true;
	err = jbd2_complete_transaction(journal, commit_tid);
	if (needs_barrier) {
		ret = blkdev_issue_flush(inode->i_sb->s_bdev, GFP_KERNEL, NULL);
		if (!err)
			err = ret;
	}

	if (err)
		mlog_errno(err);

	return (err < 0) ? -EIO : 0;
}