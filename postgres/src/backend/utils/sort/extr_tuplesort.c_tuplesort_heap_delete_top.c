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
struct TYPE_4__ {scalar_t__ memtupcount; int /*<<< orphan*/ * memtuples; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  SortTuple ;

/* Variables and functions */
 int /*<<< orphan*/  tuplesort_heap_replace_top (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tuplesort_heap_delete_top(Tuplesortstate *state)
{
	SortTuple  *memtuples = state->memtuples;
	SortTuple  *tuple;

	if (--state->memtupcount <= 0)
		return;

	/*
	 * Remove the last tuple in the heap, and re-insert it, by replacing the
	 * current top node with it.
	 */
	tuple = &memtuples[state->memtupcount];
	tuplesort_heap_replace_top(state, tuple);
}