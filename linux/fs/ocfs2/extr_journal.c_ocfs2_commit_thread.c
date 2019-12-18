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
struct ocfs2_super {int /*<<< orphan*/  checkpoint_event; struct ocfs2_journal* journal; } ;
struct ocfs2_journal {int /*<<< orphan*/  j_num_trans; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_KTHREAD ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int ocfs2_commit_cache (struct ocfs2_super*) ; 
 scalar_t__ printk_timed_ratelimit (unsigned long*,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocfs2_commit_thread(void *arg)
{
	int status;
	struct ocfs2_super *osb = arg;
	struct ocfs2_journal *journal = osb->journal;

	/* we can trust j_num_trans here because _should_stop() is only set in
	 * shutdown and nobody other than ourselves should be able to start
	 * transactions.  committing on shutdown might take a few iterations
	 * as final transactions put deleted inodes on the list */
	while (!(kthread_should_stop() &&
		 atomic_read(&journal->j_num_trans) == 0)) {

		wait_event_interruptible(osb->checkpoint_event,
					 atomic_read(&journal->j_num_trans)
					 || kthread_should_stop());

		status = ocfs2_commit_cache(osb);
		if (status < 0) {
			static unsigned long abort_warn_time;

			/* Warn about this once per minute */
			if (printk_timed_ratelimit(&abort_warn_time, 60*HZ))
				mlog(ML_ERROR, "status = %d, journal is "
						"already aborted.\n", status);
			/*
			 * After ocfs2_commit_cache() fails, j_num_trans has a
			 * non-zero value.  Sleep here to avoid a busy-wait
			 * loop.
			 */
			msleep_interruptible(1000);
		}

		if (kthread_should_stop() && atomic_read(&journal->j_num_trans)){
			mlog(ML_KTHREAD,
			     "commit_thread: %u transactions pending on "
			     "shutdown\n",
			     atomic_read(&journal->j_num_trans));
		}
	}

	return 0;
}