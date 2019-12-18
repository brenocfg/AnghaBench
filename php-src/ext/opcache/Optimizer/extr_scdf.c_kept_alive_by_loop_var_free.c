#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_5__* opcodes; } ;
typedef  TYPE_4__ zend_op_array ;
struct TYPE_14__ {scalar_t__ opcode; scalar_t__ extended_value; } ;
typedef  TYPE_5__ zend_op ;
struct TYPE_15__ {int flags; size_t* map; TYPE_7__* blocks; } ;
typedef  TYPE_6__ zend_cfg ;
typedef  int zend_bool ;
struct TYPE_16__ {size_t start; size_t len; } ;
typedef  TYPE_7__ zend_basic_block ;
typedef  size_t uint32_t ;
struct TYPE_17__ {int /*<<< orphan*/  executable_blocks; TYPE_3__* ssa; TYPE_4__* op_array; } ;
typedef  TYPE_8__ scdf_ctx ;
struct TYPE_12__ {TYPE_2__* vars; TYPE_1__* ops; TYPE_6__ cfg; } ;
struct TYPE_11__ {int definition; } ;
struct TYPE_10__ {int op1_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_FE_FREE ; 
 scalar_t__ ZEND_FREE ; 
 scalar_t__ ZEND_FREE_SWITCH ; 
 int ZEND_FUNC_FREE_LOOP_VAR ; 
 scalar_t__ zend_bitset_in (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static zend_bool kept_alive_by_loop_var_free(scdf_ctx *scdf, uint32_t block_idx) {
	uint32_t i;
	const zend_op_array *op_array = scdf->op_array;
	const zend_cfg *cfg = &scdf->ssa->cfg;
	const zend_basic_block *block = &cfg->blocks[block_idx];
	if (!(cfg->flags & ZEND_FUNC_FREE_LOOP_VAR)) {
		return 0;
	}
	for (i = block->start; i < block->start + block->len; i++) {
		zend_op *opline = &op_array->opcodes[i];
		if (opline->opcode == ZEND_FE_FREE ||
				(opline->opcode == ZEND_FREE && opline->extended_value == ZEND_FREE_SWITCH)) {
			int ssa_var = scdf->ssa->ops[i].op1_use;
			if (ssa_var >= 0) {
				int op_num = scdf->ssa->vars[ssa_var].definition;
				uint32_t def_block;
				ZEND_ASSERT(op_num >= 0);
				def_block = cfg->map[op_num];
				if (zend_bitset_in(scdf->executable_blocks, def_block)) {
					return 1;
				}
			}
		}
	}
	return 0;
}