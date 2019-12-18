#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t ntuples; scalar_t__ blockno; scalar_t__* offsets; } ;
struct TYPE_6__ {int isFinished; int reduceResult; size_t offset; size_t nlist; int /*<<< orphan*/ * list; int /*<<< orphan*/  curItem; int /*<<< orphan*/  buffer; TYPE_2__* matchResult; int /*<<< orphan*/ * matchIterator; scalar_t__ matchBitmap; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  GinState ;
typedef  TYPE_1__* GinScanEntry ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ GinItemPointerGetBlockNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ GinItemPointerGetOffsetNumber (int /*<<< orphan*/ *) ; 
 scalar_t__ ItemPointerIsLossyPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSet (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ItemPointerSetLossyPage (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ dropItem (TYPE_1__*) ; 
 int /*<<< orphan*/  entryLoadMoreItems (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ginCompareItemPointers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_end_iterate (int /*<<< orphan*/ *) ; 
 TYPE_2__* tbm_iterate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
entryGetItem(GinState *ginstate, GinScanEntry entry,
			 ItemPointerData advancePast, Snapshot snapshot)
{
	Assert(!entry->isFinished);

	Assert(!ItemPointerIsValid(&entry->curItem) ||
		   ginCompareItemPointers(&entry->curItem, &advancePast) <= 0);

	if (entry->matchBitmap)
	{
		/* A bitmap result */
		BlockNumber advancePastBlk = GinItemPointerGetBlockNumber(&advancePast);
		OffsetNumber advancePastOff = GinItemPointerGetOffsetNumber(&advancePast);
		bool		gotitem = false;

		do
		{
			/*
			 * If we've exhausted all items on this block, move to next block
			 * in the bitmap.
			 */
			while (entry->matchResult == NULL ||
				   (entry->matchResult->ntuples >= 0 &&
					entry->offset >= entry->matchResult->ntuples) ||
				   entry->matchResult->blockno < advancePastBlk ||
				   (ItemPointerIsLossyPage(&advancePast) &&
					entry->matchResult->blockno == advancePastBlk))
			{
				entry->matchResult = tbm_iterate(entry->matchIterator);

				if (entry->matchResult == NULL)
				{
					ItemPointerSetInvalid(&entry->curItem);
					tbm_end_iterate(entry->matchIterator);
					entry->matchIterator = NULL;
					entry->isFinished = true;
					break;
				}

				/*
				 * Reset counter to the beginning of entry->matchResult. Note:
				 * entry->offset is still greater than matchResult->ntuples if
				 * matchResult is lossy.  So, on next call we will get next
				 * result from TIDBitmap.
				 */
				entry->offset = 0;
			}
			if (entry->isFinished)
				break;

			/*
			 * We're now on the first page after advancePast which has any
			 * items on it. If it's a lossy result, return that.
			 */
			if (entry->matchResult->ntuples < 0)
			{
				ItemPointerSetLossyPage(&entry->curItem,
										entry->matchResult->blockno);

				/*
				 * We might as well fall out of the loop; we could not
				 * estimate number of results on this page to support correct
				 * reducing of result even if it's enabled.
				 */
				gotitem = true;
				break;
			}

			/*
			 * Not a lossy page. Skip over any offsets <= advancePast, and
			 * return that.
			 */
			if (entry->matchResult->blockno == advancePastBlk)
			{
				/*
				 * First, do a quick check against the last offset on the
				 * page. If that's > advancePast, so are all the other
				 * offsets.
				 */
				if (entry->matchResult->offsets[entry->matchResult->ntuples - 1] <= advancePastOff)
				{
					entry->offset = entry->matchResult->ntuples;
					continue;
				}

				/* Otherwise scan to find the first item > advancePast */
				while (entry->matchResult->offsets[entry->offset] <= advancePastOff)
					entry->offset++;
			}

			ItemPointerSet(&entry->curItem,
						   entry->matchResult->blockno,
						   entry->matchResult->offsets[entry->offset]);
			entry->offset++;
			gotitem = true;
		} while (!gotitem || (entry->reduceResult == true && dropItem(entry)));
	}
	else if (!BufferIsValid(entry->buffer))
	{
		/*
		 * A posting list from an entry tuple, or the last page of a posting
		 * tree.
		 */
		do
		{
			if (entry->offset >= entry->nlist)
			{
				ItemPointerSetInvalid(&entry->curItem);
				entry->isFinished = true;
				break;
			}

			entry->curItem = entry->list[entry->offset++];
		} while (ginCompareItemPointers(&entry->curItem, &advancePast) <= 0);
		/* XXX: shouldn't we apply the fuzzy search limit here? */
	}
	else
	{
		/* A posting tree */
		do
		{
			/* If we've processed the current batch, load more items */
			while (entry->offset >= entry->nlist)
			{
				entryLoadMoreItems(ginstate, entry, advancePast, snapshot);

				if (entry->isFinished)
				{
					ItemPointerSetInvalid(&entry->curItem);
					return;
				}
			}

			entry->curItem = entry->list[entry->offset++];

		} while (ginCompareItemPointers(&entry->curItem, &advancePast) <= 0 ||
				 (entry->reduceResult == true && dropItem(entry)));
	}
}