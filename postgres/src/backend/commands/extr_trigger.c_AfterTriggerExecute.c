#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplestorestate ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_18__ {int numtriggers; TYPE_1__* triggers; } ;
typedef  TYPE_3__ TriggerDesc ;
struct TYPE_19__ {int tg_event; int /*<<< orphan*/ * tg_newslot; int /*<<< orphan*/ * tg_trigslot; int /*<<< orphan*/ * tg_newtuple; int /*<<< orphan*/ * tg_trigtuple; int /*<<< orphan*/  tg_relation; int /*<<< orphan*/  type; int /*<<< orphan*/ * tg_newtable; TYPE_1__* tg_trigger; int /*<<< orphan*/  tg_oldtable; } ;
typedef  TYPE_4__ TriggerData ;
struct TYPE_22__ {int ate_flags; int /*<<< orphan*/  ate_ctid2; int /*<<< orphan*/  ate_ctid1; } ;
struct TYPE_21__ {scalar_t__ ats_tgoid; int ats_event; TYPE_2__* ats_table; } ;
struct TYPE_20__ {int /*<<< orphan*/  ri_RelationDesc; } ;
struct TYPE_17__ {int closed; int /*<<< orphan*/ * new_tuplestore; int /*<<< orphan*/  old_tuplestore; } ;
struct TYPE_16__ {scalar_t__ tgoid; scalar_t__ tgnewtable; scalar_t__ tgoldtable; } ;
typedef  TYPE_5__ ResultRelInfo ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Instrumentation ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  EState ;
typedef  TYPE_6__* AfterTriggerShared ;
typedef  TYPE_7__* AfterTriggerEvent ;

/* Variables and functions */
 int AFTER_TRIGGER_2CTID ; 
