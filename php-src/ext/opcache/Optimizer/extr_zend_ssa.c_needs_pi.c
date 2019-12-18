#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* blocks; } ;
struct TYPE_8__ {TYPE_6__ cfg; } ;
typedef  TYPE_1__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  in; } ;
typedef  TYPE_2__ zend_dfg ;
typedef  int zend_bool ;
struct TYPE_10__ {int successors_count; int* successors; int predecessors_count; } ;
typedef  TYPE_3__ zend_basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  DFG_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  dominates_other_predecessors (TYPE_6__*,TYPE_3__*,int,int) ; 

__attribute__((used)) static zend_bool needs_pi(const zend_op_array *op_array, zend_dfg *dfg, zend_ssa *ssa, int from, int to, int var) /* {{{ */
{
	zend_basic_block *from_block, *to_block;
	int other_successor;

	if (!DFG_ISSET(dfg->in, dfg->size, to, var)) {
		/* Variable is not live, certainly won't benefit from pi */
		return 0;
	}

	/* Make sure that both sucessors of the from block aren't the same. Pi nodes are associated
	 * with predecessor blocks, so we can't distinguish which edge the pi belongs to. */
	from_block = &ssa->cfg.blocks[from];
	ZEND_ASSERT(from_block->successors_count == 2);
	if (from_block->successors[0] == from_block->successors[1]) {
		return 0;
	}

	to_block = &ssa->cfg.blocks[to];
	if (to_block->predecessors_count == 1) {
		/* Always place pi if one predecessor (an if branch) */
		return 1;
	}

	/* Check that the other successor of the from block does not dominate all other predecessors.
	 * If it does, we'd probably end up annihilating a positive+negative pi assertion. */
	other_successor = from_block->successors[0] == to
		? from_block->successors[1] : from_block->successors[0];
	return !dominates_other_predecessors(&ssa->cfg, to_block, other_successor, from);
}