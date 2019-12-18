#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nentries; int* entryRes; int recheckCurItem; } ;
typedef  int GinTernaryValue ;
typedef  TYPE_1__* GinScanKey ;

/* Variables and functions */
 scalar_t__ GIN_FALSE ; 
 int GIN_MAYBE ; 
 int GIN_TRUE ; 
 int MAX_MAYBE_ENTRIES ; 
 int directBoolConsistentFn (TYPE_1__*) ; 

__attribute__((used)) static GinTernaryValue
shimTriConsistentFn(GinScanKey key)
{
	int			nmaybe;
	int			maybeEntries[MAX_MAYBE_ENTRIES];
	int			i;
	bool		boolResult;
	bool		recheck = false;
	GinTernaryValue curResult;

	/*
	 * Count how many MAYBE inputs there are, and store their indexes in
	 * maybeEntries. If there are too many MAYBE inputs, it's not feasible to
	 * test all combinations, so give up and return MAYBE.
	 */
	nmaybe = 0;
	for (i = 0; i < key->nentries; i++)
	{
		if (key->entryRes[i] == GIN_MAYBE)
		{
			if (nmaybe >= MAX_MAYBE_ENTRIES)
				return GIN_MAYBE;
			maybeEntries[nmaybe++] = i;
		}
	}

	/*
	 * If none of the inputs were MAYBE, so we can just call consistent
	 * function as is.
	 */
	if (nmaybe == 0)
		return directBoolConsistentFn(key);

	/* First call consistent function with all the maybe-inputs set FALSE */
	for (i = 0; i < nmaybe; i++)
		key->entryRes[maybeEntries[i]] = GIN_FALSE;
	curResult = directBoolConsistentFn(key);

	for (;;)
	{
		/* Twiddle the entries for next combination. */
		for (i = 0; i < nmaybe; i++)
		{
			if (key->entryRes[maybeEntries[i]] == GIN_FALSE)
			{
				key->entryRes[maybeEntries[i]] = GIN_TRUE;
				break;
			}
			else
				key->entryRes[maybeEntries[i]] = GIN_FALSE;
		}
		if (i == nmaybe)
			break;

		boolResult = directBoolConsistentFn(key);
		recheck |= key->recheckCurItem;

		if (curResult != boolResult)
			return GIN_MAYBE;
	}

	/* TRUE with recheck is taken to mean MAYBE */
	if (curResult == GIN_TRUE && recheck)
		curResult = GIN_MAYBE;

	return curResult;
}