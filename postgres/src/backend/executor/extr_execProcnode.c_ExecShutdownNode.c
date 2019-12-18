#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ running; } ;
struct TYPE_8__ {TYPE_5__* instrument; } ;
typedef  TYPE_1__ PlanState ;
typedef  int /*<<< orphan*/  HashState ;
typedef  int /*<<< orphan*/  HashJoinState ;
typedef  int /*<<< orphan*/  GatherState ;
typedef  int /*<<< orphan*/  GatherMergeState ;
typedef  int /*<<< orphan*/  ForeignScanState ;
typedef  int /*<<< orphan*/  CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecShutdownCustomScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecShutdownForeignScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecShutdownGather (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecShutdownGatherMerge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecShutdownHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecShutdownHashJoin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InstrStartNode (TYPE_5__*) ; 
 int /*<<< orphan*/  InstrStopNode (TYPE_5__*,int /*<<< orphan*/ ) ; 
#define  T_CustomScanState 133 
#define  T_ForeignScanState 132 
#define  T_GatherMergeState 131 
#define  T_GatherState 130 
#define  T_HashJoinState 129 
#define  T_HashState 128 
 int /*<<< orphan*/  check_stack_depth () ; 
 int nodeTag (TYPE_1__*) ; 
 int /*<<< orphan*/  planstate_tree_walker (TYPE_1__*,int (*) (TYPE_1__*),int /*<<< orphan*/ *) ; 

bool
ExecShutdownNode(PlanState *node)
{
	if (node == NULL)
		return false;

	check_stack_depth();

	planstate_tree_walker(node, ExecShutdownNode, NULL);

	/*
	 * Treat the node as running while we shut it down, but only if it's run
	 * at least once already.  We don't expect much CPU consumption during
	 * node shutdown, but in the case of Gather or Gather Merge, we may shut
	 * down workers at this stage.  If so, their buffer usage will get
	 * propagated into pgBufferUsage at this point, and we want to make sure
	 * that it gets associated with the Gather node.  We skip this if the node
	 * has never been executed, so as to avoid incorrectly making it appear
	 * that it has.
	 */
	if (node->instrument && node->instrument->running)
		InstrStartNode(node->instrument);

	switch (nodeTag(node))
	{
		case T_GatherState:
			ExecShutdownGather((GatherState *) node);
			break;
		case T_ForeignScanState:
			ExecShutdownForeignScan((ForeignScanState *) node);
			break;
		case T_CustomScanState:
			ExecShutdownCustomScan((CustomScanState *) node);
			break;
		case T_GatherMergeState:
			ExecShutdownGatherMerge((GatherMergeState *) node);
			break;
		case T_HashState:
			ExecShutdownHash((HashState *) node);
			break;
		case T_HashJoinState:
			ExecShutdownHashJoin((HashJoinState *) node);
			break;
		default:
			break;
	}

	/* Stop the node if we started it above, reporting 0 tuples. */
	if (node->instrument && node->instrument->running)
		InstrStopNode(node->instrument, 0);

	return false;
}