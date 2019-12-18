#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ regOffset; int /*<<< orphan*/  heapBlk; int /*<<< orphan*/  pagesPerRange; } ;
typedef  TYPE_1__ xl_brin_desummarize ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_10__ {int /*<<< orphan*/  rm_pagesPerRange; } ;
struct TYPE_9__ {int /*<<< orphan*/ * rm_tids; } ;
typedef  TYPE_2__ RevmapContents ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BrinTuple ;
typedef  TYPE_3__ BrinRevmap ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BRIN_IS_REGULAR_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/  BlockNumberIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ BrinTupleIsPlaceholder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HEAPBLK_TO_REVMAP_INDEX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdIsUsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetContents (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDeleteNoCompact (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_BRIN_ID ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationNeedsWAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SizeOfBrinDesummarize ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  XLOG_BRIN_DESUMMARIZE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brinLockRevmapPageForUpdate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* brinRevmapInitialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brinRevmapTerminate (TYPE_3__*) ; 
 int /*<<< orphan*/  brinSetHeapBlockItemptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  revmap_get_blkno (TYPE_3__*,int /*<<< orphan*/ ) ; 

bool
brinRevmapDesummarizeRange(Relation idxrel, BlockNumber heapBlk)
{
	BrinRevmap *revmap;
	BlockNumber pagesPerRange;
	RevmapContents *contents;
	ItemPointerData *iptr;
	ItemPointerData invalidIptr;
	BlockNumber revmapBlk;
	Buffer		revmapBuf;
	Buffer		regBuf;
	Page		revmapPg;
	Page		regPg;
	OffsetNumber revmapOffset;
	OffsetNumber regOffset;
	ItemId		lp;
	BrinTuple  *tup;

	revmap = brinRevmapInitialize(idxrel, &pagesPerRange, NULL);

	revmapBlk = revmap_get_blkno(revmap, heapBlk);
	if (!BlockNumberIsValid(revmapBlk))
	{
		/* revmap page doesn't exist: range not summarized, we're done */
		brinRevmapTerminate(revmap);
		return true;
	}

	/* Lock the revmap page, obtain the index tuple pointer from it */
	revmapBuf = brinLockRevmapPageForUpdate(revmap, heapBlk);
	revmapPg = BufferGetPage(revmapBuf);
	revmapOffset = HEAPBLK_TO_REVMAP_INDEX(revmap->rm_pagesPerRange, heapBlk);

	contents = (RevmapContents *) PageGetContents(revmapPg);
	iptr = contents->rm_tids;
	iptr += revmapOffset;

	if (!ItemPointerIsValid(iptr))
	{
		/* no index tuple: range not summarized, we're done */
		LockBuffer(revmapBuf, BUFFER_LOCK_UNLOCK);
		brinRevmapTerminate(revmap);
		return true;
	}

	regBuf = ReadBuffer(idxrel, ItemPointerGetBlockNumber(iptr));
	LockBuffer(regBuf, BUFFER_LOCK_EXCLUSIVE);
	regPg = BufferGetPage(regBuf);

	/* if this is no longer a regular page, tell caller to start over */
	if (!BRIN_IS_REGULAR_PAGE(regPg))
	{
		LockBuffer(revmapBuf, BUFFER_LOCK_UNLOCK);
		LockBuffer(regBuf, BUFFER_LOCK_UNLOCK);
		brinRevmapTerminate(revmap);
		return false;
	}

	regOffset = ItemPointerGetOffsetNumber(iptr);
	if (regOffset > PageGetMaxOffsetNumber(regPg))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("corrupted BRIN index: inconsistent range map")));

	lp = PageGetItemId(regPg, regOffset);
	if (!ItemIdIsUsed(lp))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("corrupted BRIN index: inconsistent range map")));
	tup = (BrinTuple *) PageGetItem(regPg, lp);
	/* XXX apply sanity checks?  Might as well delete a bogus tuple ... */

	/*
	 * We're only removing data, not reading it, so there's no need to
	 * TestForOldSnapshot here.
	 */

	/*
	 * Because of ShareUpdateExclusive lock, this function shouldn't run
	 * concurrently with summarization.  Placeholder tuples can only exist as
	 * leftovers from crashed summarization, so if we detect any, we complain
	 * but proceed.
	 */
	if (BrinTupleIsPlaceholder(tup))
		ereport(WARNING,
				(errmsg("leftover placeholder tuple detected in BRIN index \"%s\", deleting",
						RelationGetRelationName(idxrel))));

	START_CRIT_SECTION();

	ItemPointerSetInvalid(&invalidIptr);
	brinSetHeapBlockItemptr(revmapBuf, revmap->rm_pagesPerRange, heapBlk,
							invalidIptr);
	PageIndexTupleDeleteNoCompact(regPg, regOffset);
	/* XXX record free space in FSM? */

	MarkBufferDirty(regBuf);
	MarkBufferDirty(revmapBuf);

	if (RelationNeedsWAL(idxrel))
	{
		xl_brin_desummarize xlrec;
		XLogRecPtr	recptr;

		xlrec.pagesPerRange = revmap->rm_pagesPerRange;
		xlrec.heapBlk = heapBlk;
		xlrec.regOffset = regOffset;

		XLogBeginInsert();
		XLogRegisterData((char *) &xlrec, SizeOfBrinDesummarize);
		XLogRegisterBuffer(0, revmapBuf, 0);
		XLogRegisterBuffer(1, regBuf, REGBUF_STANDARD);
		recptr = XLogInsert(RM_BRIN_ID, XLOG_BRIN_DESUMMARIZE);
		PageSetLSN(revmapPg, recptr);
		PageSetLSN(regPg, recptr);
	}

	END_CRIT_SECTION();

	UnlockReleaseBuffer(regBuf);
	LockBuffer(revmapBuf, BUFFER_LOCK_UNLOCK);
	brinRevmapTerminate(revmap);

	return true;
}