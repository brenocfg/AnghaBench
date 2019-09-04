#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_18__ {int /*<<< orphan*/  constant; } ;
struct TYPE_16__ {size_t extended_value; scalar_t__ opcode; scalar_t__ op1_type; TYPE_9__ op2; TYPE_9__ op1; } ;
typedef  TYPE_3__ zend_op ;
struct TYPE_15__ {int fn_flags; size_t required_num_args; size_t num_args; TYPE_3__* opcodes; TYPE_1__* arg_info; } ;
struct TYPE_17__ {scalar_t__ type; TYPE_2__ op_array; } ;
typedef  TYPE_4__ zend_function ;
typedef  size_t uint32_t ;
struct TYPE_14__ {scalar_t__ pass_by_reference; } ;

/* Variables and functions */
 scalar_t__ IS_CONST ; 
 scalar_t__ IS_CONSTANT_AST ; 
 scalar_t__ IS_UNUSED ; 
 int /*<<< orphan*/  MAKE_NOP (TYPE_3__*) ; 
 scalar_t__ RETURN_VALUE_USED (TYPE_3__*) ; 
 int /*<<< orphan*/  RT_CONSTANT (TYPE_3__*,TYPE_9__) ; 
 int /*<<< orphan*/  SET_UNUSED (TYPE_9__) ; 
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_HAS_TYPE_HINTS ; 
 int ZEND_ACC_TRAIT_CLONE ; 
 int ZEND_ACC_VARIADIC ; 
 scalar_t__ ZEND_INIT_METHOD_CALL ; 
 scalar_t__ ZEND_QM_ASSIGN ; 
 scalar_t__ ZEND_RETURN ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_delete_call_instructions (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_optimizer_add_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_try_inline_call(zend_op_array *op_array, zend_op *fcall, zend_op *opline, zend_function *func)
{
	if (func->type == ZEND_USER_FUNCTION
	 && !(func->op_array.fn_flags & (ZEND_ACC_ABSTRACT|ZEND_ACC_HAS_TYPE_HINTS))
		/* TODO: function copied from trait may be inconsistent ??? */
	 && !(func->op_array.fn_flags & (ZEND_ACC_TRAIT_CLONE))
	 && fcall->extended_value >= func->op_array.required_num_args
	 && func->op_array.opcodes[func->op_array.num_args].opcode == ZEND_RETURN) {

		zend_op *ret_opline = func->op_array.opcodes + func->op_array.num_args;

		if (ret_opline->op1_type == IS_CONST) {
			uint32_t i, num_args = func->op_array.num_args;
			num_args += (func->op_array.fn_flags & ZEND_ACC_VARIADIC) != 0;

			if (fcall->opcode == ZEND_INIT_METHOD_CALL && fcall->op1_type == IS_UNUSED) {
				/* TODO: we can't inlne methods, because $this may be used
				 *       not in object context ???
				 */
				return;
			}

			for (i = 0; i < num_args; i++) {
				/* Don't inline functions with by-reference arguments. This would require
				 * correct handling of INDIRECT arguments. */
				if (func->op_array.arg_info[i].pass_by_reference) {
					return;
				}
			}

			if (fcall->extended_value < func->op_array.num_args) {
				/* don't inline functions with named constants in default arguments */
				i = fcall->extended_value;

				do {
					if (Z_TYPE_P(RT_CONSTANT(&func->op_array.opcodes[i], func->op_array.opcodes[i].op2)) == IS_CONSTANT_AST) {
						return;
					}
					i++;
				} while (i < func->op_array.num_args);
			}

			if (RETURN_VALUE_USED(opline)) {
				zval zv;

				ZVAL_COPY(&zv, RT_CONSTANT(ret_opline, ret_opline->op1));
				opline->opcode = ZEND_QM_ASSIGN;
				opline->op1_type = IS_CONST;
				opline->op1.constant = zend_optimizer_add_literal(op_array, &zv);
				SET_UNUSED(opline->op2);
			} else {
				MAKE_NOP(opline);
			}

			zend_delete_call_instructions(opline-1);
		}
	}
}