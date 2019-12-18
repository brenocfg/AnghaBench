#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int /*<<< orphan*/  subplan; } ;
typedef  TYPE_1__ SubqueryScanState ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleTableSlot *
SubqueryNext(SubqueryScanState *node)
{
	TupleTableSlot *slot;

	/*
	 * Get the next tuple from the sub-query.
	 */
	slot = ExecProcNode(node->subplan);

	/*
	 * We just return the subplan's result slot, rather than expending extra
	 * cycles for ExecCopySlot().  (Our own ScanTupleSlot is used only for
	 * EvalPlanQual rechecks.)
	 */
	return slot;
}