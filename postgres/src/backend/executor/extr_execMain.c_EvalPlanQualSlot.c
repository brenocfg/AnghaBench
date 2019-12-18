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
struct TYPE_5__ {int /*<<< orphan*/  tuple_table; TYPE_1__* parentestate; int /*<<< orphan*/ ** relsubs_slot; } ;
struct TYPE_4__ {int es_range_table_size; int /*<<< orphan*/  es_query_cxt; } ;
typedef  int Relation ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int Index ;
typedef  TYPE_2__ EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table_slot_create (int,int /*<<< orphan*/ *) ; 

TupleTableSlot *
EvalPlanQualSlot(EPQState *epqstate,
				 Relation relation, Index rti)
{
	TupleTableSlot **slot;

	Assert(relation);
	Assert(rti > 0 && rti <= epqstate->parentestate->es_range_table_size);
	slot = &epqstate->relsubs_slot[rti - 1];

	if (*slot == NULL)
	{
		MemoryContext oldcontext;

		oldcontext = MemoryContextSwitchTo(epqstate->parentestate->es_query_cxt);
		*slot = table_slot_create(relation, &epqstate->tuple_table);
		MemoryContextSwitchTo(oldcontext);
	}

	return *slot;
}