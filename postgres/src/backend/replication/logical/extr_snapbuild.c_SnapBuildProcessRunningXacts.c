#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ oldestRunningXid; } ;
typedef  TYPE_1__ xl_running_xacts ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  scalar_t__ TransactionId ;
struct TYPE_16__ {scalar_t__ restart_decoding_lsn; } ;
struct TYPE_15__ {scalar_t__ state; scalar_t__ xmin; scalar_t__ last_serialized_snapshot; TYPE_10__* reorder; int /*<<< orphan*/  xmax; } ;
struct TYPE_13__ {scalar_t__ current_restart_decoding_lsn; } ;
typedef  TYPE_2__ SnapBuild ;
typedef  TYPE_3__ ReorderBufferTXN ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG3 ; 
 scalar_t__ InvalidTransactionId ; 
 scalar_t__ InvalidXLogRecPtr ; 
 int /*<<< orphan*/  LogicalIncreaseRestartDecodingForSlot (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LogicalIncreaseXminForSlot (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* ReorderBufferGetOldestTXN (TYPE_10__*) ; 
 scalar_t__ ReorderBufferGetOldestXmin (TYPE_10__*) ; 
 scalar_t__ SNAPBUILD_CONSISTENT ; 
 int /*<<< orphan*/  SnapBuildFindSnapshot (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SnapBuildPurgeCommittedTxn (TYPE_2__*) ; 
 int /*<<< orphan*/  SnapBuildSerialize (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void
SnapBuildProcessRunningXacts(SnapBuild *builder, XLogRecPtr lsn, xl_running_xacts *running)
{
	ReorderBufferTXN *txn;
	TransactionId xmin;

	/*
	 * If we're not consistent yet, inspect the record to see whether it
	 * allows to get closer to being consistent. If we are consistent, dump
	 * our snapshot so others or we, after a restart, can use it.
	 */
	if (builder->state < SNAPBUILD_CONSISTENT)
	{
		/* returns false if there's no point in performing cleanup just yet */
		if (!SnapBuildFindSnapshot(builder, lsn, running))
			return;
	}
	else
		SnapBuildSerialize(builder, lsn);

	/*
	 * Update range of interesting xids based on the running xacts
	 * information. We don't increase ->xmax using it, because once we are in
	 * a consistent state we can do that ourselves and much more efficiently
	 * so, because we only need to do it for catalog transactions since we
	 * only ever look at those.
	 *
	 * NB: We only increase xmax when a catalog modifying transaction commits
	 * (see SnapBuildCommitTxn).  Because of this, xmax can be lower than
	 * xmin, which looks odd but is correct and actually more efficient, since
	 * we hit fast paths in heapam_visibility.c.
	 */
	builder->xmin = running->oldestRunningXid;

	/* Remove transactions we don't need to keep track off anymore */
	SnapBuildPurgeCommittedTxn(builder);

	/*
	 * Advance the xmin limit for the current replication slot, to allow
	 * vacuum to clean up the tuples this slot has been protecting.
	 *
	 * The reorderbuffer might have an xmin among the currently running
	 * snapshots; use it if so.  If not, we need only consider the snapshots
	 * we'll produce later, which can't be less than the oldest running xid in
	 * the record we're reading now.
	 */
	xmin = ReorderBufferGetOldestXmin(builder->reorder);
	if (xmin == InvalidTransactionId)
		xmin = running->oldestRunningXid;
	elog(DEBUG3, "xmin: %u, xmax: %u, oldest running: %u, oldest xmin: %u",
		 builder->xmin, builder->xmax, running->oldestRunningXid, xmin);
	LogicalIncreaseXminForSlot(lsn, xmin);

	/*
	 * Also tell the slot where we can restart decoding from. We don't want to
	 * do that after every commit because changing that implies an fsync of
	 * the logical slot's state file, so we only do it every time we see a
	 * running xacts record.
	 *
	 * Do so by looking for the oldest in progress transaction (determined by
	 * the first LSN of any of its relevant records). Every transaction
	 * remembers the last location we stored the snapshot to disk before its
	 * beginning. That point is where we can restart from.
	 */

	/*
	 * Can't know about a serialized snapshot's location if we're not
	 * consistent.
	 */
	if (builder->state < SNAPBUILD_CONSISTENT)
		return;

	txn = ReorderBufferGetOldestTXN(builder->reorder);

	/*
	 * oldest ongoing txn might have started when we didn't yet serialize
	 * anything because we hadn't reached a consistent state yet.
	 */
	if (txn != NULL && txn->restart_decoding_lsn != InvalidXLogRecPtr)
		LogicalIncreaseRestartDecodingForSlot(lsn, txn->restart_decoding_lsn);

	/*
	 * No in-progress transaction, can reuse the last serialized snapshot if
	 * we have one.
	 */
	else if (txn == NULL &&
			 builder->reorder->current_restart_decoding_lsn != InvalidXLogRecPtr &&
			 builder->last_serialized_snapshot != InvalidXLogRecPtr)
		LogicalIncreaseRestartDecodingForSlot(lsn,
											  builder->last_serialized_snapshot);
}