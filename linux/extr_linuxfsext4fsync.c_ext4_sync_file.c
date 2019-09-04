#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct inode {TYPE_3__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_sync_tid; int /*<<< orphan*/  i_datasync_tid; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_12__ {int j_flags; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_14__ {int s_mount_flags; TYPE_2__* s_journal; } ;
struct TYPE_13__ {int /*<<< orphan*/  s_bdev; } ;
struct TYPE_11__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 int EIO ; 
 int EROFS ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int EXT4_MF_FS_ABORTED ; 
 TYPE_7__* EXT4_SB (TYPE_3__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int JBD2_BARRIER ; 
 int /*<<< orphan*/  J_ASSERT (int /*<<< orphan*/ ) ; 
 int __generic_file_fsync (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ext4_force_commit (TYPE_3__*) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (TYPE_7__*) ; 
 int /*<<< orphan*/ * ext4_journal_current_handle () ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 int ext4_sync_parent (struct inode*) ; 
 int file_check_and_advance_wb_err (struct file*) ; 
 int file_write_and_wait_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jbd2_complete_transaction (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_trans_will_send_data_barrier (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sb_rdonly (TYPE_3__*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_opt (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_sync_file_enter (struct file*,int) ; 
 int /*<<< orphan*/  trace_ext4_sync_file_exit (struct inode*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ext4_sync_file(struct file *file, loff_t start, loff_t end, int datasync)
{
	struct inode *inode = file->f_mapping->host;
	struct ext4_inode_info *ei = EXT4_I(inode);
	journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;
	int ret = 0, err;
	tid_t commit_tid;
	bool needs_barrier = false;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	J_ASSERT(ext4_journal_current_handle() == NULL);

	trace_ext4_sync_file_enter(file, datasync);

	if (sb_rdonly(inode->i_sb)) {
		/* Make sure that we read updated s_mount_flags value */
		smp_rmb();
		if (EXT4_SB(inode->i_sb)->s_mount_flags & EXT4_MF_FS_ABORTED)
			ret = -EROFS;
		goto out;
	}

	if (!journal) {
		ret = __generic_file_fsync(file, start, end, datasync);
		if (!ret)
			ret = ext4_sync_parent(inode);
		if (test_opt(inode->i_sb, BARRIER))
			goto issue_flush;
		goto out;
	}

	ret = file_write_and_wait_range(file, start, end);
	if (ret)
		return ret;
	/*
	 * data=writeback,ordered:
	 *  The caller's filemap_fdatawrite()/wait will sync the data.
	 *  Metadata is in the journal, we wait for proper transaction to
	 *  commit here.
	 *
	 * data=journal:
	 *  filemap_fdatawrite won't do anything (the buffers are clean).
	 *  ext4_force_commit will write the file data into the journal and
	 *  will wait on that.
	 *  filemap_fdatawait() will encounter a ton of newly-dirtied pages
	 *  (they were dirtied by commit).  But that's OK - the blocks are
	 *  safe in-journal, which is all fsync() needs to ensure.
	 */
	if (ext4_should_journal_data(inode)) {
		ret = ext4_force_commit(inode->i_sb);
		goto out;
	}

	commit_tid = datasync ? ei->i_datasync_tid : ei->i_sync_tid;
	if (journal->j_flags & JBD2_BARRIER &&
	    !jbd2_trans_will_send_data_barrier(journal, commit_tid))
		needs_barrier = true;
	ret = jbd2_complete_transaction(journal, commit_tid);
	if (needs_barrier) {
	issue_flush:
		err = blkdev_issue_flush(inode->i_sb->s_bdev, GFP_KERNEL, NULL);
		if (!ret)
			ret = err;
	}
out:
	err = file_check_and_advance_wb_err(file);
	if (ret == 0)
		ret = err;
	trace_ext4_sync_file_exit(inode, ret);
	return ret;
}