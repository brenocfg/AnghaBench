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
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  scalar_t__ MinimalTuple ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  GetMemoryChunkSpace (scalar_t__) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USEMEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ heap_form_minimal_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  tuplestore_puttuple_common (TYPE_1__*,void*) ; 

void
tuplestore_putvalues(Tuplestorestate *state, TupleDesc tdesc,
					 Datum *values, bool *isnull)
{
	MinimalTuple tuple;
	MemoryContext oldcxt = MemoryContextSwitchTo(state->context);

	tuple = heap_form_minimal_tuple(tdesc, values, isnull);
	USEMEM(state, GetMemoryChunkSpace(tuple));

	tuplestore_puttuple_common(state, (void *) tuple);

	MemoryContextSwitchTo(oldcxt);
}