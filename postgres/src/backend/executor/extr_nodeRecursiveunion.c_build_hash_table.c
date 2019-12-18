#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_10__ {TYPE_1__* state; scalar_t__ plan; } ;
struct TYPE_9__ {scalar_t__ numCols; scalar_t__ numGroups; int /*<<< orphan*/  dupCollations; int /*<<< orphan*/  dupColIdx; } ;
struct TYPE_8__ {int /*<<< orphan*/  tempContext; int /*<<< orphan*/  tableContext; TYPE_6__ ps; int /*<<< orphan*/  hashfunctions; int /*<<< orphan*/  eqfuncoids; int /*<<< orphan*/  hashtable; } ;
struct TYPE_7__ {int /*<<< orphan*/  es_query_cxt; } ;
typedef  TYPE_2__ RecursiveUnionState ;
typedef  TYPE_3__ RecursiveUnion ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BuildTupleHashTableExt (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExecGetResultType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_2__*) ; 

__attribute__((used)) static void
build_hash_table(RecursiveUnionState *rustate)
{
	RecursiveUnion *node = (RecursiveUnion *) rustate->ps.plan;
	TupleDesc	desc = ExecGetResultType(outerPlanState(rustate));

	Assert(node->numCols > 0);
	Assert(node->numGroups > 0);

	rustate->hashtable = BuildTupleHashTableExt(&rustate->ps,
												desc,
												node->numCols,
												node->dupColIdx,
												rustate->eqfuncoids,
												rustate->hashfunctions,
												node->dupCollations,
												node->numGroups,
												0,
												rustate->ps.state->es_query_cxt,
												rustate->tableContext,
												rustate->tempContext,
												false);
}