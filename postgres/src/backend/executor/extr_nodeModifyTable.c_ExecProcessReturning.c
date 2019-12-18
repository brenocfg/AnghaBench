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
struct TYPE_11__ {int /*<<< orphan*/  tts_tableOid; } ;
typedef  TYPE_1__ TupleTableSlot ;
struct TYPE_14__ {TYPE_1__* ecxt_scantuple; TYPE_1__* ecxt_outertuple; } ;
struct TYPE_13__ {TYPE_4__* pi_exprContext; } ;
struct TYPE_12__ {int /*<<< orphan*/  ri_RelationDesc; TYPE_3__* ri_projectReturning; } ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  TYPE_3__ ProjectionInfo ;
typedef  TYPE_4__ ExprContext ;

/* Variables and functions */
 TYPE_1__* ExecProject (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
ExecProcessReturning(ResultRelInfo *resultRelInfo,
					 TupleTableSlot *tupleSlot,
					 TupleTableSlot *planSlot)
{
	ProjectionInfo *projectReturning = resultRelInfo->ri_projectReturning;
	ExprContext *econtext = projectReturning->pi_exprContext;

	/* Make tuple and any needed join variables available to ExecProject */
	if (tupleSlot)
		econtext->ecxt_scantuple = tupleSlot;
	econtext->ecxt_outertuple = planSlot;

	/*
	 * RETURNING expressions might reference the tableoid column, so
	 * reinitialize tts_tableOid before evaluating them.
	 */
	econtext->ecxt_scantuple->tts_tableOid =
		RelationGetRelid(resultRelInfo->ri_RelationDesc);

	/* Compute the RETURNING expressions */
	return ExecProject(projectReturning);
}