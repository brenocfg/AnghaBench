#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_7__ {int xcnt; int /*<<< orphan*/  xip; } ;
struct TYPE_9__ {scalar_t__ state; TYPE_1__ committed; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; int /*<<< orphan*/  context; } ;
struct TYPE_8__ {int xcnt; int suboverflowed; int takenDuringRecovery; int copied; scalar_t__ regd_count; scalar_t__ active_count; int /*<<< orphan*/  curcid; int /*<<< orphan*/ * subxip; scalar_t__ subxcnt; int /*<<< orphan*/ * xip; int /*<<< orphan*/  xmax; int /*<<< orphan*/  xmin; int /*<<< orphan*/  snapshot_type; } ;
typedef  int /*<<< orphan*/  SnapshotData ;
typedef  TYPE_2__* Snapshot ;
typedef  TYPE_3__ SnapBuild ;
typedef  int Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FirstCommandId ; 
 TYPE_2__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SNAPBUILD_FULL_SNAPSHOT ; 
 int /*<<< orphan*/  SNAPSHOT_HISTORIC_MVCC ; 
 int TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xidComparator ; 

__attribute__((used)) static Snapshot
SnapBuildBuildSnapshot(SnapBuild *builder)
{
	Snapshot	snapshot;
	Size		ssize;

	Assert(builder->state >= SNAPBUILD_FULL_SNAPSHOT);

	ssize = sizeof(SnapshotData)
		+ sizeof(TransactionId) * builder->committed.xcnt
		+ sizeof(TransactionId) * 1 /* toplevel xid */ ;

	snapshot = MemoryContextAllocZero(builder->context, ssize);

	snapshot->snapshot_type = SNAPSHOT_HISTORIC_MVCC;

	/*
	 * We misuse the original meaning of SnapshotData's xip and subxip fields
	 * to make the more fitting for our needs.
	 *
	 * In the 'xip' array we store transactions that have to be treated as
	 * committed. Since we will only ever look at tuples from transactions
	 * that have modified the catalog it's more efficient to store those few
	 * that exist between xmin and xmax (frequently there are none).
	 *
	 * Snapshots that are used in transactions that have modified the catalog
	 * also use the 'subxip' array to store their toplevel xid and all the
	 * subtransaction xids so we can recognize when we need to treat rows as
	 * visible that are not in xip but still need to be visible. Subxip only
	 * gets filled when the transaction is copied into the context of a
	 * catalog modifying transaction since we otherwise share a snapshot
	 * between transactions. As long as a txn hasn't modified the catalog it
	 * doesn't need to treat any uncommitted rows as visible, so there is no
	 * need for those xids.
	 *
	 * Both arrays are qsort'ed so that we can use bsearch() on them.
	 */
	Assert(TransactionIdIsNormal(builder->xmin));
	Assert(TransactionIdIsNormal(builder->xmax));

	snapshot->xmin = builder->xmin;
	snapshot->xmax = builder->xmax;

	/* store all transactions to be treated as committed by this snapshot */
	snapshot->xip =
		(TransactionId *) ((char *) snapshot + sizeof(SnapshotData));
	snapshot->xcnt = builder->committed.xcnt;
	memcpy(snapshot->xip,
		   builder->committed.xip,
		   builder->committed.xcnt * sizeof(TransactionId));

	/* sort so we can bsearch() */
	qsort(snapshot->xip, snapshot->xcnt, sizeof(TransactionId), xidComparator);

	/*
	 * Initially, subxip is empty, i.e. it's a snapshot to be used by
	 * transactions that don't modify the catalog. Will be filled by
	 * ReorderBufferCopySnap() if necessary.
	 */
	snapshot->subxcnt = 0;
	snapshot->subxip = NULL;

	snapshot->suboverflowed = false;
	snapshot->takenDuringRecovery = false;
	snapshot->copied = false;
	snapshot->curcid = FirstCommandId;
	snapshot->active_count = 0;
	snapshot->regd_count = 0;

	return snapshot;
}