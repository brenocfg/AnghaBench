#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ph_node; int /*<<< orphan*/  regd_count; } ;
typedef  TYPE_1__* Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* CopySnapshot (TYPE_1__*) ; 
 TYPE_1__* CurrentSnapshot ; 
 int /*<<< orphan*/  CurrentSnapshotData ; 
 int /*<<< orphan*/  ERROR ; 
 int FirstSnapshotSet ; 
 TYPE_1__* FirstXactSnapshot ; 
 TYPE_1__* GetSerializableTransactionSnapshot (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetSnapshotData (int /*<<< orphan*/ *) ; 
 TYPE_1__* HistoricSnapshot ; 
 scalar_t__ HistoricSnapshotActive () ; 
 int /*<<< orphan*/  InvalidateCatalogSnapshot () ; 
 scalar_t__ IsInParallelMode () ; 
 scalar_t__ IsolationIsSerializable () ; 
 scalar_t__ IsolationUsesXactSnapshot () ; 
 int /*<<< orphan*/  RegisteredSnapshots ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pairingheap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pairingheap_is_empty (int /*<<< orphan*/ *) ; 

Snapshot
GetTransactionSnapshot(void)
{
	/*
	 * Return historic snapshot if doing logical decoding. We'll never need a
	 * non-historic transaction snapshot in this (sub-)transaction, so there's
	 * no need to be careful to set one up for later calls to
	 * GetTransactionSnapshot().
	 */
	if (HistoricSnapshotActive())
	{
		Assert(!FirstSnapshotSet);
		return HistoricSnapshot;
	}

	/* First call in transaction? */
	if (!FirstSnapshotSet)
	{
		/*
		 * Don't allow catalog snapshot to be older than xact snapshot.  Must
		 * do this first to allow the empty-heap Assert to succeed.
		 */
		InvalidateCatalogSnapshot();

		Assert(pairingheap_is_empty(&RegisteredSnapshots));
		Assert(FirstXactSnapshot == NULL);

		if (IsInParallelMode())
			elog(ERROR,
				 "cannot take query snapshot during a parallel operation");

		/*
		 * In transaction-snapshot mode, the first snapshot must live until
		 * end of xact regardless of what the caller does with it, so we must
		 * make a copy of it rather than returning CurrentSnapshotData
		 * directly.  Furthermore, if we're running in serializable mode,
		 * predicate.c needs to wrap the snapshot fetch in its own processing.
		 */
		if (IsolationUsesXactSnapshot())
		{
			/* First, create the snapshot in CurrentSnapshotData */
			if (IsolationIsSerializable())
				CurrentSnapshot = GetSerializableTransactionSnapshot(&CurrentSnapshotData);
			else
				CurrentSnapshot = GetSnapshotData(&CurrentSnapshotData);
			/* Make a saved copy */
			CurrentSnapshot = CopySnapshot(CurrentSnapshot);
			FirstXactSnapshot = CurrentSnapshot;
			/* Mark it as "registered" in FirstXactSnapshot */
			FirstXactSnapshot->regd_count++;
			pairingheap_add(&RegisteredSnapshots, &FirstXactSnapshot->ph_node);
		}
		else
			CurrentSnapshot = GetSnapshotData(&CurrentSnapshotData);

		FirstSnapshotSet = true;
		return CurrentSnapshot;
	}

	if (IsolationUsesXactSnapshot())
		return CurrentSnapshot;

	/* Don't allow catalog snapshot to be older than xact snapshot. */
	InvalidateCatalogSnapshot();

	CurrentSnapshot = GetSnapshotData(&CurrentSnapshotData);

	return CurrentSnapshot;
}