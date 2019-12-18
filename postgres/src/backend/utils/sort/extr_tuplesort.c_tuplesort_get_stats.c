#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int allowedMem; int availMem; int status; int /*<<< orphan*/  boundUsed; scalar_t__ tapeset; } ;
typedef  TYPE_1__ Tuplesortstate ;
struct TYPE_6__ {int spaceUsed; int /*<<< orphan*/  sortMethod; int /*<<< orphan*/  spaceType; } ;
typedef  TYPE_2__ TuplesortInstrumentation ;

/* Variables and functions */
 int BLCKSZ ; 
 int LogicalTapeSetBlocks (scalar_t__) ; 
 int /*<<< orphan*/  SORT_SPACE_TYPE_DISK ; 
 int /*<<< orphan*/  SORT_SPACE_TYPE_MEMORY ; 
 int /*<<< orphan*/  SORT_TYPE_EXTERNAL_MERGE ; 
 int /*<<< orphan*/  SORT_TYPE_EXTERNAL_SORT ; 
 int /*<<< orphan*/  SORT_TYPE_QUICKSORT ; 
 int /*<<< orphan*/  SORT_TYPE_STILL_IN_PROGRESS ; 
 int /*<<< orphan*/  SORT_TYPE_TOP_N_HEAPSORT ; 
#define  TSS_FINALMERGE 130 
#define  TSS_SORTEDINMEM 129 
#define  TSS_SORTEDONTAPE 128 

void
tuplesort_get_stats(Tuplesortstate *state,
					TuplesortInstrumentation *stats)
{
	/*
	 * Note: it might seem we should provide both memory and disk usage for a
	 * disk-based sort.  However, the current code doesn't track memory space
	 * accurately once we have begun to return tuples to the caller (since we
	 * don't account for pfree's the caller is expected to do), so we cannot
	 * rely on availMem in a disk sort.  This does not seem worth the overhead
	 * to fix.  Is it worth creating an API for the memory context code to
	 * tell us how much is actually used in sortcontext?
	 */
	if (state->tapeset)
	{
		stats->spaceType = SORT_SPACE_TYPE_DISK;
		stats->spaceUsed = LogicalTapeSetBlocks(state->tapeset) * (BLCKSZ / 1024);
	}
	else
	{
		stats->spaceType = SORT_SPACE_TYPE_MEMORY;
		stats->spaceUsed = (state->allowedMem - state->availMem + 1023) / 1024;
	}

	switch (state->status)
	{
		case TSS_SORTEDINMEM:
			if (state->boundUsed)
				stats->sortMethod = SORT_TYPE_TOP_N_HEAPSORT;
			else
				stats->sortMethod = SORT_TYPE_QUICKSORT;
			break;
		case TSS_SORTEDONTAPE:
			stats->sortMethod = SORT_TYPE_EXTERNAL_SORT;
			break;
		case TSS_FINALMERGE:
			stats->sortMethod = SORT_TYPE_EXTERNAL_MERGE;
			break;
		default:
			stats->sortMethod = SORT_TYPE_STILL_IN_PROGRESS;
			break;
	}
}