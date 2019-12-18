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
struct ocfs2_super {int /*<<< orphan*/ * commit_task; int /*<<< orphan*/  uuid_str; int /*<<< orphan*/  slot_num; int /*<<< orphan*/  sb; } ;
struct ocfs2_journal {int /*<<< orphan*/  j_journal; struct ocfs2_super* j_osb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int jbd2_journal_load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct ocfs2_super*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clear_journal_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_thread ; 
 int ocfs2_journal_toggle_dirty (struct ocfs2_super*,int,int) ; 

int ocfs2_journal_load(struct ocfs2_journal *journal, int local, int replayed)
{
	int status = 0;
	struct ocfs2_super *osb;

	BUG_ON(!journal);

	osb = journal->j_osb;

	status = jbd2_journal_load(journal->j_journal);
	if (status < 0) {
		mlog(ML_ERROR, "Failed to load journal!\n");
		goto done;
	}

	ocfs2_clear_journal_error(osb->sb, journal->j_journal, osb->slot_num);

	status = ocfs2_journal_toggle_dirty(osb, 1, replayed);
	if (status < 0) {
		mlog_errno(status);
		goto done;
	}

	/* Launch the commit thread */
	if (!local) {
		osb->commit_task = kthread_run(ocfs2_commit_thread, osb,
				"ocfs2cmt-%s", osb->uuid_str);
		if (IS_ERR(osb->commit_task)) {
			status = PTR_ERR(osb->commit_task);
			osb->commit_task = NULL;
			mlog(ML_ERROR, "unable to launch ocfs2commit thread, "
			     "error=%d", status);
			goto done;
		}
	} else
		osb->commit_task = NULL;

done:
	return status;
}