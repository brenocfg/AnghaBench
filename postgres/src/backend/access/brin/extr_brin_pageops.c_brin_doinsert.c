#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ offnum; void* pagesPerRange; void* heapBlk; } ;
typedef  TYPE_1__ xl_brin_insert ;
typedef  int uint8 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  Item ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BrinTuple ;
typedef  int /*<<< orphan*/  BrinRevmap ;
typedef  void* BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BRIN_PAGETYPE_REGULAR ; 
 int /*<<< orphan*/  BRIN_elog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BrinMaxItemSize ; 
 void* BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FreeSpaceMapVacuumRange (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REGBUF_STANDARD ; 
 int REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_BRIN_ID ; 
 int /*<<< orphan*/  RecordPageWithFreeSpace (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBrinInsert ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int XLOG_BRIN_INIT_PAGE ; 
 int XLOG_BRIN_INSERT ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_page_get_freespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brinLockRevmapPageForUpdate (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  brinRevmapExtend (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  brinSetHeapBlockItemptr (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_getinsertbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brin_page_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OffsetNumber
brin_doinsert(Relation idxrel, BlockNumber pagesPerRange,
			  BrinRevmap *revmap, Buffer *buffer, BlockNumber heapBlk,
			  BrinTuple *tup, Size itemsz)
{
	Page		page;
	BlockNumber blk;
	OffsetNumber off;
	Size		freespace = 0;
	Buffer		revmapbuf;
	ItemPointerData tid;
	bool		extended;

	Assert(itemsz == MAXALIGN(itemsz));

	/* If the item is oversized, don't even bother. */
	if (itemsz > BrinMaxItemSize)
	{
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("index row size %zu exceeds maximum %zu for index \"%s\"",
						itemsz, BrinMaxItemSize, RelationGetRelationName(idxrel))));
		return InvalidOffsetNumber; /* keep compiler quiet */
	}

	/* Make sure the revmap is long enough to contain the entry we need */
	brinRevmapExtend(revmap, heapBlk);

	/*
	 * Acquire lock on buffer supplied by caller, if any.  If it doesn't have
	 * enough space, unpin it to obtain a new one below.
	 */
	if (BufferIsValid(*buffer))
	{
		/*
		 * It's possible that another backend (or ourselves!) extended the
		 * revmap over the page we held a pin on, so we cannot assume that
		 * it's still a regular page.
		 */
		LockBuffer(*buffer, BUFFER_LOCK_EXCLUSIVE);
		if (br_page_get_freespace(BufferGetPage(*buffer)) < itemsz)
		{
			UnlockReleaseBuffer(*buffer);
			*buffer = InvalidBuffer;
		}
	}

	/*
	 * If we still don't have a usable buffer, have brin_getinsertbuffer
	 * obtain one for us.
	 */
	if (!BufferIsValid(*buffer))
	{
		do
			*buffer = brin_getinsertbuffer(idxrel, InvalidBuffer, itemsz, &extended);
		while (!BufferIsValid(*buffer));
	}
	else
		extended = false;

	/* Now obtain lock on revmap buffer */
	revmapbuf = brinLockRevmapPageForUpdate(revmap, heapBlk);

	page = BufferGetPage(*buffer);
	blk = BufferGetBlockNumber(*buffer);

	/* Execute the actual insertion */
	START_CRIT_SECTION();
	if (extended)
		brin_page_init(page, BRIN_PAGETYPE_REGULAR);
	off = PageAddItem(page, (Item) tup, itemsz, InvalidOffsetNumber,
					  false, false);
	if (off == InvalidOffsetNumber)
		elog(ERROR, "failed to add BRIN tuple to new page");
	MarkBufferDirty(*buffer);

	/* needed to update FSM below */
	if (extended)
		freespace = br_page_get_freespace(page);

	ItemPointerSet(&tid, blk, off);
	brinSetHeapBlockItemptr(revmapbuf, pagesPerRange, heapBlk, tid);
	MarkBufferDirty(revmapbuf);

	/* XLOG stuff */
	if (RelationNeedsWAL(idxrel))
	{
		xl_brin_insert xlrec;
		XLogRecPtr	recptr;
		uint8		info;

		info = XLOG_BRIN_INSERT | (extended ? XLOG_BRIN_INIT_PAGE : 0);
		xlrec.heapBlk = heapBlk;
		xlrec.pagesPerRange = pagesPerRange;
		xlrec.offnum = off;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfBrinInsert);

		XLogRegisterBuffer(0, *buffer, REGBUF_STANDARD | (extended ? REGBUF_WILL_INIT : 0));
		XLogRegisterBufData(0, (char *) tup, itemsz);

		XLogRegisterBuffer(1, revmapbuf, 0);

		recptr = XLogInsert(RM_BRIN_ID, info);

		PageSetLSN(page, recptr);
		PageSetLSN(BufferGetPage(revmapbuf), recptr);
	}

	END_CRIT_SECTION();

	/* Tuple is firmly on buffer; we can release our locks */
	LockBuffer(*buffer, BUFFER_LOCK_UNLOCK);
	LockBuffer(revmapbuf, BUFFER_LOCK_UNLOCK);

	BRIN_elog((DEBUG2, "inserted tuple (%u,%u) for range starting at %u",
			   blk, off, heapBlk));

	if (extended)
	{
		RecordPageWithFreeSpace(idxrel, blk, freespace);
		FreeSpaceMapVacuumRange(idxrel, blk, blk + 1);
	}

	return off;
}