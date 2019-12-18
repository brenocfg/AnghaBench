#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int status; int memtupcount; int memtupsize; void** memtuples; int bound; int /*<<< orphan*/  ru_start; int /*<<< orphan*/  bounded; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  void* SortTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  COMPARETUP (TYPE_1__*,void**,void**) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LACKMEM (TYPE_1__*) ; 
 int /*<<< orphan*/  LEADER (TYPE_1__*) ; 
 int /*<<< orphan*/  LOG ; 
#define  TSS_BOUNDED 130 
#define  TSS_BUILDRUNS 129 
#define  TSS_INITIAL 128 
 int /*<<< orphan*/  dumptuples (TYPE_1__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_sort_tuple (TYPE_1__*,void**) ; 
 int /*<<< orphan*/  grow_memtuples (TYPE_1__*) ; 
 int /*<<< orphan*/  inittapes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  make_bounded_heap (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_rusage_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_sort ; 
 int /*<<< orphan*/  tuplesort_heap_replace_top (TYPE_1__*,void**) ; 

__attribute__((used)) static void
puttuple_common(Tuplesortstate *state, SortTuple *tuple)
{
	Assert(!LEADER(state));

	switch (state->status)
	{
		case TSS_INITIAL:

			/*
			 * Save the tuple into the unsorted array.  First, grow the array
			 * as needed.  Note that we try to grow the array when there is
			 * still one free slot remaining --- if we fail, there'll still be
			 * room to store the incoming tuple, and then we'll switch to
			 * tape-based operation.
			 */
			if (state->memtupcount >= state->memtupsize - 1)
			{
				(void) grow_memtuples(state);
				Assert(state->memtupcount < state->memtupsize);
			}
			state->memtuples[state->memtupcount++] = *tuple;

			/*
			 * Check if it's time to switch over to a bounded heapsort. We do
			 * so if the input tuple count exceeds twice the desired tuple
			 * count (this is a heuristic for where heapsort becomes cheaper
			 * than a quicksort), or if we've just filled workMem and have
			 * enough tuples to meet the bound.
			 *
			 * Note that once we enter TSS_BOUNDED state we will always try to
			 * complete the sort that way.  In the worst case, if later input
			 * tuples are larger than earlier ones, this might cause us to
			 * exceed workMem significantly.
			 */
			if (state->bounded &&
				(state->memtupcount > state->bound * 2 ||
				 (state->memtupcount > state->bound && LACKMEM(state))))
			{
#ifdef TRACE_SORT
				if (trace_sort)
					elog(LOG, "switching to bounded heapsort at %d tuples: %s",
						 state->memtupcount,
						 pg_rusage_show(&state->ru_start));
#endif
				make_bounded_heap(state);
				return;
			}

			/*
			 * Done if we still fit in available memory and have array slots.
			 */
			if (state->memtupcount < state->memtupsize && !LACKMEM(state))
				return;

			/*
			 * Nope; time to switch to tape-based operation.
			 */
			inittapes(state, true);

			/*
			 * Dump all tuples.
			 */
			dumptuples(state, false);
			break;

		case TSS_BOUNDED:

			/*
			 * We don't want to grow the array here, so check whether the new
			 * tuple can be discarded before putting it in.  This should be a
			 * good speed optimization, too, since when there are many more
			 * input tuples than the bound, most input tuples can be discarded
			 * with just this one comparison.  Note that because we currently
			 * have the sort direction reversed, we must check for <= not >=.
			 */
			if (COMPARETUP(state, tuple, &state->memtuples[0]) <= 0)
			{
				/* new tuple <= top of the heap, so we can discard it */
				free_sort_tuple(state, tuple);
				CHECK_FOR_INTERRUPTS();
			}
			else
			{
				/* discard top of heap, replacing it with the new tuple */
				free_sort_tuple(state, &state->memtuples[0]);
				tuplesort_heap_replace_top(state, tuple);
			}
			break;

		case TSS_BUILDRUNS:

			/*
			 * Save the tuple into the unsorted array (there must be space)
			 */
			state->memtuples[state->memtupcount++] = *tuple;

			/*
			 * If we are over the memory limit, dump all tuples.
			 */
			dumptuples(state, false);
			break;

		default:
			elog(ERROR, "invalid tuplesort state");
			break;
	}
}