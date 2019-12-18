#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TransactionId ;
typedef  TYPE_1__* TableScanDesc ;
struct TYPE_13__ {TYPE_2__* t_data; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_len; } ;
struct TYPE_12__ {int t_infomask; int /*<<< orphan*/  t_ctid; } ;
struct TYPE_11__ {int /*<<< orphan*/  rs_snapshot; int /*<<< orphan*/  rs_rd; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/ * ItemPointer ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_2__* HeapTupleHeader ;
typedef  TYPE_3__ HeapTupleData ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckForSerializableConflictOut (int,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FirstOffsetNumber ; 
 int HEAP_XMAX_INVALID ; 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (TYPE_2__*) ; 
 scalar_t__ HeapTupleHeaderIndicatesMovedPartitions (TYPE_2__*) ; 
 scalar_t__ HeapTupleHeaderIsOnlyLocked (TYPE_2__*) ; 
 int HeapTupleSatisfiesVisibility (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidTransactionId ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdIsNormal (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 

void
heap_get_latest_tid(TableScanDesc sscan,
					ItemPointer tid)
{
	Relation	relation = sscan->rs_rd;
	Snapshot	snapshot = sscan->rs_snapshot;
	ItemPointerData ctid;
	TransactionId priorXmax;

	/*
	 * table_get_latest_tid verified that the passed in tid is valid.  Assume
	 * that t_ctid links are valid however - there shouldn't be invalid ones
	 * in the table.
	 */
	Assert(ItemPointerIsValid(tid));

	/*
	 * Loop to chase down t_ctid links.  At top of loop, ctid is the tuple we
	 * need to examine, and *tid is the TID we will return if ctid turns out
	 * to be bogus.
	 *
	 * Note that we will loop until we reach the end of the t_ctid chain.
	 * Depending on the snapshot passed, there might be at most one visible
	 * version of the row, but we don't try to optimize for that.
	 */
	ctid = *tid;
	priorXmax = InvalidTransactionId;	/* cannot check first XMIN */
	for (;;)
	{
		Buffer		buffer;
		Page		page;
		OffsetNumber offnum;
		ItemId		lp;
		HeapTupleData tp;
		bool		valid;

		/*
		 * Read, pin, and lock the page.
		 */
		buffer = ReadBuffer(relation, ItemPointerGetBlockNumber(&ctid));
		LockBuffer(buffer, BUFFER_LOCK_SHARE);
		page = BufferGetPage(buffer);
		TestForOldSnapshot(snapshot, relation, page);

		/*
		 * Check for bogus item number.  This is not treated as an error
		 * condition because it can happen while following a t_ctid link. We
		 * just assume that the prior tid is OK and return it unchanged.
		 */
		offnum = ItemPointerGetOffsetNumber(&ctid);
		if (offnum < FirstOffsetNumber || offnum > PageGetMaxOffsetNumber(page))
		{
			UnlockReleaseBuffer(buffer);
			break;
		}
		lp = PageGetItemId(page, offnum);
		if (!ItemIdIsNormal(lp))
		{
			UnlockReleaseBuffer(buffer);
			break;
		}

		/* OK to access the tuple */
		tp.t_self = ctid;
		tp.t_data = (HeapTupleHeader) PageGetItem(page, lp);
		tp.t_len = ItemIdGetLength(lp);
		tp.t_tableOid = RelationGetRelid(relation);

		/*
		 * After following a t_ctid link, we might arrive at an unrelated
		 * tuple.  Check for XMIN match.
		 */
		if (TransactionIdIsValid(priorXmax) &&
			!TransactionIdEquals(priorXmax, HeapTupleHeaderGetXmin(tp.t_data)))
		{
			UnlockReleaseBuffer(buffer);
			break;
		}

		/*
		 * Check tuple visibility; if visible, set it as the new result
		 * candidate.
		 */
		valid = HeapTupleSatisfiesVisibility(&tp, snapshot, buffer);
		CheckForSerializableConflictOut(valid, relation, &tp, buffer, snapshot);
		if (valid)
			*tid = ctid;

		/*
		 * If there's a valid t_ctid link, follow it, else we're done.
		 */
		if ((tp.t_data->t_infomask & HEAP_XMAX_INVALID) ||
			HeapTupleHeaderIsOnlyLocked(tp.t_data) ||
			HeapTupleHeaderIndicatesMovedPartitions(tp.t_data) ||
			ItemPointerEquals(&tp.t_self, &tp.t_data->t_ctid))
		{
			UnlockReleaseBuffer(buffer);
			break;
		}

		ctid = tp.t_data->t_ctid;
		priorXmax = HeapTupleHeaderGetUpdateXid(tp.t_data);
		UnlockReleaseBuffer(buffer);
	}							/* end of loop */
}