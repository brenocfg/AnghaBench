#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_7__ {scalar_t__ plan; } ;
struct TYPE_8__ {TYPE_1__ ps; } ;
struct TYPE_10__ {TYPE_2__ ss; } ;
struct TYPE_9__ {scalar_t__ scanrelid; } ;
typedef  TYPE_3__ Scan ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  scalar_t__ Index ;
typedef  TYPE_4__ ForeignScanState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecCopySlot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExecProcNode (int /*<<< orphan*/ *) ; 
 scalar_t__ TupIsNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * outerPlanState (TYPE_4__*) ; 

__attribute__((used)) static bool
postgresRecheckForeignScan(ForeignScanState *node, TupleTableSlot *slot)
{
	Index		scanrelid = ((Scan *) node->ss.ps.plan)->scanrelid;
	PlanState  *outerPlan = outerPlanState(node);
	TupleTableSlot *result;

	/* For base foreign relations, it suffices to set fdw_recheck_quals */
	if (scanrelid > 0)
		return true;

	Assert(outerPlan != NULL);

	/* Execute a local join execution plan */
	result = ExecProcNode(outerPlan);
	if (TupIsNull(result))
		return false;

	/* Store result in the given slot */
	ExecCopySlot(slot, result);

	return true;
}