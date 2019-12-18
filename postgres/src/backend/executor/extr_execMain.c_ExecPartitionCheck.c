#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_8__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ri_PartitionCheckExpr; int /*<<< orphan*/ * ri_PartitionCheck; } ;
typedef  TYPE_1__ ResultRelInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ ExprContext ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 int ExecCheck (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ExecPartitionCheckEmitError (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecPrepareCheck (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* GetPerTupleExprContext (int /*<<< orphan*/ *) ; 

bool
ExecPartitionCheck(ResultRelInfo *resultRelInfo, TupleTableSlot *slot,
				   EState *estate, bool emitError)
{
	ExprContext *econtext;
	bool		success;

	/*
	 * If first time through, build expression state tree for the partition
	 * check expression.  Keep it in the per-query memory context so they'll
	 * survive throughout the query.
	 */
	if (resultRelInfo->ri_PartitionCheckExpr == NULL)
	{
		List	   *qual = resultRelInfo->ri_PartitionCheck;

		resultRelInfo->ri_PartitionCheckExpr = ExecPrepareCheck(qual, estate);
	}

	/*
	 * We will use the EState's per-tuple context for evaluating constraint
	 * expressions (creating it if it's not already there).
	 */
	econtext = GetPerTupleExprContext(estate);

	/* Arrange for econtext's scan tuple to be the tuple under test */
	econtext->ecxt_scantuple = slot;

	/*
	 * As in case of the catalogued constraints, we treat a NULL result as
	 * success here, not a failure.
	 */
	success = ExecCheck(resultRelInfo->ri_PartitionCheckExpr, econtext);

	/* if asked to emit error, don't actually return on failure */
	if (!success && emitError)
		ExecPartitionCheckEmitError(resultRelInfo, slot, estate);

	return success;
}