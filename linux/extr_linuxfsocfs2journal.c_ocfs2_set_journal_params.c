#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {long osb_commit_interval; int s_mount_opt; TYPE_1__* journal; } ;
struct TYPE_4__ {unsigned long j_commit_interval; int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_flags; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_3__ {TYPE_2__* j_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  JBD2_BARRIER ; 
 unsigned long OCFS2_DEFAULT_COMMIT_INTERVAL ; 
 int OCFS2_MOUNT_BARRIER ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void ocfs2_set_journal_params(struct ocfs2_super *osb)
{
	journal_t *journal = osb->journal->j_journal;
	unsigned long commit_interval = OCFS2_DEFAULT_COMMIT_INTERVAL;

	if (osb->osb_commit_interval)
		commit_interval = osb->osb_commit_interval;

	write_lock(&journal->j_state_lock);
	journal->j_commit_interval = commit_interval;
	if (osb->s_mount_opt & OCFS2_MOUNT_BARRIER)
		journal->j_flags |= JBD2_BARRIER;
	else
		journal->j_flags &= ~JBD2_BARRIER;
	write_unlock(&journal->j_state_lock);
}