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
typedef  int /*<<< orphan*/  XLogRecPtr ;

/* Variables and functions */
 int /*<<< orphan*/  CheckPointBuffers (int) ; 
 int /*<<< orphan*/  CheckPointCLOG () ; 
 int /*<<< orphan*/  CheckPointCommitTs () ; 
 int /*<<< orphan*/  CheckPointLogicalRewriteHeap () ; 
 int /*<<< orphan*/  CheckPointMultiXact () ; 
 int /*<<< orphan*/  CheckPointPredicate () ; 
 int /*<<< orphan*/  CheckPointRelationMap () ; 
 int /*<<< orphan*/  CheckPointReplicationOrigin () ; 
 int /*<<< orphan*/  CheckPointReplicationSlots () ; 
 int /*<<< orphan*/  CheckPointSUBTRANS () ; 
 int /*<<< orphan*/  CheckPointSnapBuild () ; 
 int /*<<< orphan*/  CheckPointTwoPhase (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CheckPointGuts(XLogRecPtr checkPointRedo, int flags)
{
	CheckPointCLOG();
	CheckPointCommitTs();
	CheckPointSUBTRANS();
	CheckPointMultiXact();
	CheckPointPredicate();
	CheckPointRelationMap();
	CheckPointReplicationSlots();
	CheckPointSnapBuild();
	CheckPointLogicalRewriteHeap();
	CheckPointBuffers(flags);	/* performs all required fsyncs */
	CheckPointReplicationOrigin();
	/* We deliberately delay 2PC checkpointing as long as possible */
	CheckPointTwoPhase(checkPointRedo);
}