#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  custom_relids; } ;
struct TYPE_12__ {int /*<<< orphan*/  fs_relids; } ;
struct TYPE_11__ {int /*<<< orphan*/  exclRelRTI; int /*<<< orphan*/  nominalRelation; } ;
struct TYPE_10__ {int /*<<< orphan*/ * plan; } ;
struct TYPE_9__ {int /*<<< orphan*/  scanrelid; } ;
typedef  TYPE_1__ Scan ;
typedef  TYPE_2__ PlanState ;
typedef  int /*<<< orphan*/  Plan ;
typedef  TYPE_3__ ModifyTable ;
typedef  TYPE_4__ ForeignScan ;
typedef  TYPE_5__ CustomScan ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
#define  T_BitmapHeapScan 143 
#define  T_CteScan 142 
#define  T_CustomScan 141 
#define  T_ForeignScan 140 
#define  T_FunctionScan 139 
#define  T_IndexOnlyScan 138 
#define  T_IndexScan 137 
#define  T_ModifyTable 136 
#define  T_NamedTuplestoreScan 135 
#define  T_SampleScan 134 
#define  T_SeqScan 133 
#define  T_SubqueryScan 132 
#define  T_TableFuncScan 131 
#define  T_TidScan 130 
#define  T_ValuesScan 129 
#define  T_WorkTableScan 128 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bms_add_members (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 
 int planstate_tree_walker (TYPE_2__*,int (*) (TYPE_2__*,int /*<<< orphan*/ **),int /*<<< orphan*/ **) ; 

__attribute__((used)) static bool
ExplainPreScanNode(PlanState *planstate, Bitmapset **rels_used)
{
	Plan	   *plan = planstate->plan;

	switch (nodeTag(plan))
	{
		case T_SeqScan:
		case T_SampleScan:
		case T_IndexScan:
		case T_IndexOnlyScan:
		case T_BitmapHeapScan:
		case T_TidScan:
		case T_SubqueryScan:
		case T_FunctionScan:
		case T_TableFuncScan:
		case T_ValuesScan:
		case T_CteScan:
		case T_NamedTuplestoreScan:
		case T_WorkTableScan:
			*rels_used = bms_add_member(*rels_used,
										((Scan *) plan)->scanrelid);
			break;
		case T_ForeignScan:
			*rels_used = bms_add_members(*rels_used,
										 ((ForeignScan *) plan)->fs_relids);
			break;
		case T_CustomScan:
			*rels_used = bms_add_members(*rels_used,
										 ((CustomScan *) plan)->custom_relids);
			break;
		case T_ModifyTable:
			*rels_used = bms_add_member(*rels_used,
										((ModifyTable *) plan)->nominalRelation);
			if (((ModifyTable *) plan)->exclRelRTI)
				*rels_used = bms_add_member(*rels_used,
											((ModifyTable *) plan)->exclRelRTI);
			break;
		default:
			break;
	}

	return planstate_tree_walker(planstate, ExplainPreScanNode, rels_used);
}