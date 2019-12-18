#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_13__ {size_t pgprocno; int procArrayGroupMember; int /*<<< orphan*/  sem; int /*<<< orphan*/  procArrayGroupNext; int /*<<< orphan*/  procArrayGroupMemberXid; } ;
struct TYPE_12__ {int /*<<< orphan*/  xid; } ;
struct TYPE_11__ {int /*<<< orphan*/  procArrayGroupFirst; } ;
typedef  TYPE_1__ PROC_HDR ;
typedef  TYPE_2__ PGXACT ;
typedef  TYPE_3__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t INVALID_PGPROCNO ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_3__* MyProc ; 
 int /*<<< orphan*/  PGSemaphoreLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGSemaphoreUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcArrayEndTransactionInternal (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 TYPE_1__* ProcGlobal ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_PROCARRAY_GROUP_UPDATE ; 
 TYPE_2__* allPgXact ; 
 TYPE_3__* allProcs ; 
 scalar_t__ pg_atomic_compare_exchange_u32 (int /*<<< orphan*/ *,size_t*,size_t) ; 
 size_t pg_atomic_exchange_u32 (int /*<<< orphan*/ *,size_t) ; 
 size_t pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_atomic_write_u32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  pg_write_barrier () ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ProcArrayGroupClearXid(PGPROC *proc, TransactionId latestXid)
{
	PROC_HDR   *procglobal = ProcGlobal;
	uint32		nextidx;
	uint32		wakeidx;

	/* We should definitely have an XID to clear. */
	Assert(TransactionIdIsValid(allPgXact[proc->pgprocno].xid));

	/* Add ourselves to the list of processes needing a group XID clear. */
	proc->procArrayGroupMember = true;
	proc->procArrayGroupMemberXid = latestXid;
	nextidx = pg_atomic_read_u32(&procglobal->procArrayGroupFirst);
	while (true)
	{
		pg_atomic_write_u32(&proc->procArrayGroupNext, nextidx);

		if (pg_atomic_compare_exchange_u32(&procglobal->procArrayGroupFirst,
										   &nextidx,
										   (uint32) proc->pgprocno))
			break;
	}

	/*
	 * If the list was not empty, the leader will clear our XID.  It is
	 * impossible to have followers without a leader because the first process
	 * that has added itself to the list will always have nextidx as
	 * INVALID_PGPROCNO.
	 */
	if (nextidx != INVALID_PGPROCNO)
	{
		int			extraWaits = 0;

		/* Sleep until the leader clears our XID. */
		pgstat_report_wait_start(WAIT_EVENT_PROCARRAY_GROUP_UPDATE);
		for (;;)
		{
			/* acts as a read barrier */
			PGSemaphoreLock(proc->sem);
			if (!proc->procArrayGroupMember)
				break;
			extraWaits++;
		}
		pgstat_report_wait_end();

		Assert(pg_atomic_read_u32(&proc->procArrayGroupNext) == INVALID_PGPROCNO);

		/* Fix semaphore count for any absorbed wakeups */
		while (extraWaits-- > 0)
			PGSemaphoreUnlock(proc->sem);
		return;
	}

	/* We are the leader.  Acquire the lock on behalf of everyone. */
	LWLockAcquire(ProcArrayLock, LW_EXCLUSIVE);

	/*
	 * Now that we've got the lock, clear the list of processes waiting for
	 * group XID clearing, saving a pointer to the head of the list.  Trying
	 * to pop elements one at a time could lead to an ABA problem.
	 */
	nextidx = pg_atomic_exchange_u32(&procglobal->procArrayGroupFirst,
									 INVALID_PGPROCNO);

	/* Remember head of list so we can perform wakeups after dropping lock. */
	wakeidx = nextidx;

	/* Walk the list and clear all XIDs. */
	while (nextidx != INVALID_PGPROCNO)
	{
		PGPROC	   *proc = &allProcs[nextidx];
		PGXACT	   *pgxact = &allPgXact[nextidx];

		ProcArrayEndTransactionInternal(proc, pgxact, proc->procArrayGroupMemberXid);

		/* Move to next proc in list. */
		nextidx = pg_atomic_read_u32(&proc->procArrayGroupNext);
	}

	/* We're done with the lock now. */
	LWLockRelease(ProcArrayLock);

	/*
	 * Now that we've released the lock, go back and wake everybody up.  We
	 * don't do this under the lock so as to keep lock hold times to a
	 * minimum.  The system calls we need to perform to wake other processes
	 * up are probably much slower than the simple memory writes we did while
	 * holding the lock.
	 */
	while (wakeidx != INVALID_PGPROCNO)
	{
		PGPROC	   *proc = &allProcs[wakeidx];

		wakeidx = pg_atomic_read_u32(&proc->procArrayGroupNext);
		pg_atomic_write_u32(&proc->procArrayGroupNext, INVALID_PGPROCNO);

		/* ensure all previous writes are visible before follower continues. */
		pg_write_barrier();

		proc->procArrayGroupMember = false;

		if (proc != MyProc)
			PGSemaphoreUnlock(proc->sem);
	}
}