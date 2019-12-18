#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_2__* ss_ScanTupleSlot; } ;
struct TYPE_20__ {int ordinal; int /*<<< orphan*/  perTableCxt; int /*<<< orphan*/ * opaque; int /*<<< orphan*/  docexpr; TYPE_3__ ss; int /*<<< orphan*/  tupstore; TYPE_5__* routine; } ;
typedef  TYPE_4__ TableFuncScanState ;
struct TYPE_21__ {int /*<<< orphan*/  (* DestroyOpaque ) (TYPE_4__*) ;int /*<<< orphan*/  (* InitOpaque ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ TableFuncRoutine ;
struct TYPE_22__ {int /*<<< orphan*/  ecxt_per_query_memory; } ;
struct TYPE_18__ {TYPE_1__* tts_tupleDescriptor; } ;
struct TYPE_17__ {int /*<<< orphan*/  natts; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_6__ ExprContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecEvalExpr (int /*<<< orphan*/ ,TYPE_6__*,int*) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 
 int /*<<< orphan*/  tfuncInitialize (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfuncLoadRows (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  tuplestore_begin_heap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_mem ; 

__attribute__((used)) static void
tfuncFetchRows(TableFuncScanState *tstate, ExprContext *econtext)
{
	const TableFuncRoutine *routine = tstate->routine;
	MemoryContext oldcxt;
	Datum		value;
	bool		isnull;

	Assert(tstate->opaque == NULL);

	/* build tuplestore for the result */
	oldcxt = MemoryContextSwitchTo(econtext->ecxt_per_query_memory);
	tstate->tupstore = tuplestore_begin_heap(false, false, work_mem);

	/*
	 * Each call to fetch a new set of rows - of which there may be very many
	 * if XMLTABLE is being used in a lateral join - will allocate a possibly
	 * substantial amount of memory, so we cannot use the per-query context
	 * here. perTableCxt now serves the same function as "argcontext" does in
	 * FunctionScan - a place to store per-one-call (i.e. one result table)
	 * lifetime data (as opposed to per-query or per-result-tuple).
	 */
	MemoryContextSwitchTo(tstate->perTableCxt);

	PG_TRY();
	{
		routine->InitOpaque(tstate,
							tstate->ss.ss_ScanTupleSlot->tts_tupleDescriptor->natts);

		/*
		 * If evaluating the document expression returns NULL, the table
		 * expression is empty and we return immediately.
		 */
		value = ExecEvalExpr(tstate->docexpr, econtext, &isnull);

		if (!isnull)
		{
			/* otherwise, pass the document value to the table builder */
			tfuncInitialize(tstate, econtext, value);

			/* initialize ordinality counter */
			tstate->ordinal = 1;

			/* Load all rows into the tuplestore, and we're done */
			tfuncLoadRows(tstate, econtext);
		}
	}
	PG_CATCH();
	{
		if (tstate->opaque != NULL)
			routine->DestroyOpaque(tstate);
		PG_RE_THROW();
	}
	PG_END_TRY();

	/* clean up and return to original memory context */

	if (tstate->opaque != NULL)
	{
		routine->DestroyOpaque(tstate);
		tstate->opaque = NULL;
	}

	MemoryContextSwitchTo(oldcxt);
	MemoryContextReset(tstate->perTableCxt);

	return;
}