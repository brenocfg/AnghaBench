#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;

/* Type definitions */
struct TYPE_25__ {int nEnd; scalar_t__ nStart; int /*<<< orphan*/  notFullPage; } ;
struct TYPE_24__ {int /*<<< orphan*/  sizeOfBloomTuple; } ;
struct TYPE_23__ {int /*<<< orphan*/  heapPtr; } ;
struct TYPE_22__ {int tuples_removed; } ;
struct TYPE_21__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  index; } ;
struct TYPE_20__ {scalar_t__ pd_lower; } ;
struct TYPE_19__ {int /*<<< orphan*/  maxoff; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Pointer ;
typedef  TYPE_1__* PageHeader ;
typedef  scalar_t__ Page ;
typedef  TYPE_2__ IndexVacuumInfo ;
typedef  TYPE_3__ IndexBulkDeleteResult ;
typedef  scalar_t__ (* IndexBulkDeleteCallback ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  GenericXLogState ;
typedef  scalar_t__* FreeBlockNumberArray ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  TYPE_4__ BloomTuple ;
typedef  TYPE_5__ BloomState ;
typedef  TYPE_6__ BloomMetaPageData ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BLOOM_HEAD_BLKNO ; 
 int /*<<< orphan*/  BLOOM_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  BUFFER_LOCK_EXCLUSIVE ; 
 int BloomMetaBlockN ; 
 int /*<<< orphan*/  BloomPageGetFreeSpace (TYPE_5__*,scalar_t__) ; 
 scalar_t__ BloomPageGetMaxOffset (scalar_t__) ; 
 TYPE_6__* BloomPageGetMeta (scalar_t__) ; 
 TYPE_4__* BloomPageGetNextTuple (TYPE_5__*,TYPE_4__*) ; 
 TYPE_13__* BloomPageGetOpaque (scalar_t__) ; 
 TYPE_4__* BloomPageGetTuple (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ BloomPageIsDeleted (scalar_t__) ; 
 int /*<<< orphan*/  BloomPageSetDeleted (scalar_t__) ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 int /*<<< orphan*/  GenericXLogAbort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenericXLogFinish (int /*<<< orphan*/ *) ; 
 scalar_t__ GenericXLogRegisterBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GenericXLogStart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  OffsetNumberNext (scalar_t__) ; 
 scalar_t__ PageIsNew (scalar_t__) ; 
 int /*<<< orphan*/  RBM_NORMAL ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBufferExtended (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initBloomState (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 

IndexBulkDeleteResult *
blbulkdelete(IndexVacuumInfo *info, IndexBulkDeleteResult *stats,
			 IndexBulkDeleteCallback callback, void *callback_state)
{
	Relation	index = info->index;
	BlockNumber blkno,
				npages;
	FreeBlockNumberArray notFullPage;
	int			countPage = 0;
	BloomState	state;
	Buffer		buffer;
	Page		page;
	BloomMetaPageData *metaData;
	GenericXLogState *gxlogState;

	if (stats == NULL)
		stats = (IndexBulkDeleteResult *) palloc0(sizeof(IndexBulkDeleteResult));

	initBloomState(&state, index);

	/*
	 * Iterate over the pages. We don't care about concurrently added pages,
	 * they can't contain tuples to delete.
	 */
	npages = RelationGetNumberOfBlocks(index);
	for (blkno = BLOOM_HEAD_BLKNO; blkno < npages; blkno++)
	{
		BloomTuple *itup,
				   *itupPtr,
				   *itupEnd;

		vacuum_delay_point();

		buffer = ReadBufferExtended(index, MAIN_FORKNUM, blkno,
									RBM_NORMAL, info->strategy);

		LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);
		gxlogState = GenericXLogStart(index);
		page = GenericXLogRegisterBuffer(gxlogState, buffer, 0);

		/* Ignore empty/deleted pages until blvacuumcleanup() */
		if (PageIsNew(page) || BloomPageIsDeleted(page))
		{
			UnlockReleaseBuffer(buffer);
			GenericXLogAbort(gxlogState);
			continue;
		}

		/*
		 * Iterate over the tuples.  itup points to current tuple being
		 * scanned, itupPtr points to where to save next non-deleted tuple.
		 */
		itup = itupPtr = BloomPageGetTuple(&state, page, FirstOffsetNumber);
		itupEnd = BloomPageGetTuple(&state, page,
									OffsetNumberNext(BloomPageGetMaxOffset(page)));
		while (itup < itupEnd)
		{
			/* Do we have to delete this tuple? */
			if (callback(&itup->heapPtr, callback_state))
			{
				/* Yes; adjust count of tuples that will be left on page */
				BloomPageGetOpaque(page)->maxoff--;
				stats->tuples_removed += 1;
			}
			else
			{
				/* No; copy it to itupPtr++, but skip copy if not needed */
				if (itupPtr != itup)
					memmove((Pointer) itupPtr, (Pointer) itup,
							state.sizeOfBloomTuple);
				itupPtr = BloomPageGetNextTuple(&state, itupPtr);
			}

			itup = BloomPageGetNextTuple(&state, itup);
		}

		/* Assert that we counted correctly */
		Assert(itupPtr == BloomPageGetTuple(&state, page,
											OffsetNumberNext(BloomPageGetMaxOffset(page))));

		/*
		 * Add page to new notFullPage list if we will not mark page as
		 * deleted and there is free space on it
		 */
		if (BloomPageGetMaxOffset(page) != 0 &&
			BloomPageGetFreeSpace(&state, page) >= state.sizeOfBloomTuple &&
			countPage < BloomMetaBlockN)
			notFullPage[countPage++] = blkno;

		/* Did we delete something? */
		if (itupPtr != itup)
		{
			/* Is it empty page now? */
			if (BloomPageGetMaxOffset(page) == 0)
				BloomPageSetDeleted(page);
			/* Adjust pd_lower */
			((PageHeader) page)->pd_lower = (Pointer) itupPtr - page;
			/* Finish WAL-logging */
			GenericXLogFinish(gxlogState);
		}
		else
		{
			/* Didn't change anything: abort WAL-logging */
			GenericXLogAbort(gxlogState);
		}
		UnlockReleaseBuffer(buffer);
	}

	/*
	 * Update the metapage's notFullPage list with whatever we found.  Our
	 * info could already be out of date at this point, but blinsert() will
	 * cope if so.
	 */
	buffer = ReadBuffer(index, BLOOM_METAPAGE_BLKNO);
	LockBuffer(buffer, BUFFER_LOCK_EXCLUSIVE);

	gxlogState = GenericXLogStart(index);
	page = GenericXLogRegisterBuffer(gxlogState, buffer, 0);

	metaData = BloomPageGetMeta(page);
	memcpy(metaData->notFullPage, notFullPage, sizeof(BlockNumber) * countPage);
	metaData->nStart = 0;
	metaData->nEnd = countPage;

	GenericXLogFinish(gxlogState);
	UnlockReleaseBuffer(buffer);

	return stats;
}