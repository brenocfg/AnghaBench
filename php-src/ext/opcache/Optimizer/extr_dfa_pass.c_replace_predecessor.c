#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* sources; struct TYPE_9__* next; } ;
typedef  TYPE_3__ zend_ssa_phi ;
struct TYPE_7__ {int* predecessors; TYPE_5__* blocks; } ;
struct TYPE_10__ {TYPE_2__* blocks; TYPE_1__ cfg; } ;
typedef  TYPE_4__ zend_ssa ;
struct TYPE_11__ {size_t predecessor_offset; int predecessors_count; } ;
typedef  TYPE_5__ zend_basic_block ;
struct TYPE_8__ {TYPE_3__* phis; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 

__attribute__((used)) static void replace_predecessor(zend_ssa *ssa, int block_id, int old_pred, int new_pred) {
	zend_basic_block *block = &ssa->cfg.blocks[block_id];
	int *predecessors = &ssa->cfg.predecessors[block->predecessor_offset];
	zend_ssa_phi *phi;

	int i;
	int old_pred_idx = -1;
	int new_pred_idx = -1;
	for (i = 0; i < block->predecessors_count; i++) {
		if (predecessors[i] == old_pred) {
			old_pred_idx = i;
		}
		if (predecessors[i] == new_pred) {
			new_pred_idx = i;
		}
	}

	ZEND_ASSERT(old_pred_idx != -1);
	if (new_pred_idx == -1) {
		/* If the new predecessor doesn't exist yet, simply rewire the old one */
		predecessors[old_pred_idx] = new_pred;
	} else {
		/* Otherwise, rewiring the old predecessor would make the new predecessor appear
		 * twice, which violates our CFG invariants. Remove the old predecessor instead. */
		memmove(
			predecessors + old_pred_idx,
			predecessors + old_pred_idx + 1,
			sizeof(int) * (block->predecessors_count - old_pred_idx - 1)
		);

		/* Also remove the corresponding phi node entries */
		for (phi = ssa->blocks[block_id].phis; phi; phi = phi->next) {
			memmove(
				phi->sources + old_pred_idx,
				phi->sources + old_pred_idx + 1,
				sizeof(int) * (block->predecessors_count - old_pred_idx - 1)
			);
		}

		block->predecessors_count--;
	}
}