#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tableContext; scalar_t__ tempContext; int /*<<< orphan*/  intermediate_table; int /*<<< orphan*/  working_table; } ;
typedef  TYPE_1__ RecursiveUnionState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextDelete (scalar_t__) ; 
 int /*<<< orphan*/  innerPlanState (TYPE_1__*) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_1__*) ; 
 int /*<<< orphan*/  tuplestore_end (int /*<<< orphan*/ ) ; 

void
ExecEndRecursiveUnion(RecursiveUnionState *node)
{
	/* Release tuplestores */
	tuplestore_end(node->working_table);
	tuplestore_end(node->intermediate_table);

	/* free subsidiary stuff including hashtable */
	if (node->tempContext)
		MemoryContextDelete(node->tempContext);
	if (node->tableContext)
		MemoryContextDelete(node->tableContext);

	/*
	 * close down subplans
	 */
	ExecEndNode(outerPlanState(node));
	ExecEndNode(innerPlanState(node));
}