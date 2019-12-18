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
struct TYPE_4__ {int* av_signal; int /*<<< orphan*/  av_freeWorkers; int /*<<< orphan*/  av_launcherpid; } ;
struct TYPE_3__ {int wi_sharedrel; int wi_dobalance; int /*<<< orphan*/  wi_links; scalar_t__ wi_cost_limit_base; scalar_t__ wi_cost_limit; scalar_t__ wi_cost_delay; scalar_t__ wi_launchtime; int /*<<< orphan*/ * wi_proc; void* wi_tableoid; void* wi_dboid; } ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 size_t AutoVacRebalance ; 
 TYPE_2__* AutoVacuumShmem ; 
 int /*<<< orphan*/  AutovacuumLauncherPid ; 
 int /*<<< orphan*/  AutovacuumLock ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* MyWorkerInfo ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
FreeWorkerInfo(int code, Datum arg)
{
	if (MyWorkerInfo != NULL)
	{
		LWLockAcquire(AutovacuumLock, LW_EXCLUSIVE);

		/*
		 * Wake the launcher up so that he can launch a new worker immediately
		 * if required.  We only save the launcher's PID in local memory here;
		 * the actual signal will be sent when the PGPROC is recycled.  Note
		 * that we always do this, so that the launcher can rebalance the cost
		 * limit setting of the remaining workers.
		 *
		 * We somewhat ignore the risk that the launcher changes its PID
		 * between us reading it and the actual kill; we expect ProcKill to be
		 * called shortly after us, and we assume that PIDs are not reused too
		 * quickly after a process exits.
		 */
		AutovacuumLauncherPid = AutoVacuumShmem->av_launcherpid;

		dlist_delete(&MyWorkerInfo->wi_links);
		MyWorkerInfo->wi_dboid = InvalidOid;
		MyWorkerInfo->wi_tableoid = InvalidOid;
		MyWorkerInfo->wi_sharedrel = false;
		MyWorkerInfo->wi_proc = NULL;
		MyWorkerInfo->wi_launchtime = 0;
		MyWorkerInfo->wi_dobalance = false;
		MyWorkerInfo->wi_cost_delay = 0;
		MyWorkerInfo->wi_cost_limit = 0;
		MyWorkerInfo->wi_cost_limit_base = 0;
		dlist_push_head(&AutoVacuumShmem->av_freeWorkers,
						&MyWorkerInfo->wi_links);
		/* not mine anymore */
		MyWorkerInfo = NULL;

		/*
		 * now that we're inactive, cause a rebalancing of the surviving
		 * workers
		 */
		AutoVacuumShmem->av_signal[AutoVacRebalance] = true;
		LWLockRelease(AutovacuumLock);
	}
}