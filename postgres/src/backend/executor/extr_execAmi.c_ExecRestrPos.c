#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SortState ;
typedef  int /*<<< orphan*/  ResultState ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  int /*<<< orphan*/  MaterialState ;
typedef  int /*<<< orphan*/  IndexScanState ;
typedef  int /*<<< orphan*/  IndexOnlyScanState ;
typedef  int /*<<< orphan*/  CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecCustomRestrPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecIndexOnlyRestrPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecIndexRestrPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecMaterialRestrPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecResultRestrPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecSortRestrPos (int /*<<< orphan*/ *) ; 
#define  T_CustomScanState 133 
#define  T_IndexOnlyScanState 132 
#define  T_IndexScanState 131 
#define  T_MaterialState 130 
#define  T_ResultState 129 
#define  T_SortState 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

void
ExecRestrPos(PlanState *node)
{
	switch (nodeTag(node))
	{
		case T_IndexScanState:
			ExecIndexRestrPos((IndexScanState *) node);
			break;

		case T_IndexOnlyScanState:
			ExecIndexOnlyRestrPos((IndexOnlyScanState *) node);
			break;

		case T_CustomScanState:
			ExecCustomRestrPos((CustomScanState *) node);
			break;

		case T_MaterialState:
			ExecMaterialRestrPos((MaterialState *) node);
			break;

		case T_SortState:
			ExecSortRestrPos((SortState *) node);
			break;

		case T_ResultState:
			ExecResultRestrPos((ResultState *) node);
			break;

		default:
			elog(ERROR, "unrecognized node type: %d", (int) nodeTag(node));
			break;
	}
}