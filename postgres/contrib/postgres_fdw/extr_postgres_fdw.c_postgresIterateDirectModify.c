#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_17__ {int es_processed; TYPE_3__* es_result_relation_info; } ;
struct TYPE_11__ {TYPE_5__* instrument; TYPE_7__* state; } ;
struct TYPE_12__ {TYPE_1__ ps; int /*<<< orphan*/ * ss_ScanTupleSlot; } ;
struct TYPE_16__ {TYPE_2__ ss; scalar_t__ fdw_state; } ;
struct TYPE_15__ {int tuplecount; } ;
struct TYPE_14__ {int num_tuples; scalar_t__ set_processed; int /*<<< orphan*/  has_returning; } ;
struct TYPE_13__ {int /*<<< orphan*/  ri_projectReturning; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  TYPE_4__ PgFdwDirectModifyState ;
typedef  TYPE_5__ Instrumentation ;
typedef  TYPE_6__ ForeignScanState ;
typedef  TYPE_7__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  execute_dml_stmt (TYPE_6__*) ; 
 int /*<<< orphan*/ * get_returning_data (TYPE_6__*) ; 

__attribute__((used)) static TupleTableSlot *
postgresIterateDirectModify(ForeignScanState *node)
{
	PgFdwDirectModifyState *dmstate = (PgFdwDirectModifyState *) node->fdw_state;
	EState	   *estate = node->ss.ps.state;
	ResultRelInfo *resultRelInfo = estate->es_result_relation_info;

	/*
	 * If this is the first call after Begin, execute the statement.
	 */
	if (dmstate->num_tuples == -1)
		execute_dml_stmt(node);

	/*
	 * If the local query doesn't specify RETURNING, just clear tuple slot.
	 */
	if (!resultRelInfo->ri_projectReturning)
	{
		TupleTableSlot *slot = node->ss.ss_ScanTupleSlot;
		Instrumentation *instr = node->ss.ps.instrument;

		Assert(!dmstate->has_returning);

		/* Increment the command es_processed count if necessary. */
		if (dmstate->set_processed)
			estate->es_processed += dmstate->num_tuples;

		/* Increment the tuple count for EXPLAIN ANALYZE if necessary. */
		if (instr)
			instr->tuplecount += dmstate->num_tuples;

		return ExecClearTuple(slot);
	}

	/*
	 * Get the next RETURNING tuple.
	 */
	return get_returning_data(node);
}