#define  AFTER_TRIGGER_FDW_FETCH 129 
#define  AFTER_TRIGGER_FDW_REUSE 128 
 int AFTER_TRIGGER_TUP_BITS ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * ExecCallTriggerFunc (TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecFetchSlotHeapTuple (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/ * ExecGetTriggerNewSlot (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * ExecGetTriggerOldSlot (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * GetCurrentFDWTuplestore () ; 
 TYPE_6__* GetTriggerSharedData (TYPE_7__*) ; 
 int /*<<< orphan*/  InstrStartNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstrStopNode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ItemPointerIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapshotAny ; 
 int TRIGGER_EVENT_OPMASK ; 
 int TRIGGER_EVENT_ROW ; 
 int TRIGGER_EVENT_UPDATE ; 
 int /*<<< orphan*/  T_TriggerData ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_tuple_fetch_row_version (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_gettupleslot (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
AfterTriggerExecute(EState *estate,
					AfterTriggerEvent event,
					ResultRelInfo *relInfo,
					TriggerDesc *trigdesc,
					FmgrInfo *finfo, Instrumentation *instr,
					MemoryContext per_tuple_context,
					TupleTableSlot *trig_tuple_slot1,
					TupleTableSlot *trig_tuple_slot2)
{
	Relation	rel = relInfo->ri_RelationDesc;
	AfterTriggerShared evtshared = GetTriggerSharedData(event);
	Oid			tgoid = evtshared->ats_tgoid;
	TriggerData LocTriggerData;
	HeapTuple	rettuple;
	int			tgindx;
	bool		should_free_trig = false;
	bool		should_free_new = false;

	/*
	 * Locate trigger in trigdesc.
	 */
	LocTriggerData.tg_trigger = NULL;
	LocTriggerData.tg_trigslot = NULL;
	LocTriggerData.tg_newslot = NULL;

	for (tgindx = 0; tgindx < trigdesc->numtriggers; tgindx++)
	{
		if (trigdesc->triggers[tgindx].tgoid == tgoid)
		{
			LocTriggerData.tg_trigger = &(trigdesc->triggers[tgindx]);
			break;
		}
	}
	if (LocTriggerData.tg_trigger == NULL)
		elog(ERROR, "could not find trigger %u", tgoid);

	/*
	 * If doing EXPLAIN ANALYZE, start charging time to this trigger. We want
	 * to include time spent re-fetching tuples in the trigger cost.
	 */
	if (instr)
		InstrStartNode(instr + tgindx);

	/*
	 * Fetch the required tuple(s).
	 */
	switch (event->ate_flags & AFTER_TRIGGER_TUP_BITS)
	{
		case AFTER_TRIGGER_FDW_FETCH:
			{
				Tuplestorestate *fdw_tuplestore = GetCurrentFDWTuplestore();

				if (!tuplestore_gettupleslot(fdw_tuplestore, true, false,
											 trig_tuple_slot1))
					elog(ERROR, "failed to fetch tuple1 for AFTER trigger");

				if ((evtshared->ats_event & TRIGGER_EVENT_OPMASK) ==
					TRIGGER_EVENT_UPDATE &&
					!tuplestore_gettupleslot(fdw_tuplestore, true, false,
											 trig_tuple_slot2))
					elog(ERROR, "failed to fetch tuple2 for AFTER trigger");
			}
			/* fall through */
		case AFTER_TRIGGER_FDW_REUSE:

			/*
			 * Store tuple in the slot so that tg_trigtuple does not reference
			 * tuplestore memory.  (It is formally possible for the trigger
			 * function to queue trigger events that add to the same
			 * tuplestore, which can push other tuples out of memory.)  The
			 * distinction is academic, because we start with a minimal tuple
			 * that is stored as a heap tuple, constructed in different memory
			 * context, in the slot anyway.
			 */
			LocTriggerData.tg_trigslot = trig_tuple_slot1;
			LocTriggerData.tg_trigtuple =
				ExecFetchSlotHeapTuple(trig_tuple_slot1, true, &should_free_trig);

			LocTriggerData.tg_newslot = trig_tuple_slot2;
			LocTriggerData.tg_newtuple =
				((evtshared->ats_event & TRIGGER_EVENT_OPMASK) ==
				 TRIGGER_EVENT_UPDATE) ?
				ExecFetchSlotHeapTuple(trig_tuple_slot2, true, &should_free_new) : NULL;

			break;

		default:
			if (ItemPointerIsValid(&(event->ate_ctid1)))
			{
				LocTriggerData.tg_trigslot = ExecGetTriggerOldSlot(estate, relInfo);

				if (!table_tuple_fetch_row_version(rel, &(event->ate_ctid1),
												   SnapshotAny,
												   LocTriggerData.tg_trigslot))
					elog(ERROR, "failed to fetch tuple1 for AFTER trigger");
				LocTriggerData.tg_trigtuple =
					ExecFetchSlotHeapTuple(LocTriggerData.tg_trigslot, false, &should_free_trig);
			}
			else
			{
				LocTriggerData.tg_trigtuple = NULL;
			}

			/* don't touch ctid2 if not there */
			if ((event->ate_flags & AFTER_TRIGGER_TUP_BITS) ==
				AFTER_TRIGGER_2CTID &&
				ItemPointerIsValid(&(event->ate_ctid2)))
			{
				LocTriggerData.tg_newslot = ExecGetTriggerNewSlot(estate, relInfo);

				if (!table_tuple_fetch_row_version(rel, &(event->ate_ctid2),
												   SnapshotAny,
												   LocTriggerData.tg_newslot))
					elog(ERROR, "failed to fetch tuple2 for AFTER trigger");
				LocTriggerData.tg_newtuple =
					ExecFetchSlotHeapTuple(LocTriggerData.tg_newslot, false, &should_free_new);
			}
			else
			{
				LocTriggerData.tg_newtuple = NULL;
			}
	}

	/*
	 * Set up the tuplestore information to let the trigger have access to
	 * transition tables.  When we first make a transition table available to
	 * a trigger, mark it "closed" so that it cannot change anymore.  If any
	 * additional events of the same type get queued in the current trigger
	 * query level, they'll go into new transition tables.
	 */
	LocTriggerData.tg_oldtable = LocTriggerData.tg_newtable = NULL;
	if (evtshared->ats_table)
	{
		if (LocTriggerData.tg_trigger->tgoldtable)
		{
			LocTriggerData.tg_oldtable = evtshared->ats_table->old_tuplestore;
			evtshared->ats_table->closed = true;
		}

		if (LocTriggerData.tg_trigger->tgnewtable)
		{
			LocTriggerData.tg_newtable = evtshared->ats_table->new_tuplestore;
			evtshared->ats_table->closed = true;
		}
	}

	/*
	 * Setup the remaining trigger information
	 */
	LocTriggerData.type = T_TriggerData;
	LocTriggerData.tg_event =
		evtshared->ats_event & (TRIGGER_EVENT_OPMASK | TRIGGER_EVENT_ROW);
	LocTriggerData.tg_relation = rel;

	MemoryContextReset(per_tuple_context);

	/*
	 * Call the trigger and throw away any possibly returned updated tuple.
	 * (Don't let ExecCallTriggerFunc measure EXPLAIN time.)
	 */
	rettuple = ExecCallTriggerFunc(&LocTriggerData,
								   tgindx,
								   finfo,
								   NULL,
								   per_tuple_context);
	if (rettuple != NULL &&
		rettuple != LocTriggerData.tg_trigtuple &&
		rettuple != LocTriggerData.tg_newtuple)
		heap_freetuple(rettuple);

	/*
	 * Release resources
	 */
	if (should_free_trig)
		heap_freetuple(LocTriggerData.tg_trigtuple);
	if (should_free_new)
		heap_freetuple(LocTriggerData.tg_newtuple);

	if (LocTriggerData.tg_trigslot)
		ExecClearTuple(LocTriggerData.tg_trigslot);
	if (LocTriggerData.tg_newslot)
		ExecClearTuple(LocTriggerData.tg_newslot);

	/*
	 * If doing EXPLAIN ANALYZE, stop charging time to this trigger, and count
	 * one "tuple returned" (really the number of firings).
	 */
	if (instr)
		InstrStopNode(instr + tgindx, 1);
}