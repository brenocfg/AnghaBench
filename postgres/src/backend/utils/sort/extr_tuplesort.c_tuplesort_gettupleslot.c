#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* sortKeys; int /*<<< orphan*/  sortcontext; } ;
typedef  TYPE_2__ Tuplesortstate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_9__ {int /*<<< orphan*/ * tuple; int /*<<< orphan*/  datum1; } ;
struct TYPE_7__ {scalar_t__ abbrev_converter; } ;
typedef  TYPE_3__ SortTuple ;
typedef  int /*<<< orphan*/  MinimalTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecStoreMinimalTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_copy_minimal_tuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplesort_gettuple_common (TYPE_2__*,int,TYPE_3__*) ; 

bool
tuplesort_gettupleslot(Tuplesortstate *state, bool forward, bool copy,
					   TupleTableSlot *slot, Datum *abbrev)
{
	MemoryContext oldcontext = MemoryContextSwitchTo(state->sortcontext);
	SortTuple	stup;

	if (!tuplesort_gettuple_common(state, forward, &stup))
		stup.tuple = NULL;

	MemoryContextSwitchTo(oldcontext);

	if (stup.tuple)
	{
		/* Record abbreviated key for caller */
		if (state->sortKeys->abbrev_converter && abbrev)
			*abbrev = stup.datum1;

		if (copy)
			stup.tuple = heap_copy_minimal_tuple((MinimalTuple) stup.tuple);

		ExecStoreMinimalTuple((MinimalTuple) stup.tuple, slot, copy);
		return true;
	}
	else
	{
		ExecClearTuple(slot);
		return false;
	}
}