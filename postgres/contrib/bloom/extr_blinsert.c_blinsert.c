#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t nEnd; size_t nStart; scalar_t__* notFullPage; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  size_t OffsetNumber ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  IndexUniqueCheck ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  int /*<<< orphan*/  GenericXLogState ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BloomTuple ;
typedef  int /*<<< orphan*/  BloomState ;
typedef  TYPE_1__ BloomMetaPageData ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLOOM_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  BUFFER_LOCK_SHARE ; 
 int /*<<< orphan*/  BUFFER_LOCK_UNLOCK ; 
 int /*<<< orphan*/ * BloomFormTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  BloomInitPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BloomNewBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ BloomPageAddItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* BloomPageGetMeta (int /*<<< orphan*/ ) ; 
 scalar_t__ BloomPageIsDeleted (int /*<<< orphan*/ ) ; 
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GENERIC_XLOG_FULL_IMAGE ; 
 int /*<<< orphan*/  GenericXLogAbort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenericXLogFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenericXLogRegisterBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GenericXLogStart (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PageIsNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  initBloomState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
blinsert(Relation index, Datum *values, bool *isnull,
		 ItemPointer ht_ctid, Relation heapRel,
		 IndexUniqueCheck checkUnique,
		 IndexInfo *indexInfo)
{
	BloomState	blstate;
	BloomTuple *itup;
	MemoryContext oldCtx;
	MemoryContext insertCtx;
	BloomMetaPageData *metaData;
	Buffer		buffer,
				metaBuffer;
	Page		page,
				metaPage;
	BlockNumber blkno = InvalidBlockNumber;
	OffsetNumber nStart;
	GenericXLogState *state;

	insertCtx = AllocSetContextCreate(CurrentMemoryContext,
									  "Bloom insert temporary context",
									  ALLOCSET_DEFAULT_SIZES);

	oldCtx = MemoryContextSwitchTo(insertCtx);

	initBloomState(&blstate, index);
	itup = BloomFormTuple(&blstate, ht_ctid, values, isnull);

	/*
	 * At first, try to insert new tuple to the first page in notFullPage
	 * array.  If successful, we don't need to modify the meta page.
	 */
	metaBuffer = ReadBuffer(index, BLOOM_METAPAGE_BLKNO);
	LockBuffer(metaBuffer, BUFFER_LOCK_SHARE);
	metaData = BloomPageGetMeta(BufferGetPage(metaBuffer));

	if (metaData->nEnd > metaData->nStart)
	{
		Page		page;

		blkno = metaData->notFullPage[metaData->nStart];
		Assert(blkno != InvalidBlockNumber);

		/* Don't hold metabuffer lock while doing insert */
		LockBuffer(metaBuffer, BUFFER_LOCK_UNLOCK);

		buffer = ReadBuffer(index, blkno);
		LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);

		state = GenericXLogStart(index);
		page = GenericXLogRegisterBuffer(state, buffer, 0);

		/*
		 * We might have found a page that was recently deleted by VACUUM.  If
		 * so, we can reuse it, but we must reinitialize it.
		 */
		if (PageIsNew(page) || BloomPageIsDeleted(page))
			BloomInitPage(page, 0);

		if (BloomPageAddItem(&blstate, page, itup))
		{
			/* Success!  Apply the change, clean up, and exit */
			GenericXLogFinish(state);
			UnlockReleaseBuffer(buffer);
			ReleaseBuffer(metaBuffer);
			MemoryContextSwitchTo(oldCtx);
			MemoryContextDelete(insertCtx);
			return false;
		}

		/* Didn't fit, must try other pages */
		GenericXLogAbort(state);
		UnlockReleaseBuffer(buffer);
	}
	else
	{
		/* No entries in notFullPage */
		LockBuffer(metaBuffer, BUFFER_LOCK_UNLOCK);
	}

	/*
	 * Try other pages in notFullPage array.  We will have to change nStart in
	 * metapage.  Thus, grab exclusive lock on metapage.
	 */
	LockBuffer(metaBuffer, BUFFER_LOCK_EXCLUSIVE);

	/* nStart might have changed while we didn't have lock */
	nStart = metaData->nStart;

	/* Skip first page if we already tried it above */
	if (nStart < metaData->nEnd &&
		blkno == metaData->notFullPage[nStart])
		nStart++;

	/*
	 * This loop iterates for each page we try from the notFullPage array, and
	 * will also initialize a GenericXLogState for the fallback case of having
	 * to allocate a new page.
	 */
	for (;;)
	{
		state = GenericXLogStart(index);

		/* get modifiable copy of metapage */
		metaPage = GenericXLogRegisterBuffer(state, metaBuffer, 0);
		metaData = BloomPageGetMeta(metaPage);

		if (nStart >= metaData->nEnd)
			break;				/* no more entries in notFullPage array */

		blkno = metaData->notFullPage[nStart];
		Assert(blkno != InvalidBlockNumber);

		buffer = ReadBuffer(index, blkno);
		LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);
		page = GenericXLogRegisterBuffer(state, buffer, 0);

		/* Basically same logic as above */
		if (PageIsNew(page) || BloomPageIsDeleted(page))
			BloomInitPage(page, 0);

		if (BloomPageAddItem(&blstate, page, itup))
		{
			/* Success!  Apply the changes, clean up, and exit */
			metaData->nStart = nStart;
			GenericXLogFinish(state);
			UnlockReleaseBuffer(buffer);
			UnlockReleaseBuffer(metaBuffer);
			MemoryContextSwitchTo(oldCtx);
			MemoryContextDelete(insertCtx);
			return false;
		}

		/* Didn't fit, must try other pages */
		GenericXLogAbort(state);
		UnlockReleaseBuffer(buffer);
		nStart++;
	}

	/*
	 * Didn't find place to insert in notFullPage array.  Allocate new page.
	 * (XXX is it good to do this while holding ex-lock on the metapage??)
	 */
	buffer = BloomNewBuffer(index);

	page = GenericXLogRegisterBuffer(state, buffer, GENERIC_XLOG_FULL_IMAGE);
	BloomInitPage(page, 0);

	if (!BloomPageAddItem(&blstate, page, itup))
	{
		/* We shouldn't be here since we're inserting to an empty page */
		elog(ERROR, "could not add new bloom tuple to empty page");
	}

	/* Reset notFullPage array to contain just this new page */
	metaData->nStart = 0;
	metaData->nEnd = 1;
	metaData->notFullPage[0] = BufferGetBlockNumber(buffer);

	/* Apply the changes, clean up, and exit */
	GenericXLogFinish(state);

	UnlockReleaseBuffer(buffer);
	UnlockReleaseBuffer(metaBuffer);

	MemoryContextSwitchTo(oldCtx);
	MemoryContextDelete(insertCtx);

	return false;
}