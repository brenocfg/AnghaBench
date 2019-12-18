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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_6__ {int isnull; } ;
struct TYPE_5__ {int /*<<< orphan*/  typlen; int /*<<< orphan*/  typbyval; scalar_t__ returnsTuple; } ;
typedef  TYPE_1__* SQLFunctionCachePtr ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ExecFetchSlotHeapTupleDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static Datum
postquel_get_single_result(TupleTableSlot *slot,
						   FunctionCallInfo fcinfo,
						   SQLFunctionCachePtr fcache,
						   MemoryContext resultcontext)
{
	Datum		value;
	MemoryContext oldcontext;

	/*
	 * Set up to return the function value.  For pass-by-reference datatypes,
	 * be sure to allocate the result in resultcontext, not the current memory
	 * context (which has query lifespan).  We can't leave the data in the
	 * TupleTableSlot because we intend to clear the slot before returning.
	 */
	oldcontext = MemoryContextSwitchTo(resultcontext);

	if (fcache->returnsTuple)
	{
		/* We must return the whole tuple as a Datum. */
		fcinfo->isnull = false;
		value = ExecFetchSlotHeapTupleDatum(slot);
	}
	else
	{
		/*
		 * Returning a scalar, which we have to extract from the first column
		 * of the SELECT result, and then copy into result context if needed.
		 */
		value = slot_getattr(slot, 1, &(fcinfo->isnull));

		if (!fcinfo->isnull)
			value = datumCopy(value, fcache->typbyval, fcache->typlen);
	}

	MemoryContextSwitchTo(oldcontext);

	return value;
}