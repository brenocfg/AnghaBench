#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_2__* script; } ;
typedef  TYPE_4__ zend_optimizer_ctx ;
struct TYPE_20__ {int last; int last_try_catch; int fn_flags; TYPE_6__* opcodes; TYPE_1__* try_catch_array; } ;
typedef  TYPE_5__ zend_op_array ;
struct TYPE_18__ {int opline_num; } ;
struct TYPE_21__ {scalar_t__ opcode; TYPE_3__ result; } ;
typedef  TYPE_6__ zend_op ;
typedef  int uint32_t ;
struct TYPE_17__ {int first_early_binding_opline; TYPE_5__ main_op_array; } ;
struct TYPE_16__ {size_t try_op; size_t catch_op; int finally_op; size_t finally_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCA_FLAG (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_EARLY_BINDING ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 scalar_t__ ZEND_JMP ; 
 scalar_t__ ZEND_NOP ; 
 TYPE_6__* ZEND_OP1_JMP_ADDR (TYPE_6__*) ; 
 scalar_t__ do_alloca (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_alloca (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_heap ; 
 int /*<<< orphan*/  zend_optimizer_migrate_jump (TYPE_5__*,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  zend_optimizer_shift_jump (TYPE_5__*,TYPE_6__*,int*) ; 

void zend_optimizer_nop_removal(zend_op_array *op_array, zend_optimizer_ctx *ctx)
{
	zend_op *end, *opline;
	uint32_t new_count, i, shift;
	int j;
	uint32_t *shiftlist;
	ALLOCA_FLAG(use_heap);

	shiftlist = (uint32_t *)do_alloca(sizeof(uint32_t) * op_array->last, use_heap);
	i = new_count = shift = 0;
	end = op_array->opcodes + op_array->last;
	for (opline = op_array->opcodes; opline < end; opline++) {

		/* Kill JMP-over-NOP-s */
		if (opline->opcode == ZEND_JMP && ZEND_OP1_JMP_ADDR(opline) > op_array->opcodes + i) {
			/* check if there are only NOPs under the branch */
			zend_op *target = ZEND_OP1_JMP_ADDR(opline) - 1;

			while (target->opcode == ZEND_NOP) {
				target--;
			}
			if (target == opline) {
				/* only NOPs */
				opline->opcode = ZEND_NOP;
			}
		}

		shiftlist[i++] = shift;
		if (opline->opcode == ZEND_NOP) {
			shift++;
		} else {
			if (shift) {
				zend_op *new_opline = op_array->opcodes + new_count;

				*new_opline = *opline;
				zend_optimizer_migrate_jump(op_array, new_opline, opline);
			}
			new_count++;
		}
	}

	if (shift) {
		op_array->last = new_count;
		end = op_array->opcodes + op_array->last;

		/* update JMPs */
		for (opline = op_array->opcodes; opline<end; opline++) {
			zend_optimizer_shift_jump(op_array, opline, shiftlist);
		}

		/* update try/catch array */
		for (j = 0; j < op_array->last_try_catch; j++) {
			op_array->try_catch_array[j].try_op -= shiftlist[op_array->try_catch_array[j].try_op];
			op_array->try_catch_array[j].catch_op -= shiftlist[op_array->try_catch_array[j].catch_op];
			if (op_array->try_catch_array[j].finally_op) {
				op_array->try_catch_array[j].finally_op -= shiftlist[op_array->try_catch_array[j].finally_op];
				op_array->try_catch_array[j].finally_end -= shiftlist[op_array->try_catch_array[j].finally_end];
			}
		}

		/* update early binding list */
		if (op_array->fn_flags & ZEND_ACC_EARLY_BINDING) {
			uint32_t *opline_num = &ctx->script->first_early_binding_opline;

			ZEND_ASSERT(op_array == &ctx->script->main_op_array);
			do {
				*opline_num -= shiftlist[*opline_num];
				opline_num = &op_array->opcodes[*opline_num].result.opline_num;
			} while (*opline_num != (uint32_t)-1);
		}
	}
	free_alloca(shiftlist, use_heap);
}