#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VirtualTransactionId ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_10__ {int xcnt; int subxcnt; int /*<<< orphan*/  ph_node; int /*<<< orphan*/  regd_count; int /*<<< orphan*/  xmin; int /*<<< orphan*/  takenDuringRecovery; int /*<<< orphan*/  suboverflowed; int /*<<< orphan*/  subxip; int /*<<< orphan*/  xip; int /*<<< orphan*/  xmax; } ;
struct TYPE_9__ {int xcnt; int subxcnt; int /*<<< orphan*/  takenDuringRecovery; int /*<<< orphan*/  suboverflowed; int /*<<< orphan*/  subxip; int /*<<< orphan*/  xip; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; } ;
typedef  TYPE_1__* Snapshot ;
typedef  int /*<<< orphan*/  PGPROC ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_3__* CopySnapshot (TYPE_3__*) ; 
 TYPE_3__* CurrentSnapshot ; 
 int /*<<< orphan*/  CurrentSnapshotData ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int FirstSnapshotSet ; 
 TYPE_3__* FirstXactSnapshot ; 
 int GetMaxSnapshotSubxidCount () ; 
 int GetMaxSnapshotXidCount () ; 
 TYPE_3__* GetSnapshotData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HistoricSnapshotActive () ; 
 int /*<<< orphan*/  InvalidateCatalogSnapshot () ; 
 scalar_t__ IsolationIsSerializable () ; 
 scalar_t__ IsolationUsesXactSnapshot () ; 
 int /*<<< orphan*/  ProcArrayInstallImportedXmin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProcArrayInstallRestoredXmin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisteredSnapshots ; 
 int /*<<< orphan*/  SetSerializableTransactionSnapshot (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,...) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pairingheap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pairingheap_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
SetTransactionSnapshot(Snapshot sourcesnap, VirtualTransactionId *sourcevxid,
					   int sourcepid, PGPROC *sourceproc)
{
	/* Caller should have checked this already */
	Assert(!FirstSnapshotSet);

	/* Better do this to ensure following Assert succeeds. */
	InvalidateCatalogSnapshot();

	Assert(pairingheap_is_empty(&RegisteredSnapshots));
	Assert(FirstXactSnapshot == NULL);
	Assert(!HistoricSnapshotActive());

	/*
	 * Even though we are not going to use the snapshot it computes, we must
	 * call GetSnapshotData, for two reasons: (1) to be sure that
	 * CurrentSnapshotData's XID arrays have been allocated, and (2) to update
	 * RecentXmin and RecentGlobalXmin.  (We could alternatively include those
	 * two variables in exported snapshot files, but it seems better to have
	 * snapshot importers compute reasonably up-to-date values for them.)
	 */
	CurrentSnapshot = GetSnapshotData(&CurrentSnapshotData);

	/*
	 * Now copy appropriate fields from the source snapshot.
	 */
	CurrentSnapshot->xmin = sourcesnap->xmin;
	CurrentSnapshot->xmax = sourcesnap->xmax;
	CurrentSnapshot->xcnt = sourcesnap->xcnt;
	Assert(sourcesnap->xcnt <= GetMaxSnapshotXidCount());
	memcpy(CurrentSnapshot->xip, sourcesnap->xip,
		   sourcesnap->xcnt * sizeof(TransactionId));
	CurrentSnapshot->subxcnt = sourcesnap->subxcnt;
	Assert(sourcesnap->subxcnt <= GetMaxSnapshotSubxidCount());
	memcpy(CurrentSnapshot->subxip, sourcesnap->subxip,
		   sourcesnap->subxcnt * sizeof(TransactionId));
	CurrentSnapshot->suboverflowed = sourcesnap->suboverflowed;
	CurrentSnapshot->takenDuringRecovery = sourcesnap->takenDuringRecovery;
	/* NB: curcid should NOT be copied, it's a local matter */

	/*
	 * Now we have to fix what GetSnapshotData did with MyPgXact->xmin and
	 * TransactionXmin.  There is a race condition: to make sure we are not
	 * causing the global xmin to go backwards, we have to test that the
	 * source transaction is still running, and that has to be done
	 * atomically. So let procarray.c do it.
	 *
	 * Note: in serializable mode, predicate.c will do this a second time. It
	 * doesn't seem worth contorting the logic here to avoid two calls,
	 * especially since it's not clear that predicate.c *must* do this.
	 */
	if (sourceproc != NULL)
	{
		if (!ProcArrayInstallRestoredXmin(CurrentSnapshot->xmin, sourceproc))
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("could not import the requested snapshot"),
					 errdetail("The source transaction is not running anymore.")));
	}
	else if (!ProcArrayInstallImportedXmin(CurrentSnapshot->xmin, sourcevxid))
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("could not import the requested snapshot"),
				 errdetail("The source process with PID %d is not running anymore.",
						   sourcepid)));

	/*
	 * In transaction-snapshot mode, the first snapshot must live until end of
	 * xact, so we must make a copy of it.  Furthermore, if we're running in
	 * serializable mode, predicate.c needs to do its own processing.
	 */
	if (IsolationUsesXactSnapshot())
	{
		if (IsolationIsSerializable())
			SetSerializableTransactionSnapshot(CurrentSnapshot, sourcevxid,
											   sourcepid);
		/* Make a saved copy */
		CurrentSnapshot = CopySnapshot(CurrentSnapshot);
		FirstXactSnapshot = CurrentSnapshot;
		/* Mark it as "registered" in FirstXactSnapshot */
		FirstXactSnapshot->regd_count++;
		pairingheap_add(&RegisteredSnapshots, &FirstXactSnapshot->ph_node);
	}

	FirstSnapshotSet = true;
}