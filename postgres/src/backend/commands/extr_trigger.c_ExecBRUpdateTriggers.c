#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_13__ {int numtriggers; TYPE_3__* triggers; } ;
typedef  TYPE_1__ TriggerDesc ;
struct TYPE_14__ {int tg_event; TYPE_3__* tg_trigger; int /*<<< orphan*/ * tg_newslot; int /*<<< orphan*/ * tg_newtuple; int /*<<< orphan*/ * tg_trigtuple; int /*<<< orphan*/ * tg_trigslot; int /*<<< orphan*/ * tg_newtable; int /*<<< orphan*/ * tg_oldtable; int /*<<< orphan*/  tg_relation; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ TriggerData ;
struct TYPE_15__ {int /*<<< orphan*/  tgtype; } ;
typedef  TYPE_3__ Trigger ;
struct TYPE_16__ {int /*<<< orphan*/  ri_TrigInstrument; int /*<<< orphan*/  ri_TrigFunctions; int /*<<< orphan*/  ri_RelationDesc; int /*<<< orphan*/  ri_junkFilter; TYPE_1__* ri_TrigDesc; } ;
typedef  TYPE_4__ ResultRelInfo ;
typedef  int /*<<< orphan*/  LockTupleMode ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  EPQState ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * ExecCallTriggerFunc (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecCopySlot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecFetchSlotHeapTuple (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/ * ExecFilterJunk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecForceStoreHeapTuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ExecGetTriggerOldSlot (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ExecMaterializeSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecUpdateLockMode (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * GetAllUpdatedColumns (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetPerTupleMemoryContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTupleForTrigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int ItemPointerIsValid (int /*<<< orphan*/ ) ; 
 int TRIGGER_EVENT_BEFORE ; 
 int TRIGGER_EVENT_ROW ; 
 int TRIGGER_EVENT_UPDATE ; 
 int /*<<< orphan*/  TRIGGER_TYPE_BEFORE ; 
 int /*<<< orphan*/  TRIGGER_TYPE_MATCHES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_TYPE_ROW ; 
 int /*<<< orphan*/  TRIGGER_TYPE_UPDATE ; 
 int /*<<< orphan*/  T_TriggerData ; 
 int /*<<< orphan*/  TriggerEnabled (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 

bool
ExecBRUpdateTriggers(EState *estate, EPQState *epqstate,
					 ResultRelInfo *relinfo,
					 ItemPointer tupleid,
					 HeapTuple fdw_trigtuple,
					 TupleTableSlot *newslot)
{
	TriggerDesc *trigdesc = relinfo->ri_TrigDesc;
	TupleTableSlot *oldslot = ExecGetTriggerOldSlot(estate, relinfo);
	HeapTuple	newtuple = NULL;
	HeapTuple	trigtuple;
	bool		should_free_trig = false;
	bool		should_free_new = false;
	TriggerData LocTriggerData;
	int			i;
	Bitmapset  *updatedCols;
	LockTupleMode lockmode;

	/* Determine lock mode to use */
	lockmode = ExecUpdateLockMode(estate, relinfo);

	Assert(HeapTupleIsValid(fdw_trigtuple) ^ ItemPointerIsValid(tupleid));
	if (fdw_trigtuple == NULL)
	{
		TupleTableSlot *epqslot_candidate = NULL;

		/* get a copy of the on-disk tuple we are planning to update */
		if (!GetTupleForTrigger(estate, epqstate, relinfo, tupleid,
								lockmode, oldslot, &epqslot_candidate))
			return false;		/* cancel the update action */

		/*
		 * In READ COMMITTED isolation level it's possible that target tuple
		 * was changed due to concurrent update.  In that case we have a raw
		 * subplan output tuple in newSlot, and need to run it through the
		 * junk filter to produce an insertable tuple.
		 *
		 * Caution: more than likely, the passed-in slot is the same as the
		 * junkfilter's output slot, so we are clobbering the original value
		 * of slottuple by doing the filtering.  This is OK since neither we
		 * nor our caller have any more interest in the prior contents of that
		 * slot.
		 */
		if (epqslot_candidate != NULL)
		{
			TupleTableSlot *epqslot_clean;

			epqslot_clean = ExecFilterJunk(relinfo->ri_junkFilter, epqslot_candidate);

			if (newslot != epqslot_clean)
				ExecCopySlot(newslot, epqslot_clean);
		}

		trigtuple = ExecFetchSlotHeapTuple(oldslot, true, &should_free_trig);
	}
	else
	{
		ExecForceStoreHeapTuple(fdw_trigtuple, oldslot, false);
		trigtuple = fdw_trigtuple;
	}

	LocTriggerData.type = T_TriggerData;
	LocTriggerData.tg_event = TRIGGER_EVENT_UPDATE |
		TRIGGER_EVENT_ROW |
		TRIGGER_EVENT_BEFORE;
	LocTriggerData.tg_relation = relinfo->ri_RelationDesc;
	LocTriggerData.tg_oldtable = NULL;
	LocTriggerData.tg_newtable = NULL;
	updatedCols = GetAllUpdatedColumns(relinfo, estate);
	for (i = 0; i < trigdesc->numtriggers; i++)
	{
		Trigger    *trigger = &trigdesc->triggers[i];
		HeapTuple	oldtuple;

		if (!TRIGGER_TYPE_MATCHES(trigger->tgtype,
								  TRIGGER_TYPE_ROW,
								  TRIGGER_TYPE_BEFORE,
								  TRIGGER_TYPE_UPDATE))
			continue;
		if (!TriggerEnabled(estate, relinfo, trigger, LocTriggerData.tg_event,
							updatedCols, oldslot, newslot))
			continue;

		if (!newtuple)
			newtuple = ExecFetchSlotHeapTuple(newslot, true, &should_free_new);

		LocTriggerData.tg_trigslot = oldslot;
		LocTriggerData.tg_trigtuple = trigtuple;
		LocTriggerData.tg_newtuple = oldtuple = newtuple;
		LocTriggerData.tg_newslot = newslot;
		LocTriggerData.tg_trigger = trigger;
		newtuple = ExecCallTriggerFunc(&LocTriggerData,
									   i,
									   relinfo->ri_TrigFunctions,
									   relinfo->ri_TrigInstrument,
									   GetPerTupleMemoryContext(estate));

		if (newtuple == NULL)
		{
			if (should_free_trig)
				heap_freetuple(trigtuple);
			if (should_free_new)
				heap_freetuple(oldtuple);
			return false;		/* "do nothing" */
		}
		else if (newtuple != oldtuple)
		{
			ExecForceStoreHeapTuple(newtuple, newslot, false);

			/*
			 * If the tuple returned by the trigger / being stored, is the old
			 * row version, and the heap tuple passed to the trigger was
			 * allocated locally, materialize the slot. Otherwise we might
			 * free it while still referenced by the slot.
			 */
			if (should_free_trig && newtuple == trigtuple)
				ExecMaterializeSlot(newslot);

			if (should_free_new)
				heap_freetuple(oldtuple);

			/* signal tuple should be re-fetched if used */
			newtuple = NULL;
		}
	}
	if (should_free_trig)
		heap_freetuple(trigtuple);

	return true;
}