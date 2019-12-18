#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_19__ {long allocatedMemory; TYPE_2__* ginstate; } ;
struct TYPE_18__ {scalar_t__ head; scalar_t__ tail; } ;
struct TYPE_17__ {int /*<<< orphan*/  index; } ;
struct TYPE_16__ {int maxvalues; } ;
struct TYPE_15__ {scalar_t__ rightlink; } ;
typedef  long Size ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ KeyArray ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  IndexBulkDeleteResult ;
typedef  TYPE_2__ GinState ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  TYPE_3__ GinMetaPageData ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ BuildAccumulator ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionalLockPage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 scalar_t__ FirstOffsetNumber ; 
 int /*<<< orphan*/  GIN_EXCLUSIVE ; 
 scalar_t__ GIN_METAPAGE_BLKNO ; 
 int /*<<< orphan*/  GIN_SHARE ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 TYPE_3__* GinPageGetMeta (int /*<<< orphan*/ ) ; 
 TYPE_13__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageHasFullRow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageIsDeleted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexFreeSpaceMapVacuum (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ IsAutoVacuumWorkerProcess () ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockPage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockPage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int autovacuum_work_mem ; 
 int /*<<< orphan*/  ginBeginBAScan (TYPE_4__*) ; 
 int /*<<< orphan*/  ginEntryInsert (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ginGetBAEntry (TYPE_4__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ginInitBA (TYPE_4__*) ; 
 int /*<<< orphan*/  initKeyArray (TYPE_1__*,int) ; 
 int maintenance_work_mem ; 
 int /*<<< orphan*/  processPendingPage (TYPE_4__*,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  shiftList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vacuum_delay_point () ; 
 long work_mem ; 

void
ginInsertCleanup(GinState *ginstate, bool full_clean,
				 bool fill_fsm, bool forceCleanup,
				 IndexBulkDeleteResult *stats)
{
	Relation	index = ginstate->index;
	Buffer		metabuffer,
				buffer;
	Page		metapage,
				page;
	GinMetaPageData *metadata;
	MemoryContext opCtx,
				oldCtx;
	BuildAccumulator accum;
	KeyArray	datums;
	BlockNumber blkno,
				blknoFinish;
	bool		cleanupFinish = false;
	bool		fsm_vac = false;
	Size		workMemory;

	/*
	 * We would like to prevent concurrent cleanup process. For that we will
	 * lock metapage in exclusive mode using LockPage() call. Nobody other
	 * will use that lock for metapage, so we keep possibility of concurrent
	 * insertion into pending list
	 */

	if (forceCleanup)
	{
		/*
		 * We are called from [auto]vacuum/analyze or gin_clean_pending_list()
		 * and we would like to wait concurrent cleanup to finish.
		 */
		LockPage(index, GIN_METAPAGE_BLKNO, ExclusiveLock);
		workMemory =
			(IsAutoVacuumWorkerProcess() && autovacuum_work_mem != -1) ?
			autovacuum_work_mem : maintenance_work_mem;
	}
	else
	{
		/*
		 * We are called from regular insert and if we see concurrent cleanup
		 * just exit in hope that concurrent process will clean up pending
		 * list.
		 */
		if (!ConditionalLockPage(index, GIN_METAPAGE_BLKNO, ExclusiveLock))
			return;
		workMemory = work_mem;
	}

	metabuffer = ReadBuffer(index, GIN_METAPAGE_BLKNO);
	LockBuffer(metabuffer, GIN_SHARE);
	metapage = BufferGetPage(metabuffer);
	metadata = GinPageGetMeta(metapage);

	if (metadata->head == InvalidBlockNumber)
	{
		/* Nothing to do */
		UnlockReleaseBuffer(metabuffer);
		UnlockPage(index, GIN_METAPAGE_BLKNO, ExclusiveLock);
		return;
	}

	/*
	 * Remember a tail page to prevent infinite cleanup if other backends add
	 * new tuples faster than we can cleanup.
	 */
	blknoFinish = metadata->tail;

	/*
	 * Read and lock head of pending list
	 */
	blkno = metadata->head;
	buffer = ReadBuffer(index, blkno);
	LockBuffer(buffer, GIN_SHARE);
	page = BufferGetPage(buffer);

	LockBuffer(metabuffer, GIN_UNLOCK);

	/*
	 * Initialize.  All temporary space will be in opCtx
	 */
	opCtx = AllocSetContextCreate(CurrentMemoryContext,
								  "GIN insert cleanup temporary context",
								  ALLOCSET_DEFAULT_SIZES);

	oldCtx = MemoryContextSwitchTo(opCtx);

	initKeyArray(&datums, 128);
	ginInitBA(&accum);
	accum.ginstate = ginstate;

	/*
	 * At the top of this loop, we have pin and lock on the current page of
	 * the pending list.  However, we'll release that before exiting the loop.
	 * Note we also have pin but not lock on the metapage.
	 */
	for (;;)
	{
		Assert(!GinPageIsDeleted(page));

		/*
		 * Are we walk through the page which as we remember was a tail when
		 * we start our cleanup?  But if caller asks us to clean up whole
		 * pending list then ignore old tail, we will work until list becomes
		 * empty.
		 */
		if (blkno == blknoFinish && full_clean == false)
			cleanupFinish = true;

		/*
		 * read page's datums into accum
		 */
		processPendingPage(&accum, &datums, page, FirstOffsetNumber);

		vacuum_delay_point();

		/*
		 * Is it time to flush memory to disk?	Flush if we are at the end of
		 * the pending list, or if we have a full row and memory is getting
		 * full.
		 */
		if (GinPageGetOpaque(page)->rightlink == InvalidBlockNumber ||
			(GinPageHasFullRow(page) &&
			 (accum.allocatedMemory >= workMemory * 1024L)))
		{
			ItemPointerData *list;
			uint32		nlist;
			Datum		key;
			GinNullCategory category;
			OffsetNumber maxoff,
						attnum;

			/*
			 * Unlock current page to increase performance. Changes of page
			 * will be checked later by comparing maxoff after completion of
			 * memory flush.
			 */
			maxoff = PageGetMaxOffsetNumber(page);
			LockBuffer(buffer, GIN_UNLOCK);

			/*
			 * Moving collected data into regular structure can take
			 * significant amount of time - so, run it without locking pending
			 * list.
			 */
			ginBeginBAScan(&accum);
			while ((list = ginGetBAEntry(&accum,
										 &attnum, &key, &category, &nlist)) != NULL)
			{
				ginEntryInsert(ginstate, attnum, key, category,
							   list, nlist, NULL);
				vacuum_delay_point();
			}

			/*
			 * Lock the whole list to remove pages
			 */
			LockBuffer(metabuffer, GIN_EXCLUSIVE);
			LockBuffer(buffer, GIN_SHARE);

			Assert(!GinPageIsDeleted(page));

			/*
			 * While we left the page unlocked, more stuff might have gotten
			 * added to it.  If so, process those entries immediately.  There
			 * shouldn't be very many, so we don't worry about the fact that
			 * we're doing this with exclusive lock. Insertion algorithm
			 * guarantees that inserted row(s) will not continue on next page.
			 * NOTE: intentionally no vacuum_delay_point in this loop.
			 */
			if (PageGetMaxOffsetNumber(page) != maxoff)
			{
				ginInitBA(&accum);
				processPendingPage(&accum, &datums, page, maxoff + 1);

				ginBeginBAScan(&accum);
				while ((list = ginGetBAEntry(&accum,
											 &attnum, &key, &category, &nlist)) != NULL)
					ginEntryInsert(ginstate, attnum, key, category,
								   list, nlist, NULL);
			}

			/*
			 * Remember next page - it will become the new list head
			 */
			blkno = GinPageGetOpaque(page)->rightlink;
			UnlockReleaseBuffer(buffer);	/* shiftList will do exclusive
											 * locking */

			/*
			 * remove read pages from pending list, at this point all content
			 * of read pages is in regular structure
			 */
			shiftList(index, metabuffer, blkno, fill_fsm, stats);

			/* At this point, some pending pages have been freed up */
			fsm_vac = true;

			Assert(blkno == metadata->head);
			LockBuffer(metabuffer, GIN_UNLOCK);

			/*
			 * if we removed the whole pending list or we cleanup tail (which
			 * we remembered on start our cleanup process) then just exit
			 */
			if (blkno == InvalidBlockNumber || cleanupFinish)
				break;

			/*
			 * release memory used so far and reinit state
			 */
			MemoryContextReset(opCtx);
			initKeyArray(&datums, datums.maxvalues);
			ginInitBA(&accum);
		}
		else
		{
			blkno = GinPageGetOpaque(page)->rightlink;
			UnlockReleaseBuffer(buffer);
		}

		/*
		 * Read next page in pending list
		 */
		vacuum_delay_point();
		buffer = ReadBuffer(index, blkno);
		LockBuffer(buffer, GIN_SHARE);
		page = BufferGetPage(buffer);
	}

	UnlockPage(index, GIN_METAPAGE_BLKNO, ExclusiveLock);
	ReleaseBuffer(metabuffer);

	/*
	 * As pending list pages can have a high churn rate, it is desirable to
	 * recycle them immediately to the FreeSpaceMap when ordinary backends
	 * clean the list.
	 */
	if (fsm_vac && fill_fsm)
		IndexFreeSpaceMapVacuum(index);

	/* Clean up temporary space */
	MemoryContextSwitchTo(oldCtx);
	MemoryContextDelete(opCtx);
}