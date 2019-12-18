#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* storeRes_func ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_21__ {int /*<<< orphan*/  pointer; } ;
struct TYPE_20__ {scalar_t__ tupstate; } ;
struct TYPE_19__ {int /*<<< orphan*/  heapPtr; int /*<<< orphan*/  distances; int /*<<< orphan*/  recheckDistances; int /*<<< orphan*/  recheck; int /*<<< orphan*/  isNull; int /*<<< orphan*/  value; scalar_t__ isLeaf; } ;
struct TYPE_18__ {scalar_t__ numberOfNonNullOrderBys; int /*<<< orphan*/  tempCxt; } ;
typedef  TYPE_2__ SpGistSearchItem ;
typedef  TYPE_1__* SpGistScanOpaque ;
typedef  TYPE_4__* SpGistInnerTuple ;
typedef  TYPE_5__* SpGistDeadTuple ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  scalar_t__ Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 scalar_t__ BufferGetBlockNumber (scalar_t__) ; 
 int /*<<< orphan*/  BufferGetPage (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstOffsetNumber ; 
 scalar_t__ InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SPGIST_LIVE ; 
 scalar_t__ SPGIST_METAPAGE_BLKNO ; 
 scalar_t__ SPGIST_REDIRECT ; 
 scalar_t__ SpGistBlockIsRoot (scalar_t__) ; 
 scalar_t__ SpGistPageIsLeaf (int /*<<< orphan*/ ) ; 
 scalar_t__ SpGistPageStoresNulls (int /*<<< orphan*/ ) ; 
 scalar_t__ SpGistRedirectOffsetNumber ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spgFreeSearchItem (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* spgGetNextQueueItem (TYPE_1__*) ; 
 int /*<<< orphan*/  spgInnerTest (TYPE_1__*,TYPE_2__*,TYPE_4__*,int) ; 
 scalar_t__ spgTestLeafTuple (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int,int,int*,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 

__attribute__((used)) static void
spgWalk(Relation index, SpGistScanOpaque so, bool scanWholeIndex,
		storeRes_func storeRes, Snapshot snapshot)
{
	Buffer		buffer = InvalidBuffer;
	bool		reportedSome = false;

	while (scanWholeIndex || !reportedSome)
	{
		SpGistSearchItem *item = spgGetNextQueueItem(so);

		if (item == NULL)
			break;				/* No more items in queue -> done */

redirect:
		/* Check for interrupts, just in case of infinite loop */
		CHECK_FOR_INTERRUPTS();

		if (item->isLeaf)
		{
			/* We store heap items in the queue only in case of ordered search */
			Assert(so->numberOfNonNullOrderBys > 0);
			storeRes(so, &item->heapPtr, item->value, item->isNull,
					 item->recheck, item->recheckDistances, item->distances);
			reportedSome = true;
		}
		else
		{
			BlockNumber blkno = ItemPointerGetBlockNumber(&item->heapPtr);
			OffsetNumber offset = ItemPointerGetOffsetNumber(&item->heapPtr);
			Page		page;
			bool		isnull;

			if (buffer == InvalidBuffer)
			{
				buffer = ReadBuffer(index, blkno);
				LockBuffer(buffer, BUFFER_LOCK_SHARE);
			}
			else if (blkno != BufferGetBlockNumber(buffer))
			{
				UnlockReleaseBuffer(buffer);
				buffer = ReadBuffer(index, blkno);
				LockBuffer(buffer, BUFFER_LOCK_SHARE);
			}

			/* else new pointer points to the same page, no work needed */

			page = BufferGetPage(buffer);
			TestForOldSnapshot(snapshot, index, page);

			isnull = SpGistPageStoresNulls(page) ? true : false;

			if (SpGistPageIsLeaf(page))
			{
				/* Page is a leaf - that is, all it's tuples are heap items */
				OffsetNumber max = PageGetMaxOffsetNumber(page);

				if (SpGistBlockIsRoot(blkno))
				{
					/* When root is a leaf, examine all its tuples */
					for (offset = FirstOffsetNumber; offset <= max; offset++)
						(void) spgTestLeafTuple(so, item, page, offset,
												isnull, true,
												&reportedSome, storeRes);
				}
				else
				{
					/* Normal case: just examine the chain we arrived at */
					while (offset != InvalidOffsetNumber)
					{
						Assert(offset >= FirstOffsetNumber && offset <= max);
						offset = spgTestLeafTuple(so, item, page, offset,
												  isnull, false,
												  &reportedSome, storeRes);
						if (offset == SpGistRedirectOffsetNumber)
							goto redirect;
					}
				}
			}
			else				/* page is inner */
			{
				SpGistInnerTuple innerTuple = (SpGistInnerTuple)
				PageGetItem(page, PageGetItemId(page, offset));

				if (innerTuple->tupstate != SPGIST_LIVE)
				{
					if (innerTuple->tupstate == SPGIST_REDIRECT)
					{
						/* transfer attention to redirect point */
						item->heapPtr = ((SpGistDeadTuple) innerTuple)->pointer;
						Assert(ItemPointerGetBlockNumber(&item->heapPtr) !=
							   SPGIST_METAPAGE_BLKNO);
						goto redirect;
					}
					elog(ERROR, "unexpected SPGiST tuple state: %d",
						 innerTuple->tupstate);
				}

				spgInnerTest(so, item, innerTuple, isnull);
			}
		}

		/* done with this scan item */
		spgFreeSearchItem(so, item);
		/* clear temp context before proceeding to the next one */
		MemoryContextReset(so->tempCxt);
	}

	if (buffer != InvalidBuffer)
		UnlockReleaseBuffer(buffer);
}