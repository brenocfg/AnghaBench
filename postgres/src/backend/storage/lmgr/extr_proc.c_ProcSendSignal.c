#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int startupProcPid; TYPE_1__* startupProc; } ;
struct TYPE_4__ {int /*<<< orphan*/  procLatch; } ;
typedef  TYPE_1__ PGPROC ;

/* Variables and functions */
 TYPE_1__* BackendPidGetProc (int) ; 
 TYPE_2__* ProcGlobal ; 
 int /*<<< orphan*/  ProcStructLock ; 
 scalar_t__ RecoveryInProgress () ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ ) ; 

void
ProcSendSignal(int pid)
{
	PGPROC	   *proc = NULL;

	if (RecoveryInProgress())
	{
		SpinLockAcquire(ProcStructLock);

		/*
		 * Check to see whether it is the Startup process we wish to signal.
		 * This call is made by the buffer manager when it wishes to wake up a
		 * process that has been waiting for a pin in so it can obtain a
		 * cleanup lock using LockBufferForCleanup(). Startup is not a normal
		 * backend, so BackendPidGetProc() will not return any pid at all. So
		 * we remember the information for this special case.
		 */
		if (pid == ProcGlobal->startupProcPid)
			proc = ProcGlobal->startupProc;

		SpinLockRelease(ProcStructLock);
	}

	if (proc == NULL)
		proc = BackendPidGetProc(pid);

	if (proc != NULL)
	{
		SetLatch(&proc->procLatch);
	}
}