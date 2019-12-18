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
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  scalar_t__ HeapTuple ;

/* Variables and functions */
 scalar_t__ COPYTUP (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_puttuple_common (TYPE_1__*,void*) ; 

void
tuplestore_puttuple(Tuplestorestate *state, HeapTuple tuple)
{
	MemoryContext oldcxt = MemoryContextSwitchTo(state->context);

	/*
	 * Copy the tuple.  (Must do this even in WRITEFILE case.  Note that
	 * COPYTUP includes USEMEM, so we needn't do that here.)
	 */
	tuple = COPYTUP(state, tuple);

	tuplestore_puttuple_common(state, (void *) tuple);

	MemoryContextSwitchTo(oldcxt);
}