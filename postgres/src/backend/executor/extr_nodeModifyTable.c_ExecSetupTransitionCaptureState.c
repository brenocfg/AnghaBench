#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ operation; scalar_t__ onConflictAction; } ;
struct TYPE_11__ {scalar_t__ plan; } ;
struct TYPE_14__ {scalar_t__ operation; TYPE_2__* mt_transition_capture; int /*<<< orphan*/ * mt_oc_transition_capture; TYPE_1__ ps; } ;
struct TYPE_13__ {int /*<<< orphan*/  ri_RelationDesc; int /*<<< orphan*/  ri_TrigDesc; } ;
struct TYPE_12__ {int /*<<< orphan*/  tcs_map; } ;
typedef  TYPE_3__ ResultRelInfo ;
typedef  TYPE_4__ ModifyTableState ;
typedef  TYPE_5__ ModifyTable ;
typedef  int /*<<< orphan*/  EState ;

/* Variables and functions */
 scalar_t__ CMD_INSERT ; 
 scalar_t__ CMD_UPDATE ; 
 int /*<<< orphan*/  ExecSetupChildParentMapForSubplan (TYPE_4__*) ; 
 void* MakeTransitionCaptureState (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ONCONFLICT_UPDATE ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 TYPE_3__* getTargetResultRelInfo (TYPE_4__*) ; 
 int /*<<< orphan*/  tupconv_map_for_subplan (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ExecSetupTransitionCaptureState(ModifyTableState *mtstate, EState *estate)
{
	ModifyTable *plan = (ModifyTable *) mtstate->ps.plan;
	ResultRelInfo *targetRelInfo = getTargetResultRelInfo(mtstate);

	/* Check for transition tables on the directly targeted relation. */
	mtstate->mt_transition_capture =
		MakeTransitionCaptureState(targetRelInfo->ri_TrigDesc,
								   RelationGetRelid(targetRelInfo->ri_RelationDesc),
								   mtstate->operation);
	if (plan->operation == CMD_INSERT &&
		plan->onConflictAction == ONCONFLICT_UPDATE)
		mtstate->mt_oc_transition_capture =
			MakeTransitionCaptureState(targetRelInfo->ri_TrigDesc,
									   RelationGetRelid(targetRelInfo->ri_RelationDesc),
									   CMD_UPDATE);

	/*
	 * If we found that we need to collect transition tuples then we may also
	 * need tuple conversion maps for any children that have TupleDescs that
	 * aren't compatible with the tuplestores.  (We can share these maps
	 * between the regular and ON CONFLICT cases.)
	 */
	if (mtstate->mt_transition_capture != NULL ||
		mtstate->mt_oc_transition_capture != NULL)
	{
		ExecSetupChildParentMapForSubplan(mtstate);

		/*
		 * Install the conversion map for the first plan for UPDATE and DELETE
		 * operations.  It will be advanced each time we switch to the next
		 * plan.  (INSERT operations set it every time, so we need not update
		 * mtstate->mt_oc_transition_capture here.)
		 */
		if (mtstate->mt_transition_capture && mtstate->operation != CMD_INSERT)
			mtstate->mt_transition_capture->tcs_map =
				tupconv_map_for_subplan(mtstate, 0);
	}
}