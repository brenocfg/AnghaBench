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
struct ocfs2_truncate_log {scalar_t__ tl_used; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct TYPE_2__ {struct ocfs2_truncate_log i_dealloc; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_check; TYPE_1__ id2; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; int /*<<< orphan*/  b_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DINODE (struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_dinode*) ; 
 struct ocfs2_dinode* kmemdup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_compute_meta_ecc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int ocfs2_get_truncate_log_info (struct ocfs2_super*,int,struct inode**,struct buffer_head**) ; 
 int ocfs2_write_block (struct ocfs2_super*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_begin_truncate_log_recovery (int) ; 
 int /*<<< orphan*/  trace_ocfs2_truncate_log_recovery_num (scalar_t__) ; 

int ocfs2_begin_truncate_log_recovery(struct ocfs2_super *osb,
				      int slot_num,
				      struct ocfs2_dinode **tl_copy)
{
	int status;
	struct inode *tl_inode = NULL;
	struct buffer_head *tl_bh = NULL;
	struct ocfs2_dinode *di;
	struct ocfs2_truncate_log *tl;

	*tl_copy = NULL;

	trace_ocfs2_begin_truncate_log_recovery(slot_num);

	status = ocfs2_get_truncate_log_info(osb, slot_num, &tl_inode, &tl_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	di = (struct ocfs2_dinode *) tl_bh->b_data;

	/* tl_bh is loaded from ocfs2_get_truncate_log_info().  It's
	 * validated by the underlying call to ocfs2_read_inode_block(),
	 * so any corruption is a code bug */
	BUG_ON(!OCFS2_IS_VALID_DINODE(di));

	tl = &di->id2.i_dealloc;
	if (le16_to_cpu(tl->tl_used)) {
		trace_ocfs2_truncate_log_recovery_num(le16_to_cpu(tl->tl_used));

		/*
		 * Assuming the write-out below goes well, this copy will be
		 * passed back to recovery for processing.
		 */
		*tl_copy = kmemdup(tl_bh->b_data, tl_bh->b_size, GFP_KERNEL);
		if (!(*tl_copy)) {
			status = -ENOMEM;
			mlog_errno(status);
			goto bail;
		}

		/* All we need to do to clear the truncate log is set
		 * tl_used. */
		tl->tl_used = 0;

		ocfs2_compute_meta_ecc(osb->sb, tl_bh->b_data, &di->i_check);
		status = ocfs2_write_block(osb, tl_bh, INODE_CACHE(tl_inode));
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

bail:
	iput(tl_inode);
	brelse(tl_bh);

	if (status < 0) {
		kfree(*tl_copy);
		*tl_copy = NULL;
		mlog_errno(status);
	}

	return status;
}