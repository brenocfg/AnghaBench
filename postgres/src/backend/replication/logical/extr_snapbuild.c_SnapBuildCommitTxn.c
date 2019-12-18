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
typedef  scalar_t__ XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_8__ {int includes_all_transactions; } ;
struct TYPE_9__ {scalar_t__ state; scalar_t__ start_decoding_at; scalar_t__ snapshot; int /*<<< orphan*/  reorder; int /*<<< orphan*/  xmax; TYPE_1__ committed; scalar_t__ building_full_snapshot; } ;
typedef  TYPE_2__ SnapBuild ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DEBUG2 ; 
 scalar_t__ NormalTransactionIdFollows (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReorderBufferSetBaseSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ReorderBufferXidHasBaseSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ReorderBufferXidHasCatalogChanges (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SNAPBUILD_BUILDING_SNAPSHOT ; 
 scalar_t__ SNAPBUILD_CONSISTENT ; 
 scalar_t__ SNAPBUILD_FULL_SNAPSHOT ; 
 scalar_t__ SNAPBUILD_START ; 
 int /*<<< orphan*/  SnapBuildAddCommittedTxn (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SnapBuildBuildSnapshot (TYPE_2__*) ; 
 int /*<<< orphan*/  SnapBuildDistributeNewCatalogSnapshot (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  SnapBuildNextPhaseAt (TYPE_2__*) ; 
 int /*<<< orphan*/  SnapBuildSnapDecRefcount (scalar_t__) ; 
 int /*<<< orphan*/  SnapBuildSnapIncRefcount (scalar_t__) ; 
 int /*<<< orphan*/  TransactionIdAdvance (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdFollowsOrEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void
SnapBuildCommitTxn(SnapBuild *builder, XLogRecPtr lsn, TransactionId xid,
				   int nsubxacts, TransactionId *subxacts)
{
	int			nxact;

	bool		needs_snapshot = false;
	bool		needs_timetravel = false;
	bool		sub_needs_timetravel = false;

	TransactionId xmax = xid;

	/*
	 * Transactions preceding BUILDING_SNAPSHOT will neither be decoded, nor
	 * will they be part of a snapshot.  So we don't need to record anything.
	 */
	if (builder->state == SNAPBUILD_START ||
		(builder->state == SNAPBUILD_BUILDING_SNAPSHOT &&
		 TransactionIdPrecedes(xid, SnapBuildNextPhaseAt(builder))))
	{
		/* ensure that only commits after this are getting replayed */
		if (builder->start_decoding_at <= lsn)
			builder->start_decoding_at = lsn + 1;
		return;
	}

	if (builder->state < SNAPBUILD_CONSISTENT)
	{
		/* ensure that only commits after this are getting replayed */
		if (builder->start_decoding_at <= lsn)
			builder->start_decoding_at = lsn + 1;

		/*
		 * If building an exportable snapshot, force xid to be tracked, even
		 * if the transaction didn't modify the catalog.
		 */
		if (builder->building_full_snapshot)
		{
			needs_timetravel = true;
		}
	}

	for (nxact = 0; nxact < nsubxacts; nxact++)
	{
		TransactionId subxid = subxacts[nxact];

		/*
		 * Add subtransaction to base snapshot if catalog modifying, we don't
		 * distinguish to toplevel transactions there.
		 */
		if (ReorderBufferXidHasCatalogChanges(builder->reorder, subxid))
		{
			sub_needs_timetravel = true;
			needs_snapshot = true;

			elog(DEBUG1, "found subtransaction %u:%u with catalog changes",
				 xid, subxid);

			SnapBuildAddCommittedTxn(builder, subxid);

			if (NormalTransactionIdFollows(subxid, xmax))
				xmax = subxid;
		}

		/*
		 * If we're forcing timetravel we also need visibility information
		 * about subtransaction, so keep track of subtransaction's state, even
		 * if not catalog modifying.  Don't need to distribute a snapshot in
		 * that case.
		 */
		else if (needs_timetravel)
		{
			SnapBuildAddCommittedTxn(builder, subxid);
			if (NormalTransactionIdFollows(subxid, xmax))
				xmax = subxid;
		}
	}

	/* if top-level modified catalog, it'll need a snapshot */
	if (ReorderBufferXidHasCatalogChanges(builder->reorder, xid))
	{
		elog(DEBUG2, "found top level transaction %u, with catalog changes",
			 xid);
		needs_snapshot = true;
		needs_timetravel = true;
		SnapBuildAddCommittedTxn(builder, xid);
	}
	else if (sub_needs_timetravel)
	{
		/* track toplevel txn as well, subxact alone isn't meaningful */
		SnapBuildAddCommittedTxn(builder, xid);
	}
	else if (needs_timetravel)
	{
		elog(DEBUG2, "forced transaction %u to do timetravel", xid);

		SnapBuildAddCommittedTxn(builder, xid);
	}

	if (!needs_timetravel)
	{
		/* record that we cannot export a general snapshot anymore */
		builder->committed.includes_all_transactions = false;
	}

	Assert(!needs_snapshot || needs_timetravel);

	/*
	 * Adjust xmax of the snapshot builder, we only do that for committed,
	 * catalog modifying, transactions, everything else isn't interesting for
	 * us since we'll never look at the respective rows.
	 */
	if (needs_timetravel &&
		(!TransactionIdIsValid(builder->xmax) ||
		 TransactionIdFollowsOrEquals(xmax, builder->xmax)))
	{
		builder->xmax = xmax;
		TransactionIdAdvance(builder->xmax);
	}

	/* if there's any reason to build a historic snapshot, do so now */
	if (needs_snapshot)
	{
		/*
		 * If we haven't built a complete snapshot yet there's no need to hand
		 * it out, it wouldn't (and couldn't) be used anyway.
		 */
		if (builder->state < SNAPBUILD_FULL_SNAPSHOT)
			return;

		/*
		 * Decrease the snapshot builder's refcount of the old snapshot, note
		 * that it still will be used if it has been handed out to the
		 * reorderbuffer earlier.
		 */
		if (builder->snapshot)
			SnapBuildSnapDecRefcount(builder->snapshot);

		builder->snapshot = SnapBuildBuildSnapshot(builder);

		/* we might need to execute invalidations, add snapshot */
		if (!ReorderBufferXidHasBaseSnapshot(builder->reorder, xid))
		{
			SnapBuildSnapIncRefcount(builder->snapshot);
			ReorderBufferSetBaseSnapshot(builder->reorder, xid, lsn,
										 builder->snapshot);
		}

		/* refcount of the snapshot builder for the new snapshot */
		SnapBuildSnapIncRefcount(builder->snapshot);

		/* add a new catalog snapshot to all currently running transactions */
		SnapBuildDistributeNewCatalogSnapshot(builder, lsn);
	}
}