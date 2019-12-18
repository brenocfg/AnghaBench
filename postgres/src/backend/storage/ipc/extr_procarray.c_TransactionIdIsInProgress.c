#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_14__ {int /*<<< orphan*/  latestCompletedXid; } ;
struct TYPE_10__ {int /*<<< orphan*/ * xids; } ;
struct TYPE_13__ {TYPE_1__ subxids; } ;
struct TYPE_12__ {int nxids; scalar_t__ overflowed; int /*<<< orphan*/  xid; } ;
struct TYPE_11__ {int maxProcs; int numProcs; int* pgprocnos; int /*<<< orphan*/  lastOverflowedXid; } ;
typedef  TYPE_2__ ProcArrayStruct ;
typedef  TYPE_3__ PGXACT ;
typedef  TYPE_4__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ KnownAssignedXidExists (int /*<<< orphan*/ ) ; 
 int KnownAssignedXidsGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 TYPE_4__* MyProc ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 int /*<<< orphan*/  RecentXmin ; 
 scalar_t__ RecoveryInProgress () ; 
 TYPE_8__* ShmemVariableCache ; 
 int /*<<< orphan*/  SubTransGetTopmostTransaction (int /*<<< orphan*/ ) ; 
 int TOTAL_MAX_CACHED_SUBXIDS ; 
 scalar_t__ TransactionIdDidAbort (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsKnownCompleted (int /*<<< orphan*/ ) ; 
 int TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedesOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT32_ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_3__* allPgXact ; 
 TYPE_4__* allProcs ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pg_read_barrier () ; 
 TYPE_2__* procArray ; 
 int /*<<< orphan*/  xc_by_child_xid_inc () ; 
 int /*<<< orphan*/  xc_by_known_assigned_inc () ; 
 int /*<<< orphan*/  xc_by_known_xact_inc () ; 
 int /*<<< orphan*/  xc_by_latest_xid_inc () ; 
 int /*<<< orphan*/  xc_by_main_xid_inc () ; 
 int /*<<< orphan*/  xc_by_my_xact_inc () ; 
 int /*<<< orphan*/  xc_by_recent_xmin_inc () ; 
 int /*<<< orphan*/  xc_no_overflow_inc () ; 
 int /*<<< orphan*/  xc_slow_answer_inc () ; 

bool
TransactionIdIsInProgress(TransactionId xid)
{
	static TransactionId *xids = NULL;
	int			nxids = 0;
	ProcArrayStruct *arrayP = procArray;
	TransactionId topxid;
	int			i,
				j;

	/*
	 * Don't bother checking a transaction older than RecentXmin; it could not
	 * possibly still be running.  (Note: in particular, this guarantees that
	 * we reject InvalidTransactionId, FrozenTransactionId, etc as not
	 * running.)
	 */
	if (TransactionIdPrecedes(xid, RecentXmin))
	{
		xc_by_recent_xmin_inc();
		return false;
	}

	/*
	 * We may have just checked the status of this transaction, so if it is
	 * already known to be completed, we can fall out without any access to
	 * shared memory.
	 */
	if (TransactionIdIsKnownCompleted(xid))
	{
		xc_by_known_xact_inc();
		return false;
	}

	/*
	 * Also, we can handle our own transaction (and subtransactions) without
	 * any access to shared memory.
	 */
	if (TransactionIdIsCurrentTransactionId(xid))
	{
		xc_by_my_xact_inc();
		return true;
	}

	/*
	 * If first time through, get workspace to remember main XIDs in. We
	 * malloc it permanently to avoid repeated palloc/pfree overhead.
	 */
	if (xids == NULL)
	{
		/*
		 * In hot standby mode, reserve enough space to hold all xids in the
		 * known-assigned list. If we later finish recovery, we no longer need
		 * the bigger array, but we don't bother to shrink it.
		 */
		int			maxxids = RecoveryInProgress() ? TOTAL_MAX_CACHED_SUBXIDS : arrayP->maxProcs;

		xids = (TransactionId *) malloc(maxxids * sizeof(TransactionId));
		if (xids == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
	}

	LWLockAcquire(ProcArrayLock, LW_SHARED);

	/*
	 * Now that we have the lock, we can check latestCompletedXid; if the
	 * target Xid is after that, it's surely still running.
	 */
	if (TransactionIdPrecedes(ShmemVariableCache->latestCompletedXid, xid))
	{
		LWLockRelease(ProcArrayLock);
		xc_by_latest_xid_inc();
		return true;
	}

	/* No shortcuts, gotta grovel through the array */
	for (i = 0; i < arrayP->numProcs; i++)
	{
		int			pgprocno = arrayP->pgprocnos[i];
		PGPROC	   *proc = &allProcs[pgprocno];
		PGXACT	   *pgxact = &allPgXact[pgprocno];
		TransactionId pxid;
		int			pxids;

		/* Ignore my own proc --- dealt with it above */
		if (proc == MyProc)
			continue;

		/* Fetch xid just once - see GetNewTransactionId */
		pxid = UINT32_ACCESS_ONCE(pgxact->xid);

		if (!TransactionIdIsValid(pxid))
			continue;

		/*
		 * Step 1: check the main Xid
		 */
		if (TransactionIdEquals(pxid, xid))
		{
			LWLockRelease(ProcArrayLock);
			xc_by_main_xid_inc();
			return true;
		}

		/*
		 * We can ignore main Xids that are younger than the target Xid, since
		 * the target could not possibly be their child.
		 */
		if (TransactionIdPrecedes(xid, pxid))
			continue;

		/*
		 * Step 2: check the cached child-Xids arrays
		 */
		pxids = pgxact->nxids;
		pg_read_barrier();		/* pairs with barrier in GetNewTransactionId() */
		for (j = pxids - 1; j >= 0; j--)
		{
			/* Fetch xid just once - see GetNewTransactionId */
			TransactionId cxid = UINT32_ACCESS_ONCE(proc->subxids.xids[j]);

			if (TransactionIdEquals(cxid, xid))
			{
				LWLockRelease(ProcArrayLock);
				xc_by_child_xid_inc();
				return true;
			}
		}

		/*
		 * Save the main Xid for step 4.  We only need to remember main Xids
		 * that have uncached children.  (Note: there is no race condition
		 * here because the overflowed flag cannot be cleared, only set, while
		 * we hold ProcArrayLock.  So we can't miss an Xid that we need to
		 * worry about.)
		 */
		if (pgxact->overflowed)
			xids[nxids++] = pxid;
	}

	/*
	 * Step 3: in hot standby mode, check the known-assigned-xids list.  XIDs
	 * in the list must be treated as running.
	 */
	if (RecoveryInProgress())
	{
		/* none of the PGXACT entries should have XIDs in hot standby mode */
		Assert(nxids == 0);

		if (KnownAssignedXidExists(xid))
		{
			LWLockRelease(ProcArrayLock);
			xc_by_known_assigned_inc();
			return true;
		}

		/*
		 * If the KnownAssignedXids overflowed, we have to check pg_subtrans
		 * too.  Fetch all xids from KnownAssignedXids that are lower than
		 * xid, since if xid is a subtransaction its parent will always have a
		 * lower value.  Note we will collect both main and subXIDs here, but
		 * there's no help for it.
		 */
		if (TransactionIdPrecedesOrEquals(xid, procArray->lastOverflowedXid))
			nxids = KnownAssignedXidsGet(xids, xid);
	}

	LWLockRelease(ProcArrayLock);

	/*
	 * If none of the relevant caches overflowed, we know the Xid is not
	 * running without even looking at pg_subtrans.
	 */
	if (nxids == 0)
	{
		xc_no_overflow_inc();
		return false;
	}

	/*
	 * Step 4: have to check pg_subtrans.
	 *
	 * At this point, we know it's either a subtransaction of one of the Xids
	 * in xids[], or it's not running.  If it's an already-failed
	 * subtransaction, we want to say "not running" even though its parent may
	 * still be running.  So first, check pg_xact to see if it's been aborted.
	 */
	xc_slow_answer_inc();

	if (TransactionIdDidAbort(xid))
		return false;

	/*
	 * It isn't aborted, so check whether the transaction tree it belongs to
	 * is still running (or, more precisely, whether it was running when we
	 * held ProcArrayLock).
	 */
	topxid = SubTransGetTopmostTransaction(xid);
	Assert(TransactionIdIsValid(topxid));
	if (!TransactionIdEquals(topxid, xid))
	{
		for (i = 0; i < nxids; i++)
		{
			if (TransactionIdEquals(xids[i], topxid))
				return true;
		}
	}

	return false;
}