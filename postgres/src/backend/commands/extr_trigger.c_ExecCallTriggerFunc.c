#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int tg_event; TYPE_1__* tg_trigger; int /*<<< orphan*/ * tg_newtable; int /*<<< orphan*/ * tg_oldtable; } ;
typedef  TYPE_3__ TriggerData ;
struct TYPE_18__ {TYPE_2__* flinfo; scalar_t__ isnull; } ;
struct TYPE_17__ {scalar_t__ fn_oid; } ;
struct TYPE_15__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_14__ {scalar_t__ tgfoid; } ;
typedef  int /*<<< orphan*/  PgStat_FunctionCallUsage ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Instrumentation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__ FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int AFTER_TRIGGER_DEFERRABLE ; 
 int AFTER_TRIGGER_INITDEFERRED ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_E_R_I_E_TRIGGER_PROTOCOL_VIOLATED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCallInvoke (TYPE_5__*) ; 
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_5__,TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstrStartNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstrStopNode (int /*<<< orphan*/ *,int) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LOCAL_FCINFO (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyTriggerDepth ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 scalar_t__ TRIGGER_FIRED_AFTER (int) ; 
 scalar_t__ TRIGGER_FIRED_BY_DELETE (int) ; 
 scalar_t__ TRIGGER_FIRED_BY_INSERT (int) ; 
 scalar_t__ TRIGGER_FIRED_BY_UPDATE (int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* fcinfo ; 
 int /*<<< orphan*/  fmgr_info (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  pgstat_end_function_usage (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pgstat_init_function_usage (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HeapTuple
ExecCallTriggerFunc(TriggerData *trigdata,
					int tgindx,
					FmgrInfo *finfo,
					Instrumentation *instr,
					MemoryContext per_tuple_context)
{
	LOCAL_FCINFO(fcinfo, 0);
	PgStat_FunctionCallUsage fcusage;
	Datum		result;
	MemoryContext oldContext;

	/*
	 * Protect against code paths that may fail to initialize transition table
	 * info.
	 */
	Assert(((TRIGGER_FIRED_BY_INSERT(trigdata->tg_event) ||
			 TRIGGER_FIRED_BY_UPDATE(trigdata->tg_event) ||
			 TRIGGER_FIRED_BY_DELETE(trigdata->tg_event)) &&
			TRIGGER_FIRED_AFTER(trigdata->tg_event) &&
			!(trigdata->tg_event & AFTER_TRIGGER_DEFERRABLE) &&
			!(trigdata->tg_event & AFTER_TRIGGER_INITDEFERRED)) ||
		   (trigdata->tg_oldtable == NULL && trigdata->tg_newtable == NULL));

	finfo += tgindx;

	/*
	 * We cache fmgr lookup info, to avoid making the lookup again on each
	 * call.
	 */
	if (finfo->fn_oid == InvalidOid)
		fmgr_info(trigdata->tg_trigger->tgfoid, finfo);

	Assert(finfo->fn_oid == trigdata->tg_trigger->tgfoid);

	/*
	 * If doing EXPLAIN ANALYZE, start charging time to this trigger.
	 */
	if (instr)
		InstrStartNode(instr + tgindx);

	/*
	 * Do the function evaluation in the per-tuple memory context, so that
	 * leaked memory will be reclaimed once per tuple. Note in particular that
	 * any new tuple created by the trigger function will live till the end of
	 * the tuple cycle.
	 */
	oldContext = MemoryContextSwitchTo(per_tuple_context);

	/*
	 * Call the function, passing no arguments but setting a context.
	 */
	InitFunctionCallInfoData(*fcinfo, finfo, 0,
							 InvalidOid, (Node *) trigdata, NULL);

	pgstat_init_function_usage(fcinfo, &fcusage);

	MyTriggerDepth++;
	PG_TRY();
	{
		result = FunctionCallInvoke(fcinfo);
	}
	PG_FINALLY();
	{
		MyTriggerDepth--;
	}
	PG_END_TRY();

	pgstat_end_function_usage(&fcusage, true);

	MemoryContextSwitchTo(oldContext);

	/*
	 * Trigger protocol allows function to return a null pointer, but NOT to
	 * set the isnull result flag.
	 */
	if (fcinfo->isnull)
		ereport(ERROR,
				(errcode(ERRCODE_E_R_I_E_TRIGGER_PROTOCOL_VIOLATED),
				 errmsg("trigger function %u returned null value",
						fcinfo->flinfo->fn_oid)));

	/*
	 * If doing EXPLAIN ANALYZE, stop charging time to this trigger, and count
	 * one "tuple returned" (really the number of firings).
	 */
	if (instr)
		InstrStopNode(instr + tgindx, 1);

	return (HeapTuple) DatumGetPointer(result);
}