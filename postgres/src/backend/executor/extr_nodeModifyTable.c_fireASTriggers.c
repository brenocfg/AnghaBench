#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  onConflictAction; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; scalar_t__ plan; } ;
struct TYPE_7__ {int operation; int /*<<< orphan*/  mt_transition_capture; TYPE_1__ ps; int /*<<< orphan*/  mt_oc_transition_capture; } ;
typedef  int /*<<< orphan*/  ResultRelInfo ;
typedef  TYPE_2__ ModifyTableState ;
typedef  TYPE_3__ ModifyTable ;

/* Variables and functions */
#define  CMD_DELETE 130 
#define  CMD_INSERT 129 
#define  CMD_UPDATE 128 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecASDeleteTriggers (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecASInsertTriggers (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecASUpdateTriggers (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ONCONFLICT_UPDATE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * getTargetResultRelInfo (TYPE_2__*) ; 

__attribute__((used)) static void
fireASTriggers(ModifyTableState *node)
{
	ModifyTable *plan = (ModifyTable *) node->ps.plan;
	ResultRelInfo *resultRelInfo = getTargetResultRelInfo(node);

	switch (node->operation)
	{
		case CMD_INSERT:
			if (plan->onConflictAction == ONCONFLICT_UPDATE)
				ExecASUpdateTriggers(node->ps.state,
									 resultRelInfo,
									 node->mt_oc_transition_capture);
			ExecASInsertTriggers(node->ps.state, resultRelInfo,
								 node->mt_transition_capture);
			break;
		case CMD_UPDATE:
			ExecASUpdateTriggers(node->ps.state, resultRelInfo,
								 node->mt_transition_capture);
			break;
		case CMD_DELETE:
			ExecASDeleteTriggers(node->ps.state, resultRelInfo,
								 node->mt_transition_capture);
			break;
		default:
			elog(ERROR, "unknown operation");
			break;
	}
}