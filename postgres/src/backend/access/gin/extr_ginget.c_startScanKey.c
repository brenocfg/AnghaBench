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
struct TYPE_8__ {int curItemMatches; int recheckCurItem; int isFinished; int nentries; scalar_t__ (* triConsistentFn ) (TYPE_2__*) ;int nrequired; int nadditional; int /*<<< orphan*/ * scanEntry; int /*<<< orphan*/ * requiredEntries; int /*<<< orphan*/ * additionalEntries; scalar_t__* entryRes; int /*<<< orphan*/  curItem; } ;
struct TYPE_7__ {int /*<<< orphan*/  keyCtx; int /*<<< orphan*/  tempCtx; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  GinState ;
typedef  TYPE_1__* GinScanOpaque ;
typedef  TYPE_2__* GinScanKey ;
typedef  int /*<<< orphan*/  GinScanEntry ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 scalar_t__ GIN_FALSE ; 
 scalar_t__ GIN_MAYBE ; 
 int /*<<< orphan*/  ItemPointerSetMin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entryIndexByFrequencyCmp ; 
 void* palloc (int) ; 
 int /*<<< orphan*/  qsort_arg (int*,int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
startScanKey(GinState *ginstate, GinScanOpaque so, GinScanKey key)
{
	MemoryContext oldCtx = CurrentMemoryContext;
	int			i;
	int			j;
	int		   *entryIndexes;

	ItemPointerSetMin(&key->curItem);
	key->curItemMatches = false;
	key->recheckCurItem = false;
	key->isFinished = false;

	/*
	 * Divide the entries into two distinct sets: required and additional.
	 * Additional entries are not enough for a match alone, without any items
	 * from the required set, but are needed by the consistent function to
	 * decide if an item matches. When scanning, we can skip over items from
	 * additional entries that have no corresponding matches in any of the
	 * required entries. That speeds up queries like "frequent & rare"
	 * considerably, if the frequent term can be put in the additional set.
	 *
	 * There can be many legal ways to divide them entries into these two
	 * sets. A conservative division is to just put everything in the required
	 * set, but the more you can put in the additional set, the more you can
	 * skip during the scan. To maximize skipping, we try to put as many
	 * frequent items as possible into additional, and less frequent ones into
	 * required. To do that, sort the entries by frequency
	 * (predictNumberResult), and put entries into the required set in that
	 * order, until the consistent function says that none of the remaining
	 * entries can form a match, without any items from the required set. The
	 * rest go to the additional set.
	 */
	if (key->nentries > 1)
	{
		MemoryContextSwitchTo(so->tempCtx);

		entryIndexes = (int *) palloc(sizeof(int) * key->nentries);
		for (i = 0; i < key->nentries; i++)
			entryIndexes[i] = i;
		qsort_arg(entryIndexes, key->nentries, sizeof(int),
				  entryIndexByFrequencyCmp, key);

		for (i = 0; i < key->nentries - 1; i++)
		{
			/* Pass all entries <= i as FALSE, and the rest as MAYBE */
			for (j = 0; j <= i; j++)
				key->entryRes[entryIndexes[j]] = GIN_FALSE;
			for (j = i + 1; j < key->nentries; j++)
				key->entryRes[entryIndexes[j]] = GIN_MAYBE;

			if (key->triConsistentFn(key) == GIN_FALSE)
				break;
		}
		/* i is now the last required entry. */

		MemoryContextSwitchTo(so->keyCtx);

		key->nrequired = i + 1;
		key->nadditional = key->nentries - key->nrequired;
		key->requiredEntries = palloc(key->nrequired * sizeof(GinScanEntry));
		key->additionalEntries = palloc(key->nadditional * sizeof(GinScanEntry));

		j = 0;
		for (i = 0; i < key->nrequired; i++)
			key->requiredEntries[i] = key->scanEntry[entryIndexes[j++]];
		for (i = 0; i < key->nadditional; i++)
			key->additionalEntries[i] = key->scanEntry[entryIndexes[j++]];

		/* clean up after consistentFn calls (also frees entryIndexes) */
		MemoryContextReset(so->tempCtx);
	}
	else
	{
		MemoryContextSwitchTo(so->keyCtx);

		key->nrequired = 1;
		key->nadditional = 0;
		key->requiredEntries = palloc(1 * sizeof(GinScanEntry));
		key->requiredEntries[0] = key->scanEntry[0];
	}
	MemoryContextSwitchTo(oldCtx);
}