#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* predecessors; } ;
struct TYPE_11__ {TYPE_1__ cfg; TYPE_2__* blocks; } ;
typedef  TYPE_3__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_12__ {int predecessors_count; int successors_count; size_t predecessor_offset; int /*<<< orphan*/ * successors; } ;
typedef  TYPE_4__ zend_basic_block ;
struct TYPE_10__ {int /*<<< orphan*/ * phis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  zend_ssa_remove_block (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  zend_ssa_replace_control_link (int /*<<< orphan*/ *,TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zend_ssa_unlink_block(zend_op_array *op_array, zend_ssa *ssa, zend_basic_block *block, int block_num)
{
	if (block->predecessors_count == 1 && ssa->blocks[block_num].phis == NULL) {
		int *predecessors, i;

		ZEND_ASSERT(block->successors_count == 1);
		predecessors = &ssa->cfg.predecessors[block->predecessor_offset];
		for (i = 0; i < block->predecessors_count; i++) {
			zend_ssa_replace_control_link(op_array, ssa, predecessors[i], block_num, block->successors[0]);
		}
		zend_ssa_remove_block(op_array, ssa, block_num);
	}
}