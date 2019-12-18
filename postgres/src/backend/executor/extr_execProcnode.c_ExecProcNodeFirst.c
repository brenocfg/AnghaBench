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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_5__ {int /*<<< orphan*/ * (* ExecProcNode ) (TYPE_1__*) ;int /*<<< orphan*/ * (* ExecProcNodeReal ) (TYPE_1__*) ;scalar_t__ instrument; } ;
typedef  TYPE_1__ PlanState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecProcNodeInstr (TYPE_1__*) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*) ; 

__attribute__((used)) static TupleTableSlot *
ExecProcNodeFirst(PlanState *node)
{
	/*
	 * Perform stack depth check during the first execution of the node.  We
	 * only do so the first time round because it turns out to not be cheap on
	 * some common architectures (eg. x86).  This relies on the assumption
	 * that ExecProcNode calls for a given plan node will always be made at
	 * roughly the same stack depth.
	 */
	check_stack_depth();

	/*
	 * If instrumentation is required, change the wrapper to one that just
	 * does instrumentation.  Otherwise we can dispense with all wrappers and
	 * have ExecProcNode() directly call the relevant function from now on.
	 */
	if (node->instrument)
		node->ExecProcNode = ExecProcNodeInstr;
	else
		node->ExecProcNode = node->ExecProcNodeReal;

	return node->ExecProcNode(node);
}