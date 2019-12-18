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
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_check; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_end_io; int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int EROFS ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_write_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_check_super_or_backup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_compute_meta_ecc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_is_soft_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int ocfs2_write_super_or_backup(struct ocfs2_super *osb,
				struct buffer_head *bh)
{
	int ret = 0;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)bh->b_data;

	BUG_ON(buffer_jbd(bh));
	ocfs2_check_super_or_backup(osb->sb, bh->b_blocknr);

	if (ocfs2_is_hard_readonly(osb) || ocfs2_is_soft_readonly(osb)) {
		ret = -EROFS;
		mlog_errno(ret);
		goto out;
	}

	lock_buffer(bh);
	set_buffer_uptodate(bh);

	/* remove from dirty list before I/O. */
	clear_buffer_dirty(bh);

	get_bh(bh); /* for end_buffer_write_sync() */
	bh->b_end_io = end_buffer_write_sync;
	ocfs2_compute_meta_ecc(osb->sb, bh->b_data, &di->i_check);
	submit_bh(REQ_OP_WRITE, 0, bh);

	wait_on_buffer(bh);

	if (!buffer_uptodate(bh)) {
		ret = -EIO;
		mlog_errno(ret);
	}

out:
	return ret;
}