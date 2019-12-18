#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  TYPE_2__* TableScanDesc ;
struct TYPE_11__ {scalar_t__ t_data; int /*<<< orphan*/  t_len; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; } ;
struct TYPE_9__ {TYPE_3__ tupdata; } ;
struct TYPE_13__ {TYPE_1__ base; } ;
struct TYPE_12__ {scalar_t__ rs_cindex; int /*<<< orphan*/  rs_cbuf; int /*<<< orphan*/  rs_cblock; } ;
struct TYPE_10__ {int /*<<< orphan*/  rs_rd; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ HeapTupleHeader ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* HeapScanDesc ;
typedef  TYPE_5__ BufferHeapTupleTableSlot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecStoreBufferHeapTuple (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  HEAPTUPLE_DEAD 132 
#define  HEAPTUPLE_DELETE_IN_PROGRESS 131 
#define  HEAPTUPLE_INSERT_IN_PROGRESS 130 
#define  HEAPTUPLE_LIVE 129 
#define  HEAPTUPLE_RECENTLY_DEAD 128 
 int /*<<< orphan*/  HeapTupleHeaderGetUpdateXid (scalar_t__) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetXmin (scalar_t__) ; 
 int HeapTupleSatisfiesVacuum (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsDead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTS_IS_BUFFERTUPLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactionIdIsCurrentTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
heapam_scan_analyze_next_tuple(TableScanDesc scan, TransactionId OldestXmin,
							   double *liverows, double *deadrows,
							   TupleTableSlot *slot)
{
	HeapScanDesc hscan = (HeapScanDesc) scan;
	Page		targpage;
	OffsetNumber maxoffset;
	BufferHeapTupleTableSlot *hslot;

	Assert(TTS_IS_BUFFERTUPLE(slot));

	hslot = (BufferHeapTupleTableSlot *) slot;
	targpage = BufferGetPage(hscan->rs_cbuf);
	maxoffset = PageGetMaxOffsetNumber(targpage);

	/* Inner loop over all tuples on the selected page */
	for (; hscan->rs_cindex <= maxoffset; hscan->rs_cindex++)
	{
		ItemId		itemid;
		HeapTuple	targtuple = &hslot->base.tupdata;
		bool		sample_it = false;

		itemid = PageGetItemId(targpage, hscan->rs_cindex);

		/*
		 * We ignore unused and redirect line pointers.  DEAD line pointers
		 * should be counted as dead, because we need vacuum to run to get rid
		 * of them.  Note that this rule agrees with the way that
		 * heap_page_prune() counts things.
		 */
		if (!ItemIdIsNormal(itemid))
		{
			if (ItemIdIsDead(itemid))
				*deadrows += 1;
			continue;
		}

		ItemPointerSet(&targtuple->t_self, hscan->rs_cblock, hscan->rs_cindex);

		targtuple->t_tableOid = RelationGetRelid(scan->rs_rd);
		targtuple->t_data = (HeapTupleHeader) PageGetItem(targpage, itemid);
		targtuple->t_len = ItemIdGetLength(itemid);

		switch (HeapTupleSatisfiesVacuum(targtuple, OldestXmin,
										 hscan->rs_cbuf))
		{
			case HEAPTUPLE_LIVE:
				sample_it = true;
				*liverows += 1;
				break;

			case HEAPTUPLE_DEAD:
			case HEAPTUPLE_RECENTLY_DEAD:
				/* Count dead and recently-dead rows */
				*deadrows += 1;
				break;

			case HEAPTUPLE_INSERT_IN_PROGRESS:

				/*
				 * Insert-in-progress rows are not counted.  We assume that
				 * when the inserting transaction commits or aborts, it will
				 * send a stats message to increment the proper count.  This
				 * works right only if that transaction ends after we finish
				 * analyzing the table; if things happen in the other order,
				 * its stats update will be overwritten by ours.  However, the
				 * error will be large only if the other transaction runs long
				 * enough to insert many tuples, so assuming it will finish
				 * after us is the safer option.
				 *
				 * A special case is that the inserting transaction might be
				 * our own.  In this case we should count and sample the row,
				 * to accommodate users who load a table and analyze it in one
				 * transaction.  (pgstat_report_analyze has to adjust the
				 * numbers we send to the stats collector to make this come
				 * out right.)
				 */
				if (TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetXmin(targtuple->t_data)))
				{
					sample_it = true;
					*liverows += 1;
				}
				break;

			case HEAPTUPLE_DELETE_IN_PROGRESS:

				/*
				 * We count and sample delete-in-progress rows the same as
				 * live ones, so that the stats counters come out right if the
				 * deleting transaction commits after us, per the same
				 * reasoning given above.
				 *
				 * If the delete was done by our own transaction, however, we
				 * must count the row as dead to make pgstat_report_analyze's
				 * stats adjustments come out right.  (Note: this works out
				 * properly when the row was both inserted and deleted in our
				 * xact.)
				 *
				 * The net effect of these choices is that we act as though an
				 * IN_PROGRESS transaction hasn't happened yet, except if it
				 * is our own transaction, which we assume has happened.
				 *
				 * This approach ensures that we behave sanely if we see both
				 * the pre-image and post-image rows for a row being updated
				 * by a concurrent transaction: we will sample the pre-image
				 * but not the post-image.  We also get sane results if the
				 * concurrent transaction never commits.
				 */
				if (TransactionIdIsCurrentTransactionId(HeapTupleHeaderGetUpdateXid(targtuple->t_data)))
					*deadrows += 1;
				else
				{
					sample_it = true;
					*liverows += 1;
				}
				break;

			default:
				elog(ERROR, "unexpected HeapTupleSatisfiesVacuum result");
				break;
		}

		if (sample_it)
		{
			ExecStoreBufferHeapTuple(targtuple, slot, hscan->rs_cbuf);
			hscan->rs_cindex++;

			/* note that we leave the buffer locked here! */
			return true;
		}
	}

	/* Now release the lock and pin on the page */
	UnlockReleaseBuffer(hscan->rs_cbuf);
	hscan->rs_cbuf = InvalidBuffer;

	/* also prevent old slot contents from having pin on page */
	ExecClearTuple(slot);

	return false;
}