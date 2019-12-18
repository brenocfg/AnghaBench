#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int h_buffer_credits; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_MAX_TRANS_DATA ; 
 int jbd2_journal_extend (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int jbd2_journal_restart (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  trace_ocfs2_allocate_extend_trans (int,int) ; 

int ocfs2_allocate_extend_trans(handle_t *handle, int thresh)
{
	int status, old_nblks;

	BUG_ON(!handle);

	old_nblks = handle->h_buffer_credits;
	trace_ocfs2_allocate_extend_trans(old_nblks, thresh);

	if (old_nblks < thresh)
		return 0;

	status = jbd2_journal_extend(handle, OCFS2_MAX_TRANS_DATA);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	if (status > 0) {
		status = jbd2_journal_restart(handle, OCFS2_MAX_TRANS_DATA);
		if (status < 0)
			mlog_errno(status);
	}

bail:
	return status;
}