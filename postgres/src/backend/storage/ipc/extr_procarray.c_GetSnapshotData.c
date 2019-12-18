#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* TransactionId ;
struct TYPE_18__ {void* latestCompletedXid; } ;
struct TYPE_13__ {scalar_t__ xids; } ;
struct TYPE_17__ {TYPE_1__ subxids; } ;
struct TYPE_16__ {int vacuumFlags; void* xmin; void* xid; int nxids; scalar_t__ overflowed; } ;
struct TYPE_15__ {int* pgprocnos; int numProcs; void* replication_slot_catalog_xmin; void* replication_slot_xmin; int /*<<< orphan*/  lastOverflowedXid; } ;
struct TYPE_14__ {void** xip; void** subxip; int xcnt; int subxcnt; int suboverflowed; int copied; scalar_t__ whenTaken; int /*<<< orphan*/  lsn; scalar_t__ regd_count; scalar_t__ active_count; int /*<<< orphan*/  curcid; void* xmax; void* xmin; int /*<<< orphan*/  takenDuringRecovery; } ;
typedef  TYPE_2__* Snapshot ;
typedef  TYPE_3__ ProcArrayStruct ;
typedef  TYPE_4__ PGXACT ;
typedef  TYPE_5__ PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 void* FirstNormalTransactionId ; 
 int /*<<< orphan*/  GetCurrentCommandId (int) ; 
 int GetMaxSnapshotSubxidCount () ; 
 int GetMaxSnapshotXidCount () ; 
 scalar_t__ GetSnapshotCurrentTimestamp () ; 
 int /*<<< orphan*/  GetXLogInsertRecPtr () ; 
 void* InvalidTransactionId ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 int KnownAssignedXidsGetAndSetXmin (void**,void**,void*) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  MaintainOldSnapshotTimeMapping (scalar_t__,void*) ; 
 TYPE_4__* MyPgXact ; 
 scalar_t__ NormalTransactionIdPrecedes (void*,void*) ; 
 int PROC_IN_LOGICAL_DECODING ; 
 int PROC_IN_VACUUM ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 void* RecentGlobalDataXmin ; 
 void* RecentGlobalXmin ; 
 void* RecentXmin ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 TYPE_9__* ShmemVariableCache ; 
 int /*<<< orphan*/  TransactionIdAdvance (void*) ; 
 scalar_t__ TransactionIdIsNormal (void*) ; 
 scalar_t__ TransactionIdIsValid (void*) ; 
 scalar_t__ TransactionIdPrecedes (void*,void*) ; 
 scalar_t__ TransactionIdPrecedesOrEquals (void*,int /*<<< orphan*/ ) ; 
 void* TransactionXmin ; 
 void* UINT32_ACCESS_ONCE (void*) ; 
 TYPE_4__* allPgXact ; 
 TYPE_5__* allProcs ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (void**,void*,int) ; 
 scalar_t__ old_snapshot_threshold ; 
 int /*<<< orphan*/  pg_read_barrier () ; 
 TYPE_3__* procArray ; 
 void* vacuum_defer_cleanup_age ; 

