#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_9__ {size_t pgprocno; int recoveryConflictPending; int /*<<< orphan*/  lxid; } ;
struct TYPE_8__ {int delayChkpt; scalar_t__ nxids; int overflowed; int /*<<< orphan*/  vacuumFlags; int /*<<< orphan*/  xmin; int /*<<< orphan*/  xid; } ;
typedef  TYPE_1__ PGXACT ;
typedef  TYPE_2__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  InvalidLocalTransactionId ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 scalar_t__ LWLockConditionalAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  PROC_VACUUM_STATE_MASK ; 
 int /*<<< orphan*/  ProcArrayEndTransactionInternal (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcArrayGroupClearXid (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 TYPE_1__* allPgXact ; 

void
ProcArrayEndTransaction(PGPROC *proc, TransactionId latestXid)
{
	PGXACT	   *pgxact = &allPgXact[proc->pgprocno];

	if (TransactionIdIsValid(latestXid))
	{
		/*
		 * We must lock ProcArrayLock while clearing our advertised XID, so
		 * that we do not exit the set of "running" transactions while someone
		 * else is taking a snapshot.  See discussion in
		 * src/backend/access/transam/README.
		 */
		Assert(TransactionIdIsValid(allPgXact[proc->pgprocno].xid));

		/*
		 * If we can immediately acquire ProcArrayLock, we clear our own XID
		 * and release the lock.  If not, use group XID clearing to improve
		 * efficiency.
		 */
		if (LWLockConditionalAcquire(ProcArrayLock, LW_EXCLUSIVE))
		{
			ProcArrayEndTransactionInternal(proc, pgxact, latestXid);
			LWLockRelease(ProcArrayLock);
		}
		else
			ProcArrayGroupClearXid(proc, latestXid);
	}
	else
	{
		/*
		 * If we have no XID, we don't need to lock, since we won't affect
		 * anyone else's calculation of a snapshot.  We might change their
		 * estimate of global xmin, but that's OK.
		 */
		Assert(!TransactionIdIsValid(allPgXact[proc->pgprocno].xid));

		proc->lxid = InvalidLocalTransactionId;
		pgxact->xmin = InvalidTransactionId;
		/* must be cleared with xid/xmin: */
		pgxact->vacuumFlags &= ~PROC_VACUUM_STATE_MASK;
		pgxact->delayChkpt = false; /* be sure this is cleared in abort */
		proc->recoveryConflictPending = false;

		Assert(pgxact->nxids == 0);
		Assert(pgxact->overflowed == false);
	}
}