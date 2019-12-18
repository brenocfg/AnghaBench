#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  XidStatus ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {int /*<<< orphan*/  xids; } ;
struct TYPE_10__ {int clogGroupMember; int clogGroupMemberPage; int /*<<< orphan*/  sem; int /*<<< orphan*/  clogGroupNext; int /*<<< orphan*/  clogGroupMemberLsn; int /*<<< orphan*/  clogGroupMemberXidStatus; TYPE_1__ subxids; int /*<<< orphan*/  clogGroupMemberXid; scalar_t__ pgprocno; } ;
struct TYPE_9__ {int /*<<< orphan*/  nxids; int /*<<< orphan*/  overflowed; } ;
struct TYPE_8__ {TYPE_4__* allProcs; TYPE_3__* allPgXact; int /*<<< orphan*/  clogGroupFirst; } ;
typedef  TYPE_2__ PROC_HDR ;
typedef  TYPE_3__ PGXACT ;
typedef  TYPE_4__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CLogControlLock ; 
 size_t INVALID_PGPROCNO ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_4__* MyProc ; 
 int /*<<< orphan*/  PGSemaphoreLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGSemaphoreUnlock (int /*<<< orphan*/ ) ; 
 TYPE_2__* ProcGlobal ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdSetPageStatusInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WAIT_EVENT_CLOG_GROUP_UPDATE ; 
 scalar_t__ pg_atomic_compare_exchange_u32 (int /*<<< orphan*/ *,size_t*,size_t) ; 
 size_t pg_atomic_exchange_u32 (int /*<<< orphan*/ *,size_t) ; 
 size_t pg_atomic_read_u32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_atomic_write_u32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  pg_write_barrier () ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
TransactionGroupUpdateXidStatus(TransactionId xid, XidStatus status,
								XLogRecPtr lsn, int pageno)
{
	volatile PROC_HDR *procglobal = ProcGlobal;
	PGPROC	   *proc = MyProc;
	uint32		nextidx;
	uint32		wakeidx;

	/* We should definitely have an XID whose status needs to be updated. */
	Assert(TransactionIdIsValid(xid));

	/*
	 * Add ourselves to the list of processes needing a group XID status
	 * update.
	 */
	proc->clogGroupMember = true;
	proc->clogGroupMemberXid = xid;
	proc->clogGroupMemberXidStatus = status;
	proc->clogGroupMemberPage = pageno;
	proc->clogGroupMemberLsn = lsn;

	nextidx = pg_atomic_read_u32(&procglobal->clogGroupFirst);

	while (true)
	{
		/*
		 * Add the proc to list, if the clog page where we need to update the
		 * current transaction status is same as group leader's clog page.
		 *
		 * There is a race condition here, which is that after doing the below
		 * check and before adding this proc's clog update to a group, the
		 * group leader might have already finished the group update for this
		 * page and becomes group leader of another group. This will lead to a
		 * situation where a single group can have different clog page
		 * updates.  This isn't likely and will still work, just maybe a bit
		 * less efficiently.
		 */
		if (nextidx != INVALID_PGPROCNO &&
			ProcGlobal->allProcs[nextidx].clogGroupMemberPage != proc->clogGroupMemberPage)
		{
			proc->clogGroupMember = false;
			return false;
		}

		pg_atomic_write_u32(&proc->clogGroupNext, nextidx);

		if (pg_atomic_compare_exchange_u32(&procglobal->clogGroupFirst,
										   &nextidx,
										   (uint32) proc->pgprocno))
			break;
	}

	/*
	 * If the list was not empty, the leader will update the status of our
	 * XID. It is impossible to have followers without a leader because the
	 * first process that has added itself to the list will always have
	 * nextidx as INVALID_PGPROCNO.
	 */
	if (nextidx != INVALID_PGPROCNO)
	{
		int			extraWaits = 0;

		/* Sleep until the leader updates our XID status. */
		pgstat_report_wait_start(WAIT_EVENT_CLOG_GROUP_UPDATE);
		for (;;)
		{
			/* acts as a read barrier */
			PGSemaphoreLock(proc->sem);
			if (!proc->clogGroupMember)
				break;
			extraWaits++;
		}
		pgstat_report_wait_end();

		Assert(pg_atomic_read_u32(&proc->clogGroupNext) == INVALID_PGPROCNO);

		/* Fix semaphore count for any absorbed wakeups */
		while (extraWaits-- > 0)
			PGSemaphoreUnlock(proc->sem);
		return true;
	}

	/* We are the leader.  Acquire the lock on behalf of everyone. */
	LWLockAcquire(CLogControlLock, LW_EXCLUSIVE);

	/*
	 * Now that we've got the lock, clear the list of processes waiting for
	 * group XID status update, saving a pointer to the head of the list.
	 * Trying to pop elements one at a time could lead to an ABA problem.
	 */
	nextidx = pg_atomic_exchange_u32(&procglobal->clogGroupFirst,
									 INVALID_PGPROCNO);

	/* Remember head of list so we can perform wakeups after dropping lock. */
	wakeidx = nextidx;

	/* Walk the list and update the status of all XIDs. */
	while (nextidx != INVALID_PGPROCNO)
	{
		PGPROC	   *proc = &ProcGlobal->allProcs[nextidx];
		PGXACT	   *pgxact = &ProcGlobal->allPgXact[nextidx];

		/*
		 * Overflowed transactions should not use group XID status update
		 * mechanism.
		 */
		Assert(!pgxact->overflowed);

		TransactionIdSetPageStatusInternal(proc->clogGroupMemberXid,
										   pgxact->nxids,
										   proc->subxids.xids,
										   proc->clogGroupMemberXidStatus,
										   proc->clogGroupMemberLsn,
										   proc->clogGroupMemberPage);

		/* Move to next proc in list. */
		nextidx = pg_atomic_read_u32(&proc->clogGroupNext);
	}

	/* We're done with the lock now. */
	LWLockRelease(CLogControlLock);

	/*
	 * Now that we've released the lock, go back and wake everybody up.  We
	 * don't do this under the lock so as to keep lock hold times to a
	 * minimum.
	 */
	while (wakeidx != INVALID_PGPROCNO)
	{
		PGPROC	   *proc = &ProcGlobal->allProcs[wakeidx];

		wakeidx = pg_atomic_read_u32(&proc->clogGroupNext);
		pg_atomic_write_u32(&proc->clogGroupNext, INVALID_PGPROCNO);

		/* ensure all previous writes are visible before follower continues. */
		pg_write_barrier();

		proc->clogGroupMember = false;

		if (proc != MyProc)
			PGSemaphoreUnlock(proc->sem);
	}

	return true;
}