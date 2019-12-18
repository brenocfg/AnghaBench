#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int memtupcount; scalar_t__ status; int bounded; int bound; int /*<<< orphan*/ * memtuples; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  SortTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ COMPARETUP (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SERIAL (TYPE_1__*) ; 
 scalar_t__ TSS_BOUNDED ; 
 scalar_t__ TSS_INITIAL ; 
 int /*<<< orphan*/  free_sort_tuple (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reversedirection (TYPE_1__*) ; 
 int /*<<< orphan*/  tuplesort_heap_insert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplesort_heap_replace_top (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
make_bounded_heap(Tuplesortstate *state)
{
	int			tupcount = state->memtupcount;
	int			i;

	Assert(state->status == TSS_INITIAL);
	Assert(state->bounded);
	Assert(tupcount >= state->bound);
	Assert(SERIAL(state));

	/* Reverse sort direction so largest entry will be at root */
	reversedirection(state);

	state->memtupcount = 0;		/* make the heap empty */
	for (i = 0; i < tupcount; i++)
	{
		if (state->memtupcount < state->bound)
		{
			/* Insert next tuple into heap */
			/* Must copy source tuple to avoid possible overwrite */
			SortTuple	stup = state->memtuples[i];

			tuplesort_heap_insert(state, &stup);
		}
		else
		{
			/*
			 * The heap is full.  Replace the largest entry with the new
			 * tuple, or just discard it, if it's larger than anything already
			 * in the heap.
			 */
			if (COMPARETUP(state, &state->memtuples[i], &state->memtuples[0]) <= 0)
			{
				free_sort_tuple(state, &state->memtuples[i]);
				CHECK_FOR_INTERRUPTS();
			}
			else
				tuplesort_heap_replace_top(state, &state->memtuples[i]);
		}
	}

	Assert(state->memtupcount == state->bound);
	state->status = TSS_BOUNDED;
}