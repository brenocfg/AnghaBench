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
struct xfs_log_item {int /*<<< orphan*/  li_lsn; } ;
struct xfs_ail {int /*<<< orphan*/  ail_empty; int /*<<< orphan*/  ail_lock; int /*<<< orphan*/  ail_task; int /*<<< orphan*/  ail_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 struct xfs_log_item* xfs_ail_max (struct xfs_ail*) ; 

void
xfs_ail_push_all_sync(
	struct xfs_ail  *ailp)
{
	struct xfs_log_item	*lip;
	DEFINE_WAIT(wait);

	spin_lock(&ailp->ail_lock);
	while ((lip = xfs_ail_max(ailp)) != NULL) {
		prepare_to_wait(&ailp->ail_empty, &wait, TASK_UNINTERRUPTIBLE);
		ailp->ail_target = lip->li_lsn;
		wake_up_process(ailp->ail_task);
		spin_unlock(&ailp->ail_lock);
		schedule();
		spin_lock(&ailp->ail_lock);
	}
	spin_unlock(&ailp->ail_lock);

	finish_wait(&ailp->ail_empty, &wait);
}