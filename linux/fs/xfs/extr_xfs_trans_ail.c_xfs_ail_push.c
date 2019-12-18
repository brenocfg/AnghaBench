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
typedef  int /*<<< orphan*/  xfs_lsn_t ;
struct xfs_log_item {int dummy; } ;
struct xfs_ail {int /*<<< orphan*/  ail_task; int /*<<< orphan*/  ail_target; int /*<<< orphan*/  ail_mount; } ;

/* Variables and functions */
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_LSN_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 
 struct xfs_log_item* xfs_ail_min (struct xfs_ail*) ; 
 int /*<<< orphan*/  xfs_trans_ail_copy_lsn (struct xfs_ail*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
xfs_ail_push(
	struct xfs_ail		*ailp,
	xfs_lsn_t		threshold_lsn)
{
	struct xfs_log_item	*lip;

	lip = xfs_ail_min(ailp);
	if (!lip || XFS_FORCED_SHUTDOWN(ailp->ail_mount) ||
	    XFS_LSN_CMP(threshold_lsn, ailp->ail_target) <= 0)
		return;

	/*
	 * Ensure that the new target is noticed in push code before it clears
	 * the XFS_AIL_PUSHING_BIT.
	 */
	smp_wmb();
	xfs_trans_ail_copy_lsn(ailp, &ailp->ail_target, &threshold_lsn);
	smp_wmb();

	wake_up_process(ailp->ail_task);
}