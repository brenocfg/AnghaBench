#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct buffer_head {TYPE_2__* b_bdev; scalar_t__ b_blocknr; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_10__ {int h_err; TYPE_1__* h_transaction; } ;
typedef  TYPE_3__ handle_t ;
struct TYPE_9__ {struct super_block* bd_super; } ;
struct TYPE_8__ {int /*<<< orphan*/ * t_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  is_handle_aborted (TYPE_3__*) ; 
 int /*<<< orphan*/  jbd2_journal_abort (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jbd2_journal_abort_handle (TYPE_3__*) ; 
 int jbd2_journal_dirty_metadata (TYPE_3__*,struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_abort (struct super_block*,char*) ; 
 int /*<<< orphan*/  trace_ocfs2_journal_dirty (unsigned long long) ; 

void ocfs2_journal_dirty(handle_t *handle, struct buffer_head *bh)
{
	int status;

	trace_ocfs2_journal_dirty((unsigned long long)bh->b_blocknr);

	status = jbd2_journal_dirty_metadata(handle, bh);
	if (status) {
		mlog_errno(status);
		if (!is_handle_aborted(handle)) {
			journal_t *journal = handle->h_transaction->t_journal;
			struct super_block *sb = bh->b_bdev->bd_super;

			mlog(ML_ERROR, "jbd2_journal_dirty_metadata failed. "
					"Aborting transaction and journal.\n");
			handle->h_err = status;
			jbd2_journal_abort_handle(handle);
			jbd2_journal_abort(journal, status);
			ocfs2_abort(sb, "Journal already aborted.\n");
		}
	}
}