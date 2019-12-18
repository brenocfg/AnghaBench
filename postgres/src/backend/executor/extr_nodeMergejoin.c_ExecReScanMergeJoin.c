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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_6__ {TYPE_5__* righttree; TYPE_5__* lefttree; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;
struct TYPE_8__ {int mj_MatchedOuter; int mj_MatchedInner; TYPE_2__ js; int /*<<< orphan*/ * mj_InnerTupleSlot; int /*<<< orphan*/ * mj_OuterTupleSlot; int /*<<< orphan*/  mj_JoinState; int /*<<< orphan*/  mj_MarkedTupleSlot; } ;
typedef  TYPE_3__ MergeJoinState ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_MJ_INITIALIZE_OUTER ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecReScan (TYPE_5__*) ; 

void
ExecReScanMergeJoin(MergeJoinState *node)
{
	ExecClearTuple(node->mj_MarkedTupleSlot);

	node->mj_JoinState = EXEC_MJ_INITIALIZE_OUTER;
	node->mj_MatchedOuter = false;
	node->mj_MatchedInner = false;
	node->mj_OuterTupleSlot = NULL;
	node->mj_InnerTupleSlot = NULL;

	/*
	 * if chgParam of subnodes is not null then plans will be re-scanned by
	 * first ExecProcNode.
	 */
	if (node->js.ps.lefttree->chgParam == NULL)
		ExecReScan(node->js.ps.lefttree);
	if (node->js.ps.righttree->chgParam == NULL)
		ExecReScan(node->js.ps.righttree);

}