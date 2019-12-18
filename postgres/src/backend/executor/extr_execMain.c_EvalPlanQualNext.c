#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_5__ {int /*<<< orphan*/  recheckplanstate; TYPE_1__* recheckestate; } ;
struct TYPE_4__ {int /*<<< orphan*/  es_query_cxt; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ EPQState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 

TupleTableSlot *
EvalPlanQualNext(EPQState *epqstate)
{
	MemoryContext oldcontext;
	TupleTableSlot *slot;

	oldcontext = MemoryContextSwitchTo(epqstate->recheckestate->es_query_cxt);
	slot = ExecProcNode(epqstate->recheckplanstate);
	MemoryContextSwitchTo(oldcontext);

	return slot;
}