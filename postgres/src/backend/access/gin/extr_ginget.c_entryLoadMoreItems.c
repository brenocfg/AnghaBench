#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int fullScan; int /*<<< orphan*/  itemptr; } ;
struct TYPE_12__ {void* buffer; } ;
struct TYPE_11__ {int isFinished; int offset; int nlist; void* buffer; int /*<<< orphan*/ * list; TYPE_5__ btree; int /*<<< orphan*/  curItem; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  TYPE_1__ GinState ;
typedef  TYPE_2__* GinScanEntry ;
typedef  TYPE_3__ GinBtreeStack ;

/* Variables and functions */
 int /*<<< orphan*/  BufferGetPage (void*) ; 
 int /*<<< orphan*/  BufferIsValid (void*) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  FirstOffsetNumber ; 
 int GIN_DELETED ; 
 int /*<<< orphan*/  GIN_SHARE ; 
 int /*<<< orphan*/  GIN_UNLOCK ; 
 int /*<<< orphan*/ * GinDataLeafPageGetItems (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GinDataPageGetRightBound (int /*<<< orphan*/ ) ; 
 scalar_t__ GinItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GinItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 TYPE_9__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageRightMost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IncrBufferRefCount (void*) ; 
 void* InvalidBuffer ; 
 int InvalidOffsetNumber ; 
 scalar_t__ ItemPointerIsLossyPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockBuffer (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetNumberNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (void*) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (void*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freeGinBtreeStack (TYPE_3__*) ; 
 scalar_t__ ginCompareItemPointers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* ginFindLeafPage (TYPE_5__*,int,int,int /*<<< orphan*/ ) ; 
 void* ginStepRight (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
entryLoadMoreItems(GinState *ginstate, GinScanEntry entry,
				   ItemPointerData advancePast, Snapshot snapshot)
{
	Page		page;
	int			i;
	bool		stepright;

	if (!BufferIsValid(entry->buffer))
	{
		entry->isFinished = true;
		return;
	}

	/*
	 * We have two strategies for finding the correct page: step right from
	 * the current page, or descend the tree again from the root. If
	 * advancePast equals the current item, the next matching item should be
	 * on the next page, so we step right. Otherwise, descend from root.
	 */
	if (ginCompareItemPointers(&entry->curItem, &advancePast) == 0)
	{
		stepright = true;
		LockBuffer(entry->buffer, GIN_SHARE);
	}
	else
	{
		GinBtreeStack *stack;

		ReleaseBuffer(entry->buffer);

		/*
		 * Set the search key, and find the correct leaf page.
		 */
		if (ItemPointerIsLossyPage(&advancePast))
		{
			ItemPointerSet(&entry->btree.itemptr,
						   GinItemPointerGetBlockNumber(&advancePast) + 1,
						   FirstOffsetNumber);
		}
		else
		{
			ItemPointerSet(&entry->btree.itemptr,
						   GinItemPointerGetBlockNumber(&advancePast),
						   OffsetNumberNext(GinItemPointerGetOffsetNumber(&advancePast)));
		}
		entry->btree.fullScan = false;
		stack = ginFindLeafPage(&entry->btree, true, false, snapshot);

		/* we don't need the stack, just the buffer. */
		entry->buffer = stack->buffer;
		IncrBufferRefCount(entry->buffer);
		freeGinBtreeStack(stack);
		stepright = false;
	}

	elog(DEBUG2, "entryLoadMoreItems, %u/%u, skip: %d",
		 GinItemPointerGetBlockNumber(&advancePast),
		 GinItemPointerGetOffsetNumber(&advancePast),
		 !stepright);

	page = BufferGetPage(entry->buffer);
	for (;;)
	{
		entry->offset = InvalidOffsetNumber;
		if (entry->list)
		{
			pfree(entry->list);
			entry->list = NULL;
			entry->nlist = 0;
		}

		if (stepright)
		{
			/*
			 * We've processed all the entries on this page. If it was the
			 * last page in the tree, we're done.
			 */
			if (GinPageRightMost(page))
			{
				UnlockReleaseBuffer(entry->buffer);
				entry->buffer = InvalidBuffer;
				entry->isFinished = true;
				return;
			}

			/*
			 * Step to next page, following the right link. then find the
			 * first ItemPointer greater than advancePast.
			 */
			entry->buffer = ginStepRight(entry->buffer,
										 ginstate->index,
										 GIN_SHARE);
			page = BufferGetPage(entry->buffer);
		}
		stepright = true;

		if (GinPageGetOpaque(page)->flags & GIN_DELETED)
			continue;			/* page was deleted by concurrent vacuum */

		/*
		 * The first item > advancePast might not be on this page, but
		 * somewhere to the right, if the page was split, or a non-match from
		 * another key in the query allowed us to skip some items from this
		 * entry. Keep following the right-links until we re-find the correct
		 * page.
		 */
		if (!GinPageRightMost(page) &&
			ginCompareItemPointers(&advancePast, GinDataPageGetRightBound(page)) >= 0)
		{
			/*
			 * the item we're looking is > the right bound of the page, so it
			 * can't be on this page.
			 */
			continue;
		}

		entry->list = GinDataLeafPageGetItems(page, &entry->nlist, advancePast);

		for (i = 0; i < entry->nlist; i++)
		{
			if (ginCompareItemPointers(&advancePast, &entry->list[i]) < 0)
			{
				entry->offset = i;

				if (GinPageRightMost(page))
				{
					/* after processing the copied items, we're done. */
					UnlockReleaseBuffer(entry->buffer);
					entry->buffer = InvalidBuffer;
				}
				else
					LockBuffer(entry->buffer, GIN_UNLOCK);
				return;
			}
		}
	}
}