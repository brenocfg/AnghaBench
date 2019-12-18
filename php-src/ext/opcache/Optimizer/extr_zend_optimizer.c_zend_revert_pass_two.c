#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int fn_flags; int last; int last_literal; int /*<<< orphan*/ * literals; TYPE_2__* opcodes; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_7__ {int op1_type; int op2_type; int result_type; int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; } ;
typedef  TYPE_2__ zend_op ;

/* Variables and functions */
 int IS_CONST ; 
 int IS_CV ; 
 int IS_TMP_VAR ; 
 int IS_VAR ; 
 int ZEND_ACC_DONE_PASS_TWO ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  ZEND_PASS_TWO_UNDO_CONSTANT (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * emalloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void zend_revert_pass_two(zend_op_array *op_array)
{
	zend_op *opline, *end;

	ZEND_ASSERT((op_array->fn_flags & ZEND_ACC_DONE_PASS_TWO) != 0);

	opline = op_array->opcodes;
	end = opline + op_array->last;
	while (opline < end) {
		if (opline->op1_type == IS_CONST) {
			ZEND_PASS_TWO_UNDO_CONSTANT(op_array, opline, opline->op1);
		}
		if (opline->op2_type == IS_CONST) {
			ZEND_PASS_TWO_UNDO_CONSTANT(op_array, opline, opline->op2);
		}
		/* reset smart branch flags IS_SMART_BRANCH_JMP[N]Z */
		opline->result_type &= (IS_TMP_VAR|IS_VAR|IS_CV|IS_CONST);
		opline++;
	}
#if !ZEND_USE_ABS_CONST_ADDR
	if (op_array->literals) {
		zval *literals = emalloc(sizeof(zval) * op_array->last_literal);
		memcpy(literals, op_array->literals, sizeof(zval) * op_array->last_literal);
		op_array->literals = literals;
	}
#endif

	op_array->fn_flags &= ~ZEND_ACC_DONE_PASS_TWO;
}