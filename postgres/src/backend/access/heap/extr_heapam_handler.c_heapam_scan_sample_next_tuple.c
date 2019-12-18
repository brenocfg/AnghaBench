#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_15__ {int /*<<< orphan*/  (* NextSampleTuple ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ TsmRoutine ;
typedef  TYPE_2__* TableScanDesc ;
struct TYPE_18__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; scalar_t__ t_data; } ;
struct TYPE_19__ {int /*<<< orphan*/  rs_cbuf; TYPE_4__ rs_ctup; int /*<<< orphan*/  rs_cblock; } ;
struct TYPE_17__ {TYPE_1__* tsmroutine; } ;
struct TYPE_16__ {int rs_flags; int /*<<< orphan*/  rs_rd; TYPE_13__* rs_snapshot; } ;
struct TYPE_14__ {int /*<<< orphan*/  takenDuringRecovery; } ;
typedef  TYPE_3__ SampleScanState ;
typedef  scalar_t__ Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ HeapTupleHeader ;
typedef  TYPE_4__* HeapTuple ;
typedef  TYPE_5__* HeapScanDesc ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CheckForSerializableConflictOut (int,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_13__*) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecStoreBufferHeapTuple (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetNumberIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetMaxOffsetNumber (scalar_t__) ; 
 scalar_t__ PageIsAllVisible (scalar_t__) ; 
 int SO_ALLOW_PAGEMODE ; 
 int SampleHeapTupleVisible (TYPE_2__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_count_heap_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
heapam_scan_sample_next_tuple(TableScanDesc scan, SampleScanState *scanstate,
							  TupleTableSlot *slot)
{
	HeapScanDesc hscan = (HeapScanDesc) scan;
	TsmRoutine *tsm = scanstate->tsmroutine;
	BlockNumber blockno = hscan->rs_cblock;
	bool		pagemode = (scan->rs_flags & SO_ALLOW_PAGEMODE) != 0;

	Page		page;
	bool		all_visible;
	OffsetNumber maxoffset;

	/*
	 * When not using pagemode, we must lock the buffer during tuple
	 * visibility checks.
	 */
	if (!pagemode)
		LockBuffer(hscan->rs_cbuf, BUFFER_LOCK_SHARE);

	page = (Page) BufferGetPage(hscan->rs_cbuf);
	all_visible = PageIsAllVisible(page) &&
		!scan->rs_snapshot->takenDuringRecovery;
	maxoffset = PageGetMaxOffsetNumber(page);

	for (;;)
	{
		OffsetNumber tupoffset;

		CHECK_FOR_INTERRUPTS();

		/* Ask the tablesample method which tuples to check on this page. */
		tupoffset = tsm->NextSampleTuple(scanstate,
										 blockno,
										 maxoffset);

		if (OffsetNumberIsValid(tupoffset))
		{
			ItemId		itemid;
			bool		visible;
			HeapTuple	tuple = &(hscan->rs_ctup);

			/* Skip invalid tuple pointers. */
			itemid = PageGetItemId(page, tupoffset);
			if (!ItemIdIsNormal(itemid))
				continue;

			tuple->t_data = (HeapTupleHeader) PageGetItem(page, itemid);
			tuple->t_len = ItemIdGetLength(itemid);
			ItemPointerSet(&(tuple->t_self), blockno, tupoffset);


			if (all_visible)
				visible = true;
			else
				visible = SampleHeapTupleVisible(scan, hscan->rs_cbuf,
												 tuple, tupoffset);

			/* in pagemode, heapgetpage did this for us */
			if (!pagemode)
				CheckForSerializableConflictOut(visible, scan->rs_rd, tuple,
												hscan->rs_cbuf, scan->rs_snapshot);

			/* Try next tuple from same page. */
			if (!visible)
				continue;

			/* Found visible tuple, return it. */
			if (!pagemode)
				LockBuffer(hscan->rs_cbuf, BUFFER_LOCK_UNLOCK);

			ExecStoreBufferHeapTuple(tuple, slot, hscan->rs_cbuf);

			/* Count successfully-fetched tuples as heap fetches */
			pgstat_count_heap_getnext(scan->rs_rd);

			return true;
		}
		else
		{
			/*
			 * If we get here, it means we've exhausted the items on this page
			 * and it's time to move to the next.
			 */
			if (!pagemode)
				LockBuffer(hscan->rs_cbuf, BUFFER_LOCK_UNLOCK);

			ExecClearTuple(slot);
			return false;
		}
	}

	Assert(0);
}