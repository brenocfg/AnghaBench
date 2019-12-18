#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_8__ {int isFinished; void* curItem; } ;
struct TYPE_7__ {int isFinished; void* curItem; size_t nrequired; size_t nadditional; size_t nentries; size_t nuserentries; int* entryRes; int (* triConsistentFn ) (TYPE_1__*) ;int curItemMatches; int recheckCurItem; TYPE_2__** scanEntry; TYPE_2__** additionalEntries; TYPE_2__** requiredEntries; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  void* ItemPointerData ;
typedef  int GinTernaryValue ;
typedef  int /*<<< orphan*/  GinState ;
typedef  TYPE_1__* GinScanKey ;
typedef  TYPE_2__* GinScanEntry ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
#define  GIN_FALSE 130 
#define  GIN_MAYBE 129 
#define  GIN_TRUE 128 
 scalar_t__ GinItemPointerGetBlockNumber (void**) ; 
 scalar_t__ GinItemPointerGetOffsetNumber (void**) ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int ItemPointerIsLossyPage (void**) ; 
 int /*<<< orphan*/  ItemPointerSet (void**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerSetLossyPage (void**,scalar_t__) ; 
 int /*<<< orphan*/  ItemPointerSetMax (void**) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetNumberPrev (scalar_t__) ; 
 int /*<<< orphan*/  entryGetItem (int /*<<< orphan*/ *,TYPE_2__*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ ginCompareItemPointers (void**,void**) ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 

__attribute__((used)) static void
keyGetItem(GinState *ginstate, MemoryContext tempCtx, GinScanKey key,
		   ItemPointerData advancePast, Snapshot snapshot)
{
	ItemPointerData minItem;
	ItemPointerData curPageLossy;
	uint32		i;
	bool		haveLossyEntry;
	GinScanEntry entry;
	GinTernaryValue res;
	MemoryContext oldCtx;
	bool		allFinished;

	Assert(!key->isFinished);

	/*
	 * We might have already tested this item; if so, no need to repeat work.
	 * (Note: the ">" case can happen, if advancePast is exact but we
	 * previously had to set curItem to a lossy-page pointer.)
	 */
	if (ginCompareItemPointers(&key->curItem, &advancePast) > 0)
		return;

	/*
	 * Find the minimum item > advancePast among the active entry streams.
	 *
	 * Note: a lossy-page entry is encoded by a ItemPointer with max value for
	 * offset (0xffff), so that it will sort after any exact entries for the
	 * same page.  So we'll prefer to return exact pointers not lossy
	 * pointers, which is good.
	 */
	ItemPointerSetMax(&minItem);
	allFinished = true;
	for (i = 0; i < key->nrequired; i++)
	{
		entry = key->requiredEntries[i];

		if (entry->isFinished)
			continue;

		/*
		 * Advance this stream if necessary.
		 *
		 * In particular, since entry->curItem was initialized with
		 * ItemPointerSetMin, this ensures we fetch the first item for each
		 * entry on the first call.
		 */
		if (ginCompareItemPointers(&entry->curItem, &advancePast) <= 0)
		{
			entryGetItem(ginstate, entry, advancePast, snapshot);
			if (entry->isFinished)
				continue;
		}

		allFinished = false;
		if (ginCompareItemPointers(&entry->curItem, &minItem) < 0)
			minItem = entry->curItem;
	}

	if (allFinished)
	{
		/* all entries are finished */
		key->isFinished = true;
		return;
	}

	/*
	 * Ok, we now know that there are no matches < minItem.
	 *
	 * If minItem is lossy, it means that there were no exact items on the
	 * page among requiredEntries, because lossy pointers sort after exact
	 * items. However, there might be exact items for the same page among
	 * additionalEntries, so we mustn't advance past them.
	 */
	if (ItemPointerIsLossyPage(&minItem))
	{
		if (GinItemPointerGetBlockNumber(&advancePast) <
			GinItemPointerGetBlockNumber(&minItem))
		{
			ItemPointerSet(&advancePast,
						   GinItemPointerGetBlockNumber(&minItem),
						   InvalidOffsetNumber);
		}
	}
	else
	{
		Assert(GinItemPointerGetOffsetNumber(&minItem) > 0);
		ItemPointerSet(&advancePast,
					   GinItemPointerGetBlockNumber(&minItem),
					   OffsetNumberPrev(GinItemPointerGetOffsetNumber(&minItem)));
	}

	/*
	 * We might not have loaded all the entry streams for this TID yet. We
	 * could call the consistent function, passing MAYBE for those entries, to
	 * see if it can decide if this TID matches based on the information we
	 * have. But if the consistent-function is expensive, and cannot in fact
	 * decide with partial information, that could be a big loss. So, load all
	 * the additional entries, before calling the consistent function.
	 */
	for (i = 0; i < key->nadditional; i++)
	{
		entry = key->additionalEntries[i];

		if (entry->isFinished)
			continue;

		if (ginCompareItemPointers(&entry->curItem, &advancePast) <= 0)
		{
			entryGetItem(ginstate, entry, advancePast, snapshot);
			if (entry->isFinished)
				continue;
		}

		/*
		 * Normally, none of the items in additionalEntries can have a curItem
		 * larger than minItem. But if minItem is a lossy page, then there
		 * might be exact items on the same page among additionalEntries.
		 */
		if (ginCompareItemPointers(&entry->curItem, &minItem) < 0)
		{
			Assert(ItemPointerIsLossyPage(&minItem));
			minItem = entry->curItem;
		}
	}

	/*
	 * Ok, we've advanced all the entries up to minItem now. Set key->curItem,
	 * and perform consistentFn test.
	 *
	 * Lossy-page entries pose a problem, since we don't know the correct
	 * entryRes state to pass to the consistentFn, and we also don't know what
	 * its combining logic will be (could be AND, OR, or even NOT). If the
	 * logic is OR then the consistentFn might succeed for all items in the
	 * lossy page even when none of the other entries match.
	 *
	 * Our strategy is to call the tri-state consistent function, with the
	 * lossy-page entries set to MAYBE, and all the other entries FALSE. If it
	 * returns FALSE, none of the lossy items alone are enough for a match, so
	 * we don't need to return a lossy-page pointer. Otherwise, return a
	 * lossy-page pointer to indicate that the whole heap page must be
	 * checked.  (On subsequent calls, we'll do nothing until minItem is past
	 * the page altogether, thus ensuring that we never return both regular
	 * and lossy pointers for the same page.)
	 *
	 * An exception is that it doesn't matter what we pass for lossy pointers
	 * in "hidden" entries, because the consistentFn's result can't depend on
	 * them. We could pass them as MAYBE as well, but if we're using the
	 * "shim" implementation of a tri-state consistent function (see
	 * ginlogic.c), it's better to pass as few MAYBEs as possible. So pass
	 * them as true.
	 *
	 * Note that only lossy-page entries pointing to the current item's page
	 * should trigger this processing; we might have future lossy pages in the
	 * entry array, but they aren't relevant yet.
	 */
	key->curItem = minItem;
	ItemPointerSetLossyPage(&curPageLossy,
							GinItemPointerGetBlockNumber(&key->curItem));
	haveLossyEntry = false;
	for (i = 0; i < key->nentries; i++)
	{
		entry = key->scanEntry[i];
		if (entry->isFinished == false &&
			ginCompareItemPointers(&entry->curItem, &curPageLossy) == 0)
		{
			if (i < key->nuserentries)
				key->entryRes[i] = GIN_MAYBE;
			else
				key->entryRes[i] = GIN_TRUE;
			haveLossyEntry = true;
		}
		else
			key->entryRes[i] = GIN_FALSE;
	}

	/* prepare for calling consistentFn in temp context */
	oldCtx = MemoryContextSwitchTo(tempCtx);

	if (haveLossyEntry)
	{
		/* Have lossy-page entries, so see if whole page matches */
		res = key->triConsistentFn(key);

		if (res == GIN_TRUE || res == GIN_MAYBE)
		{
			/* Yes, so clean up ... */
			MemoryContextSwitchTo(oldCtx);
			MemoryContextReset(tempCtx);

			/* and return lossy pointer for whole page */
			key->curItem = curPageLossy;
			key->curItemMatches = true;
			key->recheckCurItem = true;
			return;
		}
	}

	/*
	 * At this point we know that we don't need to return a lossy whole-page
	 * pointer, but we might have matches for individual exact item pointers,
	 * possibly in combination with a lossy pointer. Pass lossy pointers as
	 * MAYBE to the ternary consistent function, to let it decide if this
	 * tuple satisfies the overall key, even though we don't know if the lossy
	 * entries match.
	 *
	 * Prepare entryRes array to be passed to consistentFn.
	 */
	for (i = 0; i < key->nentries; i++)
	{
		entry = key->scanEntry[i];
		if (entry->isFinished)
			key->entryRes[i] = GIN_FALSE;
#if 0

		/*
		 * This case can't currently happen, because we loaded all the entries
		 * for this item earlier.
		 */
		else if (ginCompareItemPointers(&entry->curItem, &advancePast) <= 0)
			key->entryRes[i] = GIN_MAYBE;
#endif
		else if (ginCompareItemPointers(&entry->curItem, &curPageLossy) == 0)
			key->entryRes[i] = GIN_MAYBE;
		else if (ginCompareItemPointers(&entry->curItem, &minItem) == 0)
			key->entryRes[i] = GIN_TRUE;
		else
			key->entryRes[i] = GIN_FALSE;
	}

	res = key->triConsistentFn(key);

	switch (res)
	{
		case GIN_TRUE:
			key->curItemMatches = true;
			/* triConsistentFn set recheckCurItem */
			break;

		case GIN_FALSE:
			key->curItemMatches = false;
			break;

		case GIN_MAYBE:
			key->curItemMatches = true;
			key->recheckCurItem = true;
			break;

		default:

			/*
			 * the 'default' case shouldn't happen, but if the consistent
			 * function returns something bogus, this is the safe result
			 */
			key->curItemMatches = true;
			key->recheckCurItem = true;
			break;
	}

	/*
	 * We have a tuple, and we know if it matches or not. If it's a non-match,
	 * we could continue to find the next matching tuple, but let's break out
	 * and give scanGetItem a chance to advance the other keys. They might be
	 * able to skip past to a much higher TID, allowing us to save work.
	 */

	/* clean up after consistentFn calls */
	MemoryContextSwitchTo(oldCtx);
	MemoryContextReset(tempCtx);
}