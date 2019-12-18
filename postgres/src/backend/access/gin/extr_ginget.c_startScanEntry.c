#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ (* findItem ) (TYPE_4__*,TYPE_3__*) ;} ;
struct TYPE_23__ {int predictNumber; int /*<<< orphan*/  buffer; int /*<<< orphan*/  off; } ;
struct TYPE_22__ {int nlist; int reduceResult; int predictNumberResult; int isFinished; int /*<<< orphan*/  attnum; int /*<<< orphan*/ * list; int /*<<< orphan*/  buffer; int /*<<< orphan*/  btree; int /*<<< orphan*/ * matchBitmap; int /*<<< orphan*/ * matchIterator; int /*<<< orphan*/  queryCategory; scalar_t__ isPartialMatch; int /*<<< orphan*/  queryKey; int /*<<< orphan*/ * matchResult; int /*<<< orphan*/  offset; int /*<<< orphan*/  curItem; } ;
struct TYPE_21__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_1__ GinState ;
typedef  TYPE_2__* GinScanEntry ;
typedef  TYPE_3__ GinBtreeStack ;
typedef  TYPE_4__ GinBtreeData ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIN_CAT_EMPTY_QUERY ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 int /*<<< orphan*/ * GinDataLeafPageGetItems (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ GinGetNPosting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinGetPostingTree (int /*<<< orphan*/ ) ; 
 scalar_t__ GinIsPostingTree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IncrBufferRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerSetMin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PredicateLockPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int collectMatchBitmap (TYPE_4__*,TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeGinBtreeStack (TYPE_3__*) ; 
 TYPE_3__* ginFindLeafPage (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ginPrepareEntryScan (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * ginReadTuple (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_3__* ginScanBeginPostingTree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ stub2 (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * tbm_begin_iterate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_end_iterate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
startScanEntry(GinState *ginstate, GinScanEntry entry, Snapshot snapshot)
{
	GinBtreeData btreeEntry;
	GinBtreeStack *stackEntry;
	Page		page;
	bool		needUnlock;

restartScanEntry:
	entry->buffer = InvalidBuffer;
	ItemPointerSetMin(&entry->curItem);
	entry->offset = InvalidOffsetNumber;
	if (entry->list)
		pfree(entry->list);
	entry->list = NULL;
	entry->nlist = 0;
	entry->matchBitmap = NULL;
	entry->matchResult = NULL;
	entry->reduceResult = false;
	entry->predictNumberResult = 0;

	/*
	 * we should find entry, and begin scan of posting tree or just store
	 * posting list in memory
	 */
	ginPrepareEntryScan(&btreeEntry, entry->attnum,
						entry->queryKey, entry->queryCategory,
						ginstate);
	stackEntry = ginFindLeafPage(&btreeEntry, true, false, snapshot);
	page = BufferGetPage(stackEntry->buffer);

	/* ginFindLeafPage() will have already checked snapshot age. */
	needUnlock = true;

	entry->isFinished = true;

	if (entry->isPartialMatch ||
		entry->queryCategory == GIN_CAT_EMPTY_QUERY)
	{
		/*
		 * btreeEntry.findItem locates the first item >= given search key.
		 * (For GIN_CAT_EMPTY_QUERY, it will find the leftmost index item
		 * because of the way the GIN_CAT_EMPTY_QUERY category code is
		 * assigned.)  We scan forward from there and collect all TIDs needed
		 * for the entry type.
		 */
		btreeEntry.findItem(&btreeEntry, stackEntry);
		if (collectMatchBitmap(&btreeEntry, stackEntry, entry, snapshot)
			== false)
		{
			/*
			 * GIN tree was seriously restructured, so we will cleanup all
			 * found data and rescan. See comments near 'return false' in
			 * collectMatchBitmap()
			 */
			if (entry->matchBitmap)
			{
				if (entry->matchIterator)
					tbm_end_iterate(entry->matchIterator);
				entry->matchIterator = NULL;
				tbm_free(entry->matchBitmap);
				entry->matchBitmap = NULL;
			}
			LockBuffer(stackEntry->buffer, GIN_UNLOCK);
			freeGinBtreeStack(stackEntry);
			goto restartScanEntry;
		}

		if (entry->matchBitmap && !tbm_is_empty(entry->matchBitmap))
		{
			entry->matchIterator = tbm_begin_iterate(entry->matchBitmap);
			entry->isFinished = false;
		}
	}
	else if (btreeEntry.findItem(&btreeEntry, stackEntry))
	{
		IndexTuple	itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, stackEntry->off));

		if (GinIsPostingTree(itup))
		{
			BlockNumber rootPostingTree = GinGetPostingTree(itup);
			GinBtreeStack *stack;
			Page		page;
			ItemPointerData minItem;

			/*
			 * This is an equality scan, so lock the root of the posting tree.
			 * It represents a lock on the exact key value, and covers all the
			 * items in the posting tree.
			 */
			PredicateLockPage(ginstate->index, rootPostingTree, snapshot);

			/*
			 * We should unlock entry page before touching posting tree to
			 * prevent deadlocks with vacuum processes. Because entry is never
			 * deleted from page and posting tree is never reduced to the
			 * posting list, we can unlock page after getting BlockNumber of
			 * root of posting tree.
			 */
			LockBuffer(stackEntry->buffer, GIN_UNLOCK);
			needUnlock = false;

			stack = ginScanBeginPostingTree(&entry->btree, ginstate->index,
											rootPostingTree, snapshot);
			entry->buffer = stack->buffer;

			/*
			 * We keep buffer pinned because we need to prevent deletion of
			 * page during scan. See GIN's vacuum implementation. RefCount is
			 * increased to keep buffer pinned after freeGinBtreeStack() call.
			 */
			IncrBufferRefCount(entry->buffer);

			page = BufferGetPage(entry->buffer);

			/*
			 * Load the first page into memory.
			 */
			ItemPointerSetMin(&minItem);
			entry->list = GinDataLeafPageGetItems(page, &entry->nlist, minItem);

			entry->predictNumberResult = stack->predictNumber * entry->nlist;

			LockBuffer(entry->buffer, GIN_UNLOCK);
			freeGinBtreeStack(stack);
			entry->isFinished = false;
		}
		else
		{
			/*
			 * Lock the entry leaf page.  This is more coarse-grained than
			 * necessary, because it will conflict with any insertions that
			 * land on the same leaf page, not only the exact key we searched
			 * for.  But locking an individual tuple would require updating
			 * that lock whenever it moves because of insertions or vacuums,
			 * which seems too complicated.
			 */
			PredicateLockPage(ginstate->index,
							  BufferGetBlockNumber(stackEntry->buffer),
							  snapshot);
			if (GinGetNPosting(itup) > 0)
			{
				entry->list = ginReadTuple(ginstate, entry->attnum, itup,
										   &entry->nlist);
				entry->predictNumberResult = entry->nlist;

				entry->isFinished = false;
			}
		}
	}
	else
	{
		/*
		 * No entry found.  Predicate lock the leaf page, to lock the place
		 * where the entry would've been, had there been one.
		 */
		PredicateLockPage(ginstate->index,
						  BufferGetBlockNumber(stackEntry->buffer), snapshot);
	}

	if (needUnlock)
		LockBuffer(stackEntry->buffer, GIN_UNLOCK);
	freeGinBtreeStack(stackEntry);
}