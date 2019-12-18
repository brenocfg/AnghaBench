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
typedef  void* uint32 ;
struct TYPE_4__ {int nKeys; void* max_buckets; void* low_mask; void* high_mask; void* indexRel; void* heapRel; int /*<<< orphan*/  readtup; int /*<<< orphan*/  writetup; int /*<<< orphan*/  copytup; int /*<<< orphan*/  comparetup; int /*<<< orphan*/  sortcontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  SortCoordinate ;
typedef  void* Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comparetup_index_hash ; 
 int /*<<< orphan*/  copytup_index ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*,void*,void*,int,char) ; 
 int /*<<< orphan*/  readtup_index ; 
 scalar_t__ trace_sort ; 
 TYPE_1__* tuplesort_begin_common (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writetup_index ; 

Tuplesortstate *
tuplesort_begin_index_hash(Relation heapRel,
						   Relation indexRel,
						   uint32 high_mask,
						   uint32 low_mask,
						   uint32 max_buckets,
						   int workMem,
						   SortCoordinate coordinate,
						   bool randomAccess)
{
	Tuplesortstate *state = tuplesort_begin_common(workMem, coordinate,
												   randomAccess);
	MemoryContext oldcontext;

	oldcontext = MemoryContextSwitchTo(state->sortcontext);

#ifdef TRACE_SORT
	if (trace_sort)
		elog(LOG,
			 "begin index sort: high_mask = 0x%x, low_mask = 0x%x, "
			 "max_buckets = 0x%x, workMem = %d, randomAccess = %c",
			 high_mask,
			 low_mask,
			 max_buckets,
			 workMem, randomAccess ? 't' : 'f');
#endif

	state->nKeys = 1;			/* Only one sort column, the hash code */

	state->comparetup = comparetup_index_hash;
	state->copytup = copytup_index;
	state->writetup = writetup_index;
	state->readtup = readtup_index;

	state->heapRel = heapRel;
	state->indexRel = indexRel;

	state->high_mask = high_mask;
	state->low_mask = low_mask;
	state->max_buckets = max_buckets;

	MemoryContextSwitchTo(oldcontext);

	return state;
}