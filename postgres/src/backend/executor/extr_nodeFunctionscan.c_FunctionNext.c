#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
typedef  int /*<<< orphan*/  Tuplestorestate ;
struct TYPE_16__ {int* tts_isnull; scalar_t__* tts_values; } ;
typedef  TYPE_3__ TupleTableSlot ;
struct TYPE_19__ {int /*<<< orphan*/  es_direction; } ;
struct TYPE_18__ {int rowcount; int colcount; TYPE_3__* func_slot; int /*<<< orphan*/ * tstore; int /*<<< orphan*/  tupdesc; int /*<<< orphan*/  setexpr; } ;
struct TYPE_14__ {int /*<<< orphan*/  ps_ExprContext; TYPE_6__* state; } ;
struct TYPE_15__ {TYPE_1__ ps; TYPE_3__* ss_ScanTupleSlot; } ;
struct TYPE_17__ {int eflags; int ordinal; int nfuncs; scalar_t__ ordinality; int /*<<< orphan*/  argcontext; TYPE_2__ ss; TYPE_5__* funcstates; scalar_t__ simple; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_4__ FunctionScanState ;
typedef  TYPE_5__ FunctionScanPerFuncState ;
typedef  TYPE_6__ EState ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int EXEC_FLAG_BACKWARD ; 
 int /*<<< orphan*/  ExecClearTuple (TYPE_3__*) ; 
 void* ExecMakeTableFunctionResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExecStoreVirtualTuple (TYPE_3__*) ; 
 scalar_t__ Int64GetDatumFast (int) ; 
 scalar_t__ ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 scalar_t__ TupIsNull (TYPE_3__*) ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_3__*) ; 
 int /*<<< orphan*/  tuplestore_gettupleslot (int /*<<< orphan*/ *,scalar_t__,int,TYPE_3__*) ; 
 int /*<<< orphan*/  tuplestore_rescan (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
FunctionNext(FunctionScanState *node)
{
	EState	   *estate;
	ScanDirection direction;
	TupleTableSlot *scanslot;
	bool		alldone;
	int64		oldpos;
	int			funcno;
	int			att;

	/*
	 * get information from the estate and scan state
	 */
	estate = node->ss.ps.state;
	direction = estate->es_direction;
	scanslot = node->ss.ss_ScanTupleSlot;

	if (node->simple)
	{
		/*
		 * Fast path for the trivial case: the function return type and scan
		 * result type are the same, so we fetch the function result straight
		 * into the scan result slot. No need to update ordinality or
		 * rowcounts either.
		 */
		Tuplestorestate *tstore = node->funcstates[0].tstore;

		/*
		 * If first time through, read all tuples from function and put them
		 * in a tuplestore. Subsequent calls just fetch tuples from
		 * tuplestore.
		 */
		if (tstore == NULL)
		{
			node->funcstates[0].tstore = tstore =
				ExecMakeTableFunctionResult(node->funcstates[0].setexpr,
											node->ss.ps.ps_ExprContext,
											node->argcontext,
											node->funcstates[0].tupdesc,
											node->eflags & EXEC_FLAG_BACKWARD);

			/*
			 * paranoia - cope if the function, which may have constructed the
			 * tuplestore itself, didn't leave it pointing at the start. This
			 * call is fast, so the overhead shouldn't be an issue.
			 */
			tuplestore_rescan(tstore);
		}

		/*
		 * Get the next tuple from tuplestore.
		 */
		(void) tuplestore_gettupleslot(tstore,
									   ScanDirectionIsForward(direction),
									   false,
									   scanslot);
		return scanslot;
	}

	/*
	 * Increment or decrement ordinal counter before checking for end-of-data,
	 * so that we can move off either end of the result by 1 (and no more than
	 * 1) without losing correct count.  See PortalRunSelect for why we can
	 * assume that we won't be called repeatedly in the end-of-data state.
	 */
	oldpos = node->ordinal;
	if (ScanDirectionIsForward(direction))
		node->ordinal++;
	else
		node->ordinal--;

	/*
	 * Main loop over functions.
	 *
	 * We fetch the function results into func_slots (which match the function
	 * return types), and then copy the values to scanslot (which matches the
	 * scan result type), setting the ordinal column (if any) as well.
	 */
	ExecClearTuple(scanslot);
	att = 0;
	alldone = true;
	for (funcno = 0; funcno < node->nfuncs; funcno++)
	{
		FunctionScanPerFuncState *fs = &node->funcstates[funcno];
		int			i;

		/*
		 * If first time through, read all tuples from function and put them
		 * in a tuplestore. Subsequent calls just fetch tuples from
		 * tuplestore.
		 */
		if (fs->tstore == NULL)
		{
			fs->tstore =
				ExecMakeTableFunctionResult(fs->setexpr,
											node->ss.ps.ps_ExprContext,
											node->argcontext,
											fs->tupdesc,
											node->eflags & EXEC_FLAG_BACKWARD);

			/*
			 * paranoia - cope if the function, which may have constructed the
			 * tuplestore itself, didn't leave it pointing at the start. This
			 * call is fast, so the overhead shouldn't be an issue.
			 */
			tuplestore_rescan(fs->tstore);
		}

		/*
		 * Get the next tuple from tuplestore.
		 *
		 * If we have a rowcount for the function, and we know the previous
		 * read position was out of bounds, don't try the read. This allows
		 * backward scan to work when there are mixed row counts present.
		 */
		if (fs->rowcount != -1 && fs->rowcount < oldpos)
			ExecClearTuple(fs->func_slot);
		else
			(void) tuplestore_gettupleslot(fs->tstore,
										   ScanDirectionIsForward(direction),
										   false,
										   fs->func_slot);

		if (TupIsNull(fs->func_slot))
		{
			/*
			 * If we ran out of data for this function in the forward
			 * direction then we now know how many rows it returned. We need
			 * to know this in order to handle backwards scans. The row count
			 * we store is actually 1+ the actual number, because we have to
			 * position the tuplestore 1 off its end sometimes.
			 */
			if (ScanDirectionIsForward(direction) && fs->rowcount == -1)
				fs->rowcount = node->ordinal;

			/*
			 * populate the result cols with nulls
			 */
			for (i = 0; i < fs->colcount; i++)
			{
				scanslot->tts_values[att] = (Datum) 0;
				scanslot->tts_isnull[att] = true;
				att++;
			}
		}
		else
		{
			/*
			 * we have a result, so just copy it to the result cols.
			 */
			slot_getallattrs(fs->func_slot);

			for (i = 0; i < fs->colcount; i++)
			{
				scanslot->tts_values[att] = fs->func_slot->tts_values[i];
				scanslot->tts_isnull[att] = fs->func_slot->tts_isnull[i];
				att++;
			}

			/*
			 * We're not done until every function result is exhausted; we pad
			 * the shorter results with nulls until then.
			 */
			alldone = false;
		}
	}

	/*
	 * ordinal col is always last, per spec.
	 */
	if (node->ordinality)
	{
		scanslot->tts_values[att] = Int64GetDatumFast(node->ordinal);
		scanslot->tts_isnull[att] = false;
	}

	/*
	 * If alldone, we just return the previously-cleared scanslot.  Otherwise,
	 * finish creating the virtual tuple.
	 */
	if (!alldone)
		ExecStoreVirtualTuple(scanslot);

	return scanslot;
}