Snapshot
GetSnapshotData(Snapshot snapshot)
{
	ProcArrayStruct *arrayP = procArray;
	TransactionId xmin;
	TransactionId xmax;
	TransactionId globalxmin;
	int			index;
	int			count = 0;
	int			subcount = 0;
	bool		suboverflowed = false;
	TransactionId replication_slot_xmin = InvalidTransactionId;
	TransactionId replication_slot_catalog_xmin = InvalidTransactionId;

	Assert(snapshot != NULL);

	/*
	 * Allocating space for maxProcs xids is usually overkill; numProcs would
	 * be sufficient.  But it seems better to do the malloc while not holding
	 * the lock, so we can't look at numProcs.  Likewise, we allocate much
	 * more subxip storage than is probably needed.
	 *
	 * This does open a possibility for avoiding repeated malloc/free: since
	 * maxProcs does not change at runtime, we can simply reuse the previous
	 * xip arrays if any.  (This relies on the fact that all callers pass
	 * static SnapshotData structs.)
	 */
	if (snapshot->xip == NULL)
	{
		/*
		 * First call for this snapshot. Snapshot is same size whether or not
		 * we are in recovery, see later comments.
		 */
		snapshot->xip = (TransactionId *)
			malloc(GetMaxSnapshotXidCount() * sizeof(TransactionId));
		if (snapshot->xip == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
		Assert(snapshot->subxip == NULL);
		snapshot->subxip = (TransactionId *)
			malloc(GetMaxSnapshotSubxidCount() * sizeof(TransactionId));
		if (snapshot->subxip == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
	}

	/*
	 * It is sufficient to get shared lock on ProcArrayLock, even if we are
	 * going to set MyPgXact->xmin.
	 */
	LWLockAcquire(ProcArrayLock, LW_SHARED);

	/* xmax is always latestCompletedXid + 1 */
	xmax = ShmemVariableCache->latestCompletedXid;
	Assert(TransactionIdIsNormal(xmax));
	TransactionIdAdvance(xmax);

	/* initialize xmin calculation with xmax */
	globalxmin = xmin = xmax;

	snapshot->takenDuringRecovery = RecoveryInProgress();

	if (!snapshot->takenDuringRecovery)
	{
		int		   *pgprocnos = arrayP->pgprocnos;
		int			numProcs;

		/*
		 * Spin over procArray checking xid, xmin, and subxids.  The goal is
		 * to gather all active xids, find the lowest xmin, and try to record
		 * subxids.
		 */
		numProcs = arrayP->numProcs;
		for (index = 0; index < numProcs; index++)
		{
			int			pgprocno = pgprocnos[index];
			PGXACT	   *pgxact = &allPgXact[pgprocno];
			TransactionId xid;

			/*
			 * Skip over backends doing logical decoding which manages xmin
			 * separately (check below) and ones running LAZY VACUUM.
			 */
			if (pgxact->vacuumFlags &
				(PROC_IN_LOGICAL_DECODING | PROC_IN_VACUUM))
				continue;

			/* Update globalxmin to be the smallest valid xmin */
			xid = UINT32_ACCESS_ONCE(pgxact->xmin);
			if (TransactionIdIsNormal(xid) &&
				NormalTransactionIdPrecedes(xid, globalxmin))
				globalxmin = xid;

			/* Fetch xid just once - see GetNewTransactionId */
			xid = UINT32_ACCESS_ONCE(pgxact->xid);

			/*
			 * If the transaction has no XID assigned, we can skip it; it
			 * won't have sub-XIDs either.  If the XID is >= xmax, we can also
			 * skip it; such transactions will be treated as running anyway
			 * (and any sub-XIDs will also be >= xmax).
			 */
			if (!TransactionIdIsNormal(xid)
				|| !NormalTransactionIdPrecedes(xid, xmax))
				continue;

			/*
			 * We don't include our own XIDs (if any) in the snapshot, but we
			 * must include them in xmin.
			 */
			if (NormalTransactionIdPrecedes(xid, xmin))
				xmin = xid;
			if (pgxact == MyPgXact)
				continue;

			/* Add XID to snapshot. */
			snapshot->xip[count++] = xid;

			/*
			 * Save subtransaction XIDs if possible (if we've already
			 * overflowed, there's no point).  Note that the subxact XIDs must
			 * be later than their parent, so no need to check them against
			 * xmin.  We could filter against xmax, but it seems better not to
			 * do that much work while holding the ProcArrayLock.
			 *
			 * The other backend can add more subxids concurrently, but cannot
			 * remove any.  Hence it's important to fetch nxids just once.
			 * Should be safe to use memcpy, though.  (We needn't worry about
			 * missing any xids added concurrently, because they must postdate
			 * xmax.)
			 *
			 * Again, our own XIDs are not included in the snapshot.
			 */
			if (!suboverflowed)
			{
				if (pgxact->overflowed)
					suboverflowed = true;
				else
				{
					int			nxids = pgxact->nxids;

					if (nxids > 0)
					{
						PGPROC	   *proc = &allProcs[pgprocno];

						pg_read_barrier();	/* pairs with GetNewTransactionId */

						memcpy(snapshot->subxip + subcount,
							   (void *) proc->subxids.xids,
							   nxids * sizeof(TransactionId));
						subcount += nxids;
					}
				}
			}
		}
	}
	else
	{
		/*
		 * We're in hot standby, so get XIDs from KnownAssignedXids.
		 *
		 * We store all xids directly into subxip[]. Here's why:
		 *
		 * In recovery we don't know which xids are top-level and which are
		 * subxacts, a design choice that greatly simplifies xid processing.
		 *
		 * It seems like we would want to try to put xids into xip[] only, but
		 * that is fairly small. We would either need to make that bigger or
		 * to increase the rate at which we WAL-log xid assignment; neither is
		 * an appealing choice.
		 *
		 * We could try to store xids into xip[] first and then into subxip[]
		 * if there are too many xids. That only works if the snapshot doesn't
		 * overflow because we do not search subxip[] in that case. A simpler
		 * way is to just store all xids in the subxact array because this is
		 * by far the bigger array. We just leave the xip array empty.
		 *
		 * Either way we need to change the way XidInMVCCSnapshot() works
		 * depending upon when the snapshot was taken, or change normal
		 * snapshot processing so it matches.
		 *
		 * Note: It is possible for recovery to end before we finish taking
		 * the snapshot, and for newly assigned transaction ids to be added to
		 * the ProcArray.  xmax cannot change while we hold ProcArrayLock, so
		 * those newly added transaction ids would be filtered away, so we
		 * need not be concerned about them.
		 */
		subcount = KnownAssignedXidsGetAndSetXmin(snapshot->subxip, &xmin,
												  xmax);

		if (TransactionIdPrecedesOrEquals(xmin, procArray->lastOverflowedXid))
			suboverflowed = true;
	}


	/*
	 * Fetch into local variable while ProcArrayLock is held - the
	 * LWLockRelease below is a barrier, ensuring this happens inside the
	 * lock.
	 */
	replication_slot_xmin = procArray->replication_slot_xmin;
	replication_slot_catalog_xmin = procArray->replication_slot_catalog_xmin;

	if (!TransactionIdIsValid(MyPgXact->xmin))
		MyPgXact->xmin = TransactionXmin = xmin;

	LWLockRelease(ProcArrayLock);

	/*
	 * Update globalxmin to include actual process xids.  This is a slightly
	 * different way of computing it than GetOldestXmin uses, but should give
	 * the same result.
	 */
	if (TransactionIdPrecedes(xmin, globalxmin))
		globalxmin = xmin;

	/* Update global variables too */
	RecentGlobalXmin = globalxmin - vacuum_defer_cleanup_age;
	if (!TransactionIdIsNormal(RecentGlobalXmin))
		RecentGlobalXmin = FirstNormalTransactionId;

	/* Check whether there's a replication slot requiring an older xmin. */
	if (TransactionIdIsValid(replication_slot_xmin) &&
		NormalTransactionIdPrecedes(replication_slot_xmin, RecentGlobalXmin))
		RecentGlobalXmin = replication_slot_xmin;

	/* Non-catalog tables can be vacuumed if older than this xid */
	RecentGlobalDataXmin = RecentGlobalXmin;

	/*
	 * Check whether there's a replication slot requiring an older catalog
	 * xmin.
	 */
	if (TransactionIdIsNormal(replication_slot_catalog_xmin) &&
		NormalTransactionIdPrecedes(replication_slot_catalog_xmin, RecentGlobalXmin))
		RecentGlobalXmin = replication_slot_catalog_xmin;

	RecentXmin = xmin;

	snapshot->xmin = xmin;
	snapshot->xmax = xmax;
	snapshot->xcnt = count;
	snapshot->subxcnt = subcount;
	snapshot->suboverflowed = suboverflowed;

	snapshot->curcid = GetCurrentCommandId(false);

	/*
	 * This is a new snapshot, so set both refcounts are zero, and mark it as
	 * not copied in persistent memory.
	 */
	snapshot->active_count = 0;
	snapshot->regd_count = 0;
	snapshot->copied = false;

	if (old_snapshot_threshold < 0)
	{
		/*
		 * If not using "snapshot too old" feature, fill related fields with
		 * dummy values that don't require any locking.
		 */
		snapshot->lsn = InvalidXLogRecPtr;
		snapshot->whenTaken = 0;
	}
	else
	{
		/*
		 * Capture the current time and WAL stream location in case this
		 * snapshot becomes old enough to need to fall back on the special
		 * "old snapshot" logic.
		 */
		snapshot->lsn = GetXLogInsertRecPtr();
		snapshot->whenTaken = GetSnapshotCurrentTimestamp();
		MaintainOldSnapshotTimeMapping(snapshot->whenTaken, xmin);
	}

	return snapshot;
}