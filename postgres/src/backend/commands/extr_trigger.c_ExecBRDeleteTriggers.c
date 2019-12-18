#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_11__ {int numtriggers; TYPE_3__* triggers; } ;
typedef  TYPE_1__ TriggerDesc ;
struct TYPE_12__ {int tg_event; TYPE_3__* tg_trigger; int /*<<< orphan*/ * tg_trigtuple; int /*<<< orphan*/ * tg_trigslot; int /*<<< orphan*/ * tg_newtable; int /*<<< orphan*/ * tg_oldtable; int /*<<< orphan*/ * tg_newslot; int /*<<< orphan*/ * tg_newtuple; int /*<<< orphan*/  tg_relation; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ TriggerData ;
struct TYPE_13__ {int /*<<< orphan*/  tgtype; } ;
typedef  TYPE_3__ Trigger ;
struct TYPE_14__ {int /*<<< orphan*/  ri_TrigInstrument; int /*<<< orphan*/  ri_TrigFunctions; int /*<<< orphan*/  ri_RelationDesc; TYPE_1__* ri_TrigDesc; } ;
typedef  TYPE_4__ ResultRelInfo ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  EPQState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * ExecCallTriggerFunc (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExecFetchSlotHeapTuple (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ExecForceStoreHeapTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ExecGetTriggerOldSlot (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  GetPerTupleMemoryContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTupleForTrigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int ItemPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockTupleExclusive ; 
 int TRIGGER_EVENT_BEFORE ; 
 int TRIGGER_EVENT_DELETE ; 
 int TRIGGER_EVENT_ROW ; 
 int /*<<< orphan*/  TRIGGER_TYPE_BEFORE ; 
 int /*<<< orphan*/  TRIGGER_TYPE_DELETE ; 
 int /*<<< orphan*/  TRIGGER_TYPE_MATCHES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_TYPE_ROW ; 
 int /*<<< orphan*/  T_TriggerData ; 
 int /*<<< orphan*/  TriggerEnabled (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 

bool
ExecBRDeleteTriggers(EState *estate, EPQState *epqstate,
					 ResultRelInfo *relinfo,
					 ItemPointer tupleid,
					 HeapTuple fdw_trigtuple,
					 TupleTableSlot **epqslot)
{
	TupleTableSlot *slot = ExecGetTriggerOldSlot(estate, relinfo);
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;
	bool		result = true;
	TriggerData LocTriggerData;
	HeapTuple	trigtuple;
	bool		should_free = false;
	int			i;

	Assert(HeapTupleIsValid(fdw_trigtuple) ^ ItemPointerIsValid(tupleid));
	if (fdw_trigtuple == NULL)
	{
		TupleTableSlot *epqslot_candidate = NULL;

		if (!GetTupleForTrigger(estate, epqstate, relinfo, tupleid,
								LockTupleExclusive, slot, &epqslot_candidate))
			return false;

		/*
		 * If the tuple was concurrently updated and the caller of this
		 * function requested for the updated tuple, skip the trigger
		 * execution.
		 */
		if (epqslot_candidate != NULL && epqslot != NULL)
		{
			*epqslot = epqslot_candidate;
			return false;
		}

		trigtuple = ExecFetchSlotHeapTuple(slot, true, &should_free);

	}
	else
	{
		trigtuple = fdw_trigtuple;
		ExecForceStoreHeapTuple(trigtuple, slot, false);
	}

	LocTriggerData.type = T_TriggerData;
	LocTriggerData.tg_event = TRIGGER_EVENT_DELETE |
		TRIGGER_EVENT_ROW |
		TRIGGER_EVENT_BEFORE;
	LocTriggerData.tg_relation = relinfo->ri_RelationDesc;
	LocTriggerData.tg_trigtuple = NULL;
	LocTriggerData.tg_newtuple = NULL;
	LocTriggerData.tg_trigslot = NULL;
	LocTriggerData.tg_newslot = NULL;
	LocTriggerData.tg_oldtable = NULL;
	LocTriggerData.tg_newtable = NULL;
	for (i = 0; i < trigdesc->numtriggers; i++)
	{
		HeapTuple	newtuple;
		Trigger    *trigger = &trigdesc->triggers[i];

		if (!TRIGGER_TYPE_MATCHES(trigger->tgtype,
								  TRIGGER_TYPE_ROW,
								  TRIGGER_TYPE_BEFORE,
								  TRIGGER_TYPE_DELETE))
			continue;
		if (!TriggerEnabled(estate, relinfo, trigger, LocTriggerData.tg_event,
							NULL, slot, NULL))
			continue;

		LocTriggerData.tg_trigslot = slot;
		LocTriggerData.tg_trigtuple = trigtuple;
		LocTriggerData.tg_trigger = trigger;
		newtuple = ExecCallTriggerFunc(&LocTriggerData,
									   i,
									   relinfo->ri_TrigFunctions,
									   relinfo->ri_TrigInstrument,
									   GetPerTupleMemoryContext(estate));
		if (newtuple == NULL)
		{
			result = false;		/* tell caller to suppress delete */
			break;
		}
		if (newtuple != trigtuple)
			heap_freetuple(newtuple);
	}
	if (should_free)
		heap_freetuple(trigtuple);

	return result;
}