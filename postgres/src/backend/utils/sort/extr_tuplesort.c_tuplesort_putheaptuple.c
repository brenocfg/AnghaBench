#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sortcontext; } ;
typedef  TYPE_1__ Tuplesortstate ;
typedef  int /*<<< orphan*/  SortTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  scalar_t__ HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  COPYTUP (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puttuple_common (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
tuplesort_putheaptuple(Tuplesortstate *state, HeapTuple tup)
{
	MemoryContext oldcontext = MemoryContextSwitchTo(state->sortcontext);
	SortTuple	stup;

	/*
	 * Copy the given tuple into memory we control, and decrease availMem.
	 * Then call the common code.
	 */
	COPYTUP(state, &stup, (void *) tup);

	puttuple_common(state, &stup);

	MemoryContextSwitchTo(oldcontext);
}