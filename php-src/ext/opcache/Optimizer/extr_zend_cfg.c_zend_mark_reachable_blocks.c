#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int last_try_catch; TYPE_3__* opcodes; TYPE_1__* try_catch_array; } ;
typedef  TYPE_2__ zend_op_array ;
struct TYPE_16__ {scalar_t__ opcode; scalar_t__ extended_value; } ;
typedef  TYPE_3__ zend_op ;
struct TYPE_17__ {int* map; int flags; int blocks_count; TYPE_5__* blocks; } ;
typedef  TYPE_4__ zend_cfg ;
struct TYPE_18__ {int flags; int start; int len; } ;
typedef  TYPE_5__ zend_basic_block ;
typedef  int uint32_t ;
struct TYPE_14__ {size_t try_op; int catch_op; int finally_op; int finally_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int ZEND_BB_CATCH ; 
 int ZEND_BB_FINALLY ; 
 int ZEND_BB_FINALLY_END ; 
 int ZEND_BB_REACHABLE ; 
 int ZEND_BB_START ; 
 int ZEND_BB_TRY ; 
 int ZEND_BB_UNREACHABLE_FREE ; 
 scalar_t__ ZEND_FE_FREE ; 
 scalar_t__ ZEND_FREE ; 
 scalar_t__ ZEND_FREE_SWITCH ; 
 int ZEND_FUNC_FREE_LOOP_VAR ; 
 int /*<<< orphan*/  zend_mark_reachable (TYPE_3__*,TYPE_4__*,TYPE_5__*) ; 
 TYPE_3__* zend_optimizer_get_loop_var_def (TYPE_2__ const*,TYPE_3__*) ; 

__attribute__((used)) static void zend_mark_reachable_blocks(const zend_op_array *op_array, zend_cfg *cfg, int start) /* {{{ */
{
	zend_basic_block *blocks = cfg->blocks;

	blocks[start].flags = ZEND_BB_START;
	zend_mark_reachable(op_array->opcodes, cfg, blocks + start);

	if (op_array->last_try_catch) {
		zend_basic_block *b;
		int j, changed;
		uint32_t *block_map = cfg->map;

		do {
			changed = 0;

			/* Add exception paths */
			for (j = 0; j < op_array->last_try_catch; j++) {

				/* check for jumps into the middle of try block */
				b = blocks + block_map[op_array->try_catch_array[j].try_op];
				if (!(b->flags & ZEND_BB_REACHABLE)) {
					zend_basic_block *end;

					if (op_array->try_catch_array[j].catch_op) {
						end = blocks + block_map[op_array->try_catch_array[j].catch_op];
						while (b != end) {
							if (b->flags & ZEND_BB_REACHABLE) {
								op_array->try_catch_array[j].try_op = b->start;
								break;
							}
							b++;
						}
					}
					b = blocks + block_map[op_array->try_catch_array[j].try_op];
					if (!(b->flags & ZEND_BB_REACHABLE)) {
						if (op_array->try_catch_array[j].finally_op) {
							end = blocks + block_map[op_array->try_catch_array[j].finally_op];
							while (b != end) {
								if (b->flags & ZEND_BB_REACHABLE) {
									op_array->try_catch_array[j].try_op = op_array->try_catch_array[j].catch_op;
									changed = 1;
									zend_mark_reachable(op_array->opcodes, cfg, blocks + block_map[op_array->try_catch_array[j].try_op]);
									break;
								}
								b++;
							}
						}
					}
				}

				b = blocks + block_map[op_array->try_catch_array[j].try_op];
				if (b->flags & ZEND_BB_REACHABLE) {
					b->flags |= ZEND_BB_TRY;
					if (op_array->try_catch_array[j].catch_op) {
						b = blocks + block_map[op_array->try_catch_array[j].catch_op];
						b->flags |= ZEND_BB_CATCH;
						if (!(b->flags & ZEND_BB_REACHABLE)) {
							changed = 1;
							zend_mark_reachable(op_array->opcodes, cfg, b);
						}
					}
					if (op_array->try_catch_array[j].finally_op) {
						b = blocks + block_map[op_array->try_catch_array[j].finally_op];
						b->flags |= ZEND_BB_FINALLY;
						if (!(b->flags & ZEND_BB_REACHABLE)) {
							changed = 1;
							zend_mark_reachable(op_array->opcodes, cfg, b);
						}
					}
					if (op_array->try_catch_array[j].finally_end) {
						b = blocks + block_map[op_array->try_catch_array[j].finally_end];
						b->flags |= ZEND_BB_FINALLY_END;
						if (!(b->flags & ZEND_BB_REACHABLE)) {
							changed = 1;
							zend_mark_reachable(op_array->opcodes, cfg, b);
						}
					}
				} else {
					if (op_array->try_catch_array[j].catch_op) {
						ZEND_ASSERT(!(blocks[block_map[op_array->try_catch_array[j].catch_op]].flags & ZEND_BB_REACHABLE));
					}
					if (op_array->try_catch_array[j].finally_op) {
						ZEND_ASSERT(!(blocks[block_map[op_array->try_catch_array[j].finally_op]].flags & ZEND_BB_REACHABLE));
					}
					if (op_array->try_catch_array[j].finally_end) {
						ZEND_ASSERT(!(blocks[block_map[op_array->try_catch_array[j].finally_end]].flags & ZEND_BB_REACHABLE));
					}
				}
			}
		} while (changed);
	}

	if (cfg->flags & ZEND_FUNC_FREE_LOOP_VAR) {
		zend_basic_block *b;
		int j;
		uint32_t *block_map = cfg->map;

		/* Mark blocks that are unreachable, but free a loop var created in a reachable block. */
		for (b = blocks; b < blocks + cfg->blocks_count; b++) {
			if (b->flags & ZEND_BB_REACHABLE) {
				continue;
			}

			for (j = b->start; j < b->start + b->len; j++) {
				zend_op *opline = &op_array->opcodes[j];
				if (opline->opcode == ZEND_FE_FREE ||
					(opline->opcode == ZEND_FREE && opline->extended_value == ZEND_FREE_SWITCH)
				) {
					zend_op *def_opline = zend_optimizer_get_loop_var_def(op_array, opline);
					if (def_opline) {
						uint32_t def_block = block_map[def_opline - op_array->opcodes];
						if (blocks[def_block].flags & ZEND_BB_REACHABLE) {
							b->flags |= ZEND_BB_UNREACHABLE_FREE;
							break;
						}
					}
				}
			}
		}
	}
}