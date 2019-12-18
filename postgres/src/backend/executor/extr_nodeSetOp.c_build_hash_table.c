#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_12__ {TYPE_1__* state; TYPE_4__* ps_ExprContext; scalar_t__ plan; } ;
struct TYPE_11__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_10__ {scalar_t__ strategy; scalar_t__ numGroups; int /*<<< orphan*/  dupCollations; int /*<<< orphan*/  dupColIdx; int /*<<< orphan*/  numCols; } ;
struct TYPE_9__ {int /*<<< orphan*/  tableContext; TYPE_7__ ps; int /*<<< orphan*/  hashfunctions; int /*<<< orphan*/  eqfuncoids; int /*<<< orphan*/  hashtable; } ;
struct TYPE_8__ {int /*<<< orphan*/  es_query_cxt; } ;
typedef  TYPE_2__ SetOpState ;
typedef  TYPE_3__ SetOp ;
typedef  TYPE_4__ ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BuildTupleHashTableExt (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExecGetResultType (int /*<<< orphan*/ ) ; 
 scalar_t__ SETOP_HASHED ; 
 int /*<<< orphan*/  outerPlanState (TYPE_2__*) ; 

__attribute__((used)) static void
build_hash_table(SetOpState *setopstate)
{
	SetOp	   *node = (SetOp *) setopstate->ps.plan;
	ExprContext *econtext = setopstate->ps.ps_ExprContext;
	TupleDesc	desc = ExecGetResultType(outerPlanState(setopstate));

	Assert(node->strategy == SETOP_HASHED);
	Assert(node->numGroups > 0);

	setopstate->hashtable = BuildTupleHashTableExt(&setopstate->ps,
												   desc,
												   node->numCols,
												   node->dupColIdx,
												   setopstate->eqfuncoids,
												   setopstate->hashfunctions,
												   node->dupCollations,
												   node->numGroups,
												   0,
												   setopstate->ps.state->es_query_cxt,
												   setopstate->tableContext,
												   econtext->ecxt_per_tuple_memory,
												   false);
}