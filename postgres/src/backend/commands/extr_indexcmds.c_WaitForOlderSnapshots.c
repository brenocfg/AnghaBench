#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  backendId; } ;
typedef  TYPE_1__ VirtualTransactionId ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_12__ {int pid; } ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 TYPE_2__* BackendIdGetProc (int /*<<< orphan*/ ) ; 
 TYPE_1__* GetCurrentVirtualXIDs (int /*<<< orphan*/ ,int,int,int,int*) ; 
 int PROC_IN_VACUUM ; 
 int PROC_IS_AUTOVACUUM ; 
 int /*<<< orphan*/  PROGRESS_WAITFOR_CURRENT_PID ; 
 int /*<<< orphan*/  PROGRESS_WAITFOR_DONE ; 
 int /*<<< orphan*/  PROGRESS_WAITFOR_TOTAL ; 
 int /*<<< orphan*/  SetInvalidVirtualTransactionId (TYPE_1__) ; 
 scalar_t__ VirtualTransactionIdEquals (TYPE_1__,TYPE_1__) ; 
 scalar_t__ VirtualTransactionIdIsValid (TYPE_1__) ; 
 int /*<<< orphan*/  VirtualXactLock (TYPE_1__,int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pgstat_progress_update_param (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
WaitForOlderSnapshots(TransactionId limitXmin, bool progress)
{
	int			n_old_snapshots;
	int			i;
	VirtualTransactionId *old_snapshots;

	old_snapshots = GetCurrentVirtualXIDs(limitXmin, true, false,
										  PROC_IS_AUTOVACUUM | PROC_IN_VACUUM,
										  &n_old_snapshots);
	if (progress)
		pgstat_progress_update_param(PROGRESS_WAITFOR_TOTAL, n_old_snapshots);

	for (i = 0; i < n_old_snapshots; i++)
	{
		if (!VirtualTransactionIdIsValid(old_snapshots[i]))
			continue;			/* found uninteresting in previous cycle */

		if (i > 0)
		{
			/* see if anything's changed ... */
			VirtualTransactionId *newer_snapshots;
			int			n_newer_snapshots;
			int			j;
			int			k;

			newer_snapshots = GetCurrentVirtualXIDs(limitXmin,
													true, false,
													PROC_IS_AUTOVACUUM | PROC_IN_VACUUM,
													&n_newer_snapshots);
			for (j = i; j < n_old_snapshots; j++)
			{
				if (!VirtualTransactionIdIsValid(old_snapshots[j]))
					continue;	/* found uninteresting in previous cycle */
				for (k = 0; k < n_newer_snapshots; k++)
				{
					if (VirtualTransactionIdEquals(old_snapshots[j],
												   newer_snapshots[k]))
						break;
				}
				if (k >= n_newer_snapshots) /* not there anymore */
					SetInvalidVirtualTransactionId(old_snapshots[j]);
			}
			pfree(newer_snapshots);
		}

		if (VirtualTransactionIdIsValid(old_snapshots[i]))
		{
			/* If requested, publish who we're going to wait for. */
			if (progress)
			{
				PGPROC	   *holder = BackendIdGetProc(old_snapshots[i].backendId);

				if (holder)
					pgstat_progress_update_param(PROGRESS_WAITFOR_CURRENT_PID,
												 holder->pid);
			}
			VirtualXactLock(old_snapshots[i], true);
		}

		if (progress)
			pgstat_progress_update_param(PROGRESS_WAITFOR_DONE, i + 1);
	}
}