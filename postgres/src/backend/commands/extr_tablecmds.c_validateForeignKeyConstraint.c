#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  trig ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_8__ {int tg_event; TYPE_2__* tg_trigger; int /*<<< orphan*/ * tg_newslot; int /*<<< orphan*/ * tg_newtuple; int /*<<< orphan*/ * tg_trigslot; int /*<<< orphan*/  tg_trigtuple; int /*<<< orphan*/  tg_relation; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ TriggerData ;
struct TYPE_9__ {char* tgname; int tgisinternal; int tgdeferrable; int tginitdeferred; int /*<<< orphan*/ * context; void* tgconstraint; void* tgconstrindid; int /*<<< orphan*/  tgconstrrelid; int /*<<< orphan*/  tgenabled; int /*<<< orphan*/  tgoid; } ;
typedef  TYPE_2__ Trigger ;
typedef  int /*<<< orphan*/  TableScanDesc ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecFetchSlotHeapTuple (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GetLatestSnapshot () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RI_FKey_check_ins (TYPE_2__*) ; 
 scalar_t__ RI_Initial_Check (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int SizeForFunctionCallInfo (int /*<<< orphan*/ ) ; 
 int TRIGGER_EVENT_INSERT ; 
 int TRIGGER_EVENT_ROW ; 
 int /*<<< orphan*/  TRIGGER_FIRES_ON_ORIGIN ; 
 int /*<<< orphan*/  T_TriggerData ; 
 int /*<<< orphan*/  UnregisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 TYPE_2__* fcinfo ; 
 int /*<<< orphan*/  table_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 scalar_t__ table_scan_getnextslot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * table_slot_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
validateForeignKeyConstraint(char *conname,
							 Relation rel,
							 Relation pkrel,
							 Oid pkindOid,
							 Oid constraintOid)
{
	TupleTableSlot *slot;
	TableScanDesc scan;
	Trigger		trig;
	Snapshot	snapshot;
	MemoryContext oldcxt;
	MemoryContext perTupCxt;

	ereport(DEBUG1,
			(errmsg("validating foreign key constraint \"%s\"", conname)));

	/*
	 * Build a trigger call structure; we'll need it either way.
	 */
	MemSet(&trig, 0, sizeof(trig));
	trig.tgoid = InvalidOid;
	trig.tgname = conname;
	trig.tgenabled = TRIGGER_FIRES_ON_ORIGIN;
	trig.tgisinternal = true;
	trig.tgconstrrelid = RelationGetRelid(pkrel);
	trig.tgconstrindid = pkindOid;
	trig.tgconstraint = constraintOid;
	trig.tgdeferrable = false;
	trig.tginitdeferred = false;
	/* we needn't fill in remaining fields */

	/*
	 * See if we can do it with a single LEFT JOIN query.  A false result
	 * indicates we must proceed with the fire-the-trigger method.
	 */
	if (RI_Initial_Check(&trig, rel, pkrel))
		return;

	/*
	 * Scan through each tuple, calling RI_FKey_check_ins (insert trigger) as
	 * if that tuple had just been inserted.  If any of those fail, it should
	 * ereport(ERROR) and that's that.
	 */
	snapshot = RegisterSnapshot(GetLatestSnapshot());
	slot = table_slot_create(rel, NULL);
	scan = table_beginscan(rel, snapshot, 0, NULL);

	perTupCxt = AllocSetContextCreate(CurrentMemoryContext,
									  "validateForeignKeyConstraint",
									  ALLOCSET_SMALL_SIZES);
	oldcxt = MemoryContextSwitchTo(perTupCxt);

	while (table_scan_getnextslot(scan, ForwardScanDirection, slot))
	{
		LOCAL_FCINFO(fcinfo, 0);
		TriggerData trigdata;

		CHECK_FOR_INTERRUPTS();

		/*
		 * Make a call to the trigger function
		 *
		 * No parameters are passed, but we do set a context
		 */
		MemSet(fcinfo, 0, SizeForFunctionCallInfo(0));

		/*
		 * We assume RI_FKey_check_ins won't look at flinfo...
		 */
		trigdata.type = T_TriggerData;
		trigdata.tg_event = TRIGGER_EVENT_INSERT | TRIGGER_EVENT_ROW;
		trigdata.tg_relation = rel;
		trigdata.tg_trigtuple = ExecFetchSlotHeapTuple(slot, false, NULL);
		trigdata.tg_trigslot = slot;
		trigdata.tg_newtuple = NULL;
		trigdata.tg_newslot = NULL;
		trigdata.tg_trigger = &trig;

		fcinfo->context = (Node *) &trigdata;

		RI_FKey_check_ins(fcinfo);

		MemoryContextReset(perTupCxt);
	}

	MemoryContextSwitchTo(oldcxt);
	MemoryContextDelete(perTupCxt);
	table_endscan(scan);
	UnregisterSnapshot(snapshot);
	ExecDropSingleTupleTableSlot(slot);
}