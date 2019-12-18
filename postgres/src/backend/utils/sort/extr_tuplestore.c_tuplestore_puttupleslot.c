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
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
typedef  scalar_t__ MinimalTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 scalar_t__ ExecCopySlotMinimalTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetMemoryChunkSpace (scalar_t__) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_puttuple_common (TYPE_1__*,void*) ; 

void
tuplestore_puttupleslot(Tuplestorestate *state,
						TupleTableSlot *slot)
{
	MinimalTuple tuple;
	MemoryContext oldcxt = MemoryContextSwitchTo(state->context);

	/*
	 * Form a MinimalTuple in working memory
	 */
	tuple = ExecCopySlotMinimalTuple(slot);
	USEMEM(state, GetMemoryChunkSpace(tuple));

	tuplestore_puttuple_common(state, (void *) tuple);

	MemoryContextSwitchTo(oldcxt);
}