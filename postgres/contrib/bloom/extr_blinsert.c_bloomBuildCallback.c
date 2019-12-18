#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int indtuples; int /*<<< orphan*/  tmpCtx; int /*<<< orphan*/  count; TYPE_1__ data; int /*<<< orphan*/  blstate; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  BloomTuple ;
typedef  TYPE_2__ BloomBuildState ;

/* Variables and functions */
 int /*<<< orphan*/ * BloomFormTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ BloomPageAddItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flushCachedPage (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  initCachedPage (TYPE_2__*) ; 

__attribute__((used)) static void
bloomBuildCallback(Relation index, ItemPointer tid, Datum *values,
				   bool *isnull, bool tupleIsAlive, void *state)
{
	BloomBuildState *buildstate = (BloomBuildState *) state;
	MemoryContext oldCtx;
	BloomTuple *itup;

	oldCtx = MemoryContextSwitchTo(buildstate->tmpCtx);

	itup = BloomFormTuple(&buildstate->blstate, tid, values, isnull);

	/* Try to add next item to cached page */
	if (BloomPageAddItem(&buildstate->blstate, buildstate->data.data, itup))
	{
		/* Next item was added successfully */
		buildstate->count++;
	}
	else
	{
		/* Cached page is full, flush it out and make a new one */
		flushCachedPage(index, buildstate);

		CHECK_FOR_INTERRUPTS();

		initCachedPage(buildstate);

		if (!BloomPageAddItem(&buildstate->blstate, buildstate->data.data, itup))
		{
			/* We shouldn't be here since we're inserting to the empty page */
			elog(ERROR, "could not add new bloom tuple to empty page");
		}

		/* Next item was added successfully */
		buildstate->count++;
	}

	/* Update total tuple count */
	buildstate->indtuples += 1;

	MemoryContextSwitchTo(oldCtx);
	MemoryContextReset(buildstate->tmpCtx);
}