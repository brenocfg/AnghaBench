#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  scalar_t__ MinimalTuple ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecStoreMinimalTuple (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ heap_copy_minimal_tuple (scalar_t__) ; 
 scalar_t__ tuplestore_gettuple (int /*<<< orphan*/ *,int,int*) ; 

bool
tuplestore_gettupleslot(Tuplestorestate *state, bool forward,
						bool copy, TupleTableSlot *slot)
{
	MinimalTuple tuple;
	bool		should_free;

	tuple = (MinimalTuple) tuplestore_gettuple(state, forward, &should_free);

	if (tuple)
	{
		if (copy && !should_free)
		{
			tuple = heap_copy_minimal_tuple(tuple);
			should_free = true;
		}
		ExecStoreMinimalTuple(tuple, slot, should_free);
		return true;
	}
	else
	{
		ExecClearTuple(slot);
		return false;
	}
}