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
struct TYPE_9__ {scalar_t__ rm_pagesPerRange; void* rm_currBuf; int /*<<< orphan*/  rm_irel; } ;
struct TYPE_8__ {scalar_t__ bt_blkno; } ;
struct TYPE_7__ {int /*<<< orphan*/ * rm_tids; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Size ;
typedef  TYPE_1__ RevmapContents ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  void* Buffer ;
typedef  TYPE_2__ BrinTuple ;
typedef  TYPE_3__ BrinRevmap ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BRIN_IS_REGULAR_PAGE (int /*<<< orphan*/ ) ; 
 int BUFFER_LOCK_SHARE ; 
 int BUFFER_LOCK_UNLOCK ; 
 scalar_t__ BufferGetBlockNumber (void*) ; 
 int /*<<< orphan*/  BufferGetPage (void*) ; 
 scalar_t__ BufferIsValid (void*) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HEAPBLK_TO_REVMAP_INDEX (scalar_t__,scalar_t__) ; 
 scalar_t__ InvalidBlockNumber ; 
 void* InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsUsed (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerEquals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (void*,int) ; 
 scalar_t__ PageGetContents (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 void* ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (void*) ; 
 int /*<<< orphan*/  TestForOldSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 
 scalar_t__ revmap_get_blkno (TYPE_3__*,scalar_t__) ; 

BrinTuple *
brinGetTupleForHeapBlock(BrinRevmap *revmap, BlockNumber heapBlk,
						 Buffer *buf, OffsetNumber *off, Size *size, int mode,
						 Snapshot snapshot)
{
	Relation	idxRel = revmap->rm_irel;
	BlockNumber mapBlk;
	RevmapContents *contents;
	ItemPointerData *iptr;
	BlockNumber blk;
	Page		page;
	ItemId		lp;
	BrinTuple  *tup;
	ItemPointerData previptr;

	/* normalize the heap block number to be the first page in the range */
	heapBlk = (heapBlk / revmap->rm_pagesPerRange) * revmap->rm_pagesPerRange;

	/*
	 * Compute the revmap page number we need.  If Invalid is returned (i.e.,
	 * the revmap page hasn't been created yet), the requested page range is
	 * not summarized.
	 */
	mapBlk = revmap_get_blkno(revmap, heapBlk);
	if (mapBlk == InvalidBlockNumber)
	{
		*off = InvalidOffsetNumber;
		return NULL;
	}

	ItemPointerSetInvalid(&previptr);
	for (;;)
	{
		CHECK_FOR_INTERRUPTS();

		if (revmap->rm_currBuf == InvalidBuffer ||
			BufferGetBlockNumber(revmap->rm_currBuf) != mapBlk)
		{
			if (revmap->rm_currBuf != InvalidBuffer)
				ReleaseBuffer(revmap->rm_currBuf);

			Assert(mapBlk != InvalidBlockNumber);
			revmap->rm_currBuf = ReadBuffer(revmap->rm_irel, mapBlk);
		}

		LockBuffer(revmap->rm_currBuf, BUFFER_LOCK_SHARE);

		contents = (RevmapContents *)
			PageGetContents(BufferGetPage(revmap->rm_currBuf));
		iptr = contents->rm_tids;
		iptr += HEAPBLK_TO_REVMAP_INDEX(revmap->rm_pagesPerRange, heapBlk);

		if (!ItemPointerIsValid(iptr))
		{
			LockBuffer(revmap->rm_currBuf, BUFFER_LOCK_UNLOCK);
			return NULL;
		}

		/*
		 * Check the TID we got in a previous iteration, if any, and save the
		 * current TID we got from the revmap; if we loop, we can sanity-check
		 * that the next one we get is different.  Otherwise we might be stuck
		 * looping forever if the revmap is somehow badly broken.
		 */
		if (ItemPointerIsValid(&previptr) && ItemPointerEquals(&previptr, iptr))
			ereport(ERROR,
					(errcode(ERRCODE_INDEX_CORRUPTED),
					 errmsg_internal("corrupted BRIN index: inconsistent range map")));
		previptr = *iptr;

		blk = ItemPointerGetBlockNumber(iptr);
		*off = ItemPointerGetOffsetNumber(iptr);

		LockBuffer(revmap->rm_currBuf, BUFFER_LOCK_UNLOCK);

		/* Ok, got a pointer to where the BrinTuple should be. Fetch it. */
		if (!BufferIsValid(*buf) || BufferGetBlockNumber(*buf) != blk)
		{
			if (BufferIsValid(*buf))
				ReleaseBuffer(*buf);
			*buf = ReadBuffer(idxRel, blk);
		}
		LockBuffer(*buf, mode);
		page = BufferGetPage(*buf);
		TestForOldSnapshot(snapshot, idxRel, page);

		/* If we land on a revmap page, start over */
		if (BRIN_IS_REGULAR_PAGE(page))
		{
			if (*off > PageGetMaxOffsetNumber(page))
				ereport(ERROR,
						(errcode(ERRCODE_INDEX_CORRUPTED),
						 errmsg_internal("corrupted BRIN index: inconsistent range map")));
			lp = PageGetItemId(page, *off);
			if (ItemIdIsUsed(lp))
			{
				tup = (BrinTuple *) PageGetItem(page, lp);

				if (tup->bt_blkno == heapBlk)
				{
					if (size)
						*size = ItemIdGetLength(lp);
					/* found it! */
					return tup;
				}
			}
		}

		/*
		 * No luck. Assume that the revmap was updated concurrently.
		 */
		LockBuffer(*buf, BUFFER_LOCK_UNLOCK);
	}
	/* not reached, but keep compiler quiet */
	return NULL;
}