#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int /*<<< orphan*/  sb; struct ocfs2_journal* journal; } ;
struct ocfs2_journal {int /*<<< orphan*/  j_trans_barrier; } ;
struct TYPE_4__ {int h_ref; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int jbd2_journal_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ocfs2_commit_trans(struct ocfs2_super *osb,
		       handle_t *handle)
{
	int ret, nested;
	struct ocfs2_journal *journal = osb->journal;

	BUG_ON(!handle);

	nested = handle->h_ref > 1;
	ret = jbd2_journal_stop(handle);
	if (ret < 0)
		mlog_errno(ret);

	if (!nested) {
		up_read(&journal->j_trans_barrier);
		sb_end_intwrite(osb->sb);
	}

	return ret;
}