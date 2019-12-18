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
struct ocfs2_super {int disable_recovery; struct ocfs2_recovery_map* recovery_map; scalar_t__ ocfs2_wq; int /*<<< orphan*/  recovery_event; int /*<<< orphan*/  recovery_lock; } ;
struct ocfs2_recovery_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_recovery_map*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_recovery_thread_running (struct ocfs2_super*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void ocfs2_recovery_exit(struct ocfs2_super *osb)
{
	struct ocfs2_recovery_map *rm;

	/* disable any new recovery threads and wait for any currently
	 * running ones to exit. Do this before setting the vol_state. */
	mutex_lock(&osb->recovery_lock);
	osb->disable_recovery = 1;
	mutex_unlock(&osb->recovery_lock);
	wait_event(osb->recovery_event, !ocfs2_recovery_thread_running(osb));

	/* At this point, we know that no more recovery threads can be
	 * launched, so wait for any recovery completion work to
	 * complete. */
	if (osb->ocfs2_wq)
		flush_workqueue(osb->ocfs2_wq);

	/*
	 * Now that recovery is shut down, and the osb is about to be
	 * freed,  the osb_lock is not taken here.
	 */
	rm = osb->recovery_map;
	/* XXX: Should we bug if there are dirty entries? */

	kfree(rm);
}