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
struct ocfs2_super {struct ocfs2_journal* journal; } ;
struct ocfs2_journal {int /*<<< orphan*/  j_checkpointed; int /*<<< orphan*/  j_trans_id; int /*<<< orphan*/  j_trans_barrier; int /*<<< orphan*/  j_num_trans; int /*<<< orphan*/  j_journal; } ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int jbd2_journal_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_journal_lock_updates (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_journal_unlock_updates (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_inc_trans_id (struct ocfs2_journal*) ; 
 int /*<<< orphan*/  ocfs2_wake_downconvert_thread (struct ocfs2_super*) ; 
 int /*<<< orphan*/  trace_ocfs2_commit_cache_begin (unsigned int) ; 
 int /*<<< orphan*/  trace_ocfs2_commit_cache_end (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_commit_cache(struct ocfs2_super *osb)
{
	int status = 0;
	unsigned int flushed;
	struct ocfs2_journal *journal = NULL;

	journal = osb->journal;

	/* Flush all pending commits and checkpoint the journal. */
	down_write(&journal->j_trans_barrier);

	flushed = atomic_read(&journal->j_num_trans);
	trace_ocfs2_commit_cache_begin(flushed);
	if (flushed == 0) {
		up_write(&journal->j_trans_barrier);
		goto finally;
	}

	jbd2_journal_lock_updates(journal->j_journal);
	status = jbd2_journal_flush(journal->j_journal);
	jbd2_journal_unlock_updates(journal->j_journal);
	if (status < 0) {
		up_write(&journal->j_trans_barrier);
		mlog_errno(status);
		goto finally;
	}

	ocfs2_inc_trans_id(journal);

	flushed = atomic_read(&journal->j_num_trans);
	atomic_set(&journal->j_num_trans, 0);
	up_write(&journal->j_trans_barrier);

	trace_ocfs2_commit_cache_end(journal->j_trans_id, flushed);

	ocfs2_wake_downconvert_thread(osb);
	wake_up(&journal->j_checkpointed);
finally:
	return status;
}