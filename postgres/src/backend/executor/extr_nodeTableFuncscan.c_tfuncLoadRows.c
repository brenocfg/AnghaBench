#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {int* tts_isnull; int /*<<< orphan*/ * tts_values; TYPE_5__* tts_tupleDescriptor; } ;
typedef  TYPE_4__ TupleTableSlot ;
typedef  TYPE_5__* TupleDesc ;
struct TYPE_22__ {scalar_t__ plan; } ;
struct TYPE_23__ {TYPE_4__* ss_ScanTupleSlot; TYPE_2__ ps; } ;
struct TYPE_26__ {int /*<<< orphan*/  tupstore; int /*<<< orphan*/  coldefexprs; int /*<<< orphan*/  notnulls; int /*<<< orphan*/  ordinal; TYPE_3__ ss; TYPE_8__* routine; } ;
typedef  TYPE_6__ TableFuncScanState ;
struct TYPE_27__ {TYPE_1__* tablefunc; } ;
typedef  TYPE_7__ TableFuncScan ;
struct TYPE_28__ {int /*<<< orphan*/  (* GetValue ) (TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;scalar_t__ (* FetchRow ) (TYPE_6__*) ;} ;
typedef  TYPE_8__ TableFuncRoutine ;
struct TYPE_29__ {int /*<<< orphan*/  attname; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  atttypid; } ;
struct TYPE_25__ {int natts; } ;
struct TYPE_21__ {int ordinalitycol; } ;
struct TYPE_20__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  TYPE_9__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_10__ ExprContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecClearTuple (TYPE_4__*) ; 
 int /*<<< orphan*/  ExecEvalExpr (int /*<<< orphan*/ *,TYPE_10__*,int*) ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_9__* TupleDescAttr (TYPE_5__*,int) ; 
 scalar_t__ bms_is_member (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lnext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tuplestore_putvalues (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
tfuncLoadRows(TableFuncScanState *tstate, ExprContext *econtext)
{
	const TableFuncRoutine *routine = tstate->routine;
	TupleTableSlot *slot = tstate->ss.ss_ScanTupleSlot;
	TupleDesc	tupdesc = slot->tts_tupleDescriptor;
	Datum	   *values = slot->tts_values;
	bool	   *nulls = slot->tts_isnull;
	int			natts = tupdesc->natts;
	MemoryContext oldcxt;
	int			ordinalitycol;

	ordinalitycol =
		((TableFuncScan *) (tstate->ss.ps.plan))->tablefunc->ordinalitycol;

	/*
	 * We need a short-lived memory context that we can clean up each time
	 * around the loop, to avoid wasting space. Our default per-tuple context
	 * is fine for the job, since we won't have used it for anything yet in
	 * this tuple cycle.
	 */
	oldcxt = MemoryContextSwitchTo(econtext->ecxt_per_tuple_memory);

	/*
	 * Keep requesting rows from the table builder until there aren't any.
	 */
	while (routine->FetchRow(tstate))
	{
		ListCell   *cell = list_head(tstate->coldefexprs);
		int			colno;

		CHECK_FOR_INTERRUPTS();

		ExecClearTuple(tstate->ss.ss_ScanTupleSlot);

		/*
		 * Obtain the value of each column for this row, installing them into
		 * the slot; then add the tuple to the tuplestore.
		 */
		for (colno = 0; colno < natts; colno++)
		{
			Form_pg_attribute att = TupleDescAttr(tupdesc, colno);

			if (colno == ordinalitycol)
			{
				/* Fast path for ordinality column */
				values[colno] = Int32GetDatum(tstate->ordinal++);
				nulls[colno] = false;
			}
			else
			{
				bool		isnull;

				values[colno] = routine->GetValue(tstate,
												  colno,
												  att->atttypid,
												  att->atttypmod,
												  &isnull);

				/* No value?  Evaluate and apply the default, if any */
				if (isnull && cell != NULL)
				{
					ExprState  *coldefexpr = (ExprState *) lfirst(cell);

					if (coldefexpr != NULL)
						values[colno] = ExecEvalExpr(coldefexpr, econtext,
													 &isnull);
				}

				/* Verify a possible NOT NULL constraint */
				if (isnull && bms_is_member(colno, tstate->notnulls))
					ereport(ERROR,
							(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
							 errmsg("null is not allowed in column \"%s\"",
									NameStr(att->attname))));

				nulls[colno] = isnull;
			}

			/* advance list of default expressions */
			if (cell != NULL)
				cell = lnext(tstate->coldefexprs, cell);
		}

		tuplestore_putvalues(tstate->tupstore, tupdesc, values, nulls);

		MemoryContextReset(econtext->ecxt_per_tuple_memory);
	}

	MemoryContextSwitchTo(oldcxt);
}