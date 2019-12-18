#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_12__ {int /*<<< orphan*/  xmin; } ;
struct TYPE_9__ {int /*<<< orphan*/  includes_all_transactions; } ;
struct TYPE_11__ {scalar_t__ state; TYPE_1__ committed; } ;
struct TYPE_10__ {int xcnt; int /*<<< orphan*/ * xip; int /*<<< orphan*/  snapshot_type; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; } ;
typedef  TYPE_2__* Snapshot ;
typedef  TYPE_3__ SnapBuild ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_T_R_SERIALIZATION_FAILURE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FirstSnapshotSet ; 
 int GetMaxSnapshotXidCount () ; 
 int /*<<< orphan*/  GetOldestSafeDecodingTransactionId (int) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 TYPE_8__* MyPgXact ; 
 scalar_t__ NormalTransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcArrayLock ; 
 scalar_t__ SNAPBUILD_CONSISTENT ; 
 int /*<<< orphan*/  SNAPSHOT_MVCC ; 
 TYPE_2__* SnapBuildBuildSnapshot (TYPE_3__*) ; 
 int /*<<< orphan*/  TransactionIdAdvance (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int TransactionIdPrecedesOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XACT_REPEATABLE_READ ; 
 scalar_t__ XactIsoLevel ; 
 void* bsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  xidComparator ; 

Snapshot
SnapBuildInitialSnapshot(SnapBuild *builder)
{
	Snapshot	snap;
	TransactionId xid;
	TransactionId *newxip;
	int			newxcnt = 0;

	Assert(!FirstSnapshotSet);
	Assert(XactIsoLevel == XACT_REPEATABLE_READ);

	if (builder->state != SNAPBUILD_CONSISTENT)
		elog(ERROR, "cannot build an initial slot snapshot before reaching a consistent state");

	if (!builder->committed.includes_all_transactions)
		elog(ERROR, "cannot build an initial slot snapshot, not all transactions are monitored anymore");

	/* so we don't overwrite the existing value */
	if (TransactionIdIsValid(MyPgXact->xmin))
		elog(ERROR, "cannot build an initial slot snapshot when MyPgXact->xmin already is valid");

	snap = SnapBuildBuildSnapshot(builder);

	/*
	 * We know that snap->xmin is alive, enforced by the logical xmin
	 * mechanism. Due to that we can do this without locks, we're only
	 * changing our own value.
	 */
#ifdef USE_ASSERT_CHECKING
	{
		TransactionId safeXid;

		LWLockAcquire(ProcArrayLock, LW_SHARED);
		safeXid = GetOldestSafeDecodingTransactionId(false);
		LWLockRelease(ProcArrayLock);

		Assert(TransactionIdPrecedesOrEquals(safeXid, snap->xmin));
	}
#endif

	MyPgXact->xmin = snap->xmin;

	/* allocate in transaction context */
	newxip = (TransactionId *)
		palloc(sizeof(TransactionId) * GetMaxSnapshotXidCount());

	/*
	 * snapbuild.c builds transactions in an "inverted" manner, which means it
	 * stores committed transactions in ->xip, not ones in progress. Build a
	 * classical snapshot by marking all non-committed transactions as
	 * in-progress. This can be expensive.
	 */
	for (xid = snap->xmin; NormalTransactionIdPrecedes(xid, snap->xmax);)
	{
		void	   *test;

		/*
		 * Check whether transaction committed using the decoding snapshot
		 * meaning of ->xip.
		 */
		test = bsearch(&xid, snap->xip, snap->xcnt,
					   sizeof(TransactionId), xidComparator);

		if (test == NULL)
		{
			if (newxcnt >= GetMaxSnapshotXidCount())
				ereport(ERROR,
						(errcode(ERRCODE_T_R_SERIALIZATION_FAILURE),
						 errmsg("initial slot snapshot too large")));

			newxip[newxcnt++] = xid;
		}

		TransactionIdAdvance(xid);
	}

	/* adjust remaining snapshot fields as needed */
	snap->snapshot_type = SNAPSHOT_MVCC;
	snap->xcnt = newxcnt;
	snap->xip = newxip;

	return snap;
}