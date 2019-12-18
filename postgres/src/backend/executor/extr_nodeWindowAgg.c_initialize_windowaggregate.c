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
typedef  int /*<<< orphan*/  WindowStatePerFunc ;
typedef  TYPE_1__* WindowStatePerAgg ;
struct TYPE_6__ {scalar_t__ aggcontext; } ;
typedef  TYPE_2__ WindowAggState ;
struct TYPE_5__ {scalar_t__ aggcontext; int resultValueIsNull; scalar_t__ resultValue; scalar_t__ transValueCount; scalar_t__ initValueIsNull; scalar_t__ transValueIsNull; int /*<<< orphan*/  transtypeLen; int /*<<< orphan*/  transtypeByVal; int /*<<< orphan*/  initValue; int /*<<< orphan*/  transValue; } ;
typedef  scalar_t__ MemoryContext ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (scalar_t__) ; 
 scalar_t__ MemoryContextSwitchTo (scalar_t__) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
initialize_windowaggregate(WindowAggState *winstate,
						   WindowStatePerFunc perfuncstate,
						   WindowStatePerAgg peraggstate)
{
	MemoryContext oldContext;

	/*
	 * If we're using a private aggcontext, we may reset it here.  But if the
	 * context is shared, we don't know which other aggregates may still need
	 * it, so we must leave it to the caller to reset at an appropriate time.
	 */
	if (peraggstate->aggcontext != winstate->aggcontext)
		MemoryContextResetAndDeleteChildren(peraggstate->aggcontext);

	if (peraggstate->initValueIsNull)
		peraggstate->transValue = peraggstate->initValue;
	else
	{
		oldContext = MemoryContextSwitchTo(peraggstate->aggcontext);
		peraggstate->transValue = datumCopy(peraggstate->initValue,
											peraggstate->transtypeByVal,
											peraggstate->transtypeLen);
		MemoryContextSwitchTo(oldContext);
	}
	peraggstate->transValueIsNull = peraggstate->initValueIsNull;
	peraggstate->transValueCount = 0;
	peraggstate->resultValue = (Datum) 0;
	peraggstate->resultValueIsNull = true;
}