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
struct xfs_dquot {int /*<<< orphan*/  q_pincount; int /*<<< orphan*/  q_pinwait; int /*<<< orphan*/  q_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_DQ_IS_LOCKED (struct xfs_dquot*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_log_force (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_qm_dqunpin_wait(
	struct xfs_dquot	*dqp)
{
	ASSERT(XFS_DQ_IS_LOCKED(dqp));
	if (atomic_read(&dqp->q_pincount) == 0)
		return;

	/*
	 * Give the log a push so we don't wait here too long.
	 */
	xfs_log_force(dqp->q_mount, 0);
	wait_event(dqp->q_pinwait, (atomic_read(&dqp->q_pincount) == 0));
}