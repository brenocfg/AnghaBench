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
struct ocfs2_super {int /*<<< orphan*/ * dc_task; int /*<<< orphan*/  dc_event; } ;

/* Variables and functions */
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocfs2_downconvert_thread_do_work (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_downconvert_thread_lists_empty (struct ocfs2_super*) ; 
 scalar_t__ ocfs2_downconvert_thread_should_wake (struct ocfs2_super*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocfs2_downconvert_thread(void *arg)
{
	int status = 0;
	struct ocfs2_super *osb = arg;

	/* only quit once we've been asked to stop and there is no more
	 * work available */
	while (!(kthread_should_stop() &&
		ocfs2_downconvert_thread_lists_empty(osb))) {

		wait_event_interruptible(osb->dc_event,
					 ocfs2_downconvert_thread_should_wake(osb) ||
					 kthread_should_stop());

		mlog(0, "downconvert_thread: awoken\n");

		ocfs2_downconvert_thread_do_work(osb);
	}

	osb->dc_task = NULL;
	return status;
}