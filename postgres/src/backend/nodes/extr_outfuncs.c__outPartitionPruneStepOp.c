#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  step_id; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  PartitionPruneStepOp ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_BITMAPSET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  cmpfns ; 
 int /*<<< orphan*/  exprs ; 
 int /*<<< orphan*/  nullkeys ; 
 int /*<<< orphan*/  opstrategy ; 
 TYPE_1__ step ; 

__attribute__((used)) static void
_outPartitionPruneStepOp(StringInfo str, const PartitionPruneStepOp *node)
{
	WRITE_NODE_TYPE("PARTITIONPRUNESTEPOP");

	WRITE_INT_FIELD(step.step_id);
	WRITE_INT_FIELD(opstrategy);
	WRITE_NODE_FIELD(exprs);
	WRITE_NODE_FIELD(cmpfns);
	WRITE_BITMAPSET_FIELD(nullkeys);
}