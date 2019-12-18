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
struct TYPE_5__ {int /*<<< orphan*/ * chgParam; } ;
typedef  TYPE_1__ PlanState ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  HashState ;
typedef  int /*<<< orphan*/  BitmapOrState ;
typedef  int /*<<< orphan*/  BitmapIndexScanState ;
typedef  int /*<<< orphan*/  BitmapAndState ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecReScan (TYPE_1__*) ; 
 int /*<<< orphan*/ * MultiExecBitmapAnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MultiExecBitmapIndexScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MultiExecBitmapOr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MultiExecHash (int /*<<< orphan*/ *) ; 
#define  T_BitmapAndState 131 
#define  T_BitmapIndexScanState 130 
#define  T_BitmapOrState 129 
#define  T_HashState 128 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int nodeTag (TYPE_1__*) ; 

Node *
MultiExecProcNode(PlanState *node)
{
	Node	   *result;

	check_stack_depth();

	CHECK_FOR_INTERRUPTS();

	if (node->chgParam != NULL) /* something changed */
		ExecReScan(node);		/* let ReScan handle this */

	switch (nodeTag(node))
	{
			/*
			 * Only node types that actually support multiexec will be listed
			 */

		case T_HashState:
			result = MultiExecHash((HashState *) node);
			break;

		case T_BitmapIndexScanState:
			result = MultiExecBitmapIndexScan((BitmapIndexScanState *) node);
			break;

		case T_BitmapAndState:
			result = MultiExecBitmapAnd((BitmapAndState *) node);
			break;

		case T_BitmapOrState:
			result = MultiExecBitmapOr((BitmapOrState *) node);
			break;

		default:
			elog(ERROR, "unrecognized node type: %d", (int) nodeTag(node));
			result = NULL;
			break;
	}

	return result;
}