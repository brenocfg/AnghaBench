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
typedef  size_t uint32 ;
typedef  scalar_t__ int32 ;
struct TYPE_7__ {int isPartialMatch; scalar_t__ strategy; scalar_t__ searchMode; scalar_t__ attnum; int isFinished; int reduceResult; int /*<<< orphan*/  offset; scalar_t__ nlist; int /*<<< orphan*/ * list; int /*<<< orphan*/ * matchResult; int /*<<< orphan*/ * matchIterator; int /*<<< orphan*/ * matchBitmap; int /*<<< orphan*/  curItem; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * extra_data; int /*<<< orphan*/  queryCategory; int /*<<< orphan*/  queryKey; } ;
struct TYPE_6__ {size_t totalentries; int allocentries; TYPE_2__** entries; int /*<<< orphan*/  ginstate; } ;
typedef  scalar_t__ StrategyNumber ;
typedef  int /*<<< orphan*/ * Pointer ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  GinState ;
typedef  TYPE_1__* GinScanOpaque ;
typedef  int /*<<< orphan*/  GinScanEntryData ;
typedef  TYPE_2__* GinScanEntry ;
typedef  int /*<<< orphan*/  GinNullCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBuffer ; 
 int /*<<< orphan*/  InvalidOffsetNumber ; 
 int /*<<< orphan*/  ItemPointerSetMin (int /*<<< orphan*/ *) ; 
 scalar_t__ ginCompareEntries (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  palloc (int) ; 
 scalar_t__ repalloc (TYPE_2__**,int) ; 

__attribute__((used)) static GinScanEntry
ginFillScanEntry(GinScanOpaque so, OffsetNumber attnum,
				 StrategyNumber strategy, int32 searchMode,
				 Datum queryKey, GinNullCategory queryCategory,
				 bool isPartialMatch, Pointer extra_data)
{
	GinState   *ginstate = &so->ginstate;
	GinScanEntry scanEntry;
	uint32		i;

	/*
	 * Look for an existing equivalent entry.
	 *
	 * Entries with non-null extra_data are never considered identical, since
	 * we can't know exactly what the opclass might be doing with that.
	 */
	if (extra_data == NULL)
	{
		for (i = 0; i < so->totalentries; i++)
		{
			GinScanEntry prevEntry = so->entries[i];

			if (prevEntry->extra_data == NULL &&
				prevEntry->isPartialMatch == isPartialMatch &&
				prevEntry->strategy == strategy &&
				prevEntry->searchMode == searchMode &&
				prevEntry->attnum == attnum &&
				ginCompareEntries(ginstate, attnum,
								  prevEntry->queryKey,
								  prevEntry->queryCategory,
								  queryKey,
								  queryCategory) == 0)
			{
				/* Successful match */
				return prevEntry;
			}
		}
	}

	/* Nope, create a new entry */
	scanEntry = (GinScanEntry) palloc(sizeof(GinScanEntryData));
	scanEntry->queryKey = queryKey;
	scanEntry->queryCategory = queryCategory;
	scanEntry->isPartialMatch = isPartialMatch;
	scanEntry->extra_data = extra_data;
	scanEntry->strategy = strategy;
	scanEntry->searchMode = searchMode;
	scanEntry->attnum = attnum;

	scanEntry->buffer = InvalidBuffer;
	ItemPointerSetMin(&scanEntry->curItem);
	scanEntry->matchBitmap = NULL;
	scanEntry->matchIterator = NULL;
	scanEntry->matchResult = NULL;
	scanEntry->list = NULL;
	scanEntry->nlist = 0;
	scanEntry->offset = InvalidOffsetNumber;
	scanEntry->isFinished = false;
	scanEntry->reduceResult = false;

	/* Add it to so's array */
	if (so->totalentries >= so->allocentries)
	{
		so->allocentries *= 2;
		so->entries = (GinScanEntry *)
			repalloc(so->entries, so->allocentries * sizeof(GinScanEntry));
	}
	so->entries[so->totalentries++] = scanEntry;

	return scanEntry;
}