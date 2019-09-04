#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {int last_literal; int last; TYPE_2__* opcodes; int /*<<< orphan*/ * literals; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_9__ {scalar_t__ op1_type; scalar_t__ op2_type; int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; } ;
typedef  TYPE_2__ zend_op ;

/* Variables and functions */
 scalar_t__ IS_CONST ; 
 int ZEND_MM_ALIGNED_SIZE_EX (int,int) ; 
 int /*<<< orphan*/  ZEND_PASS_TWO_UPDATE_CONSTANT (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_VM_SET_OPCODE_HANDLER (TYPE_2__*) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 scalar_t__ erealloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void zend_redo_pass_two(zend_op_array *op_array)
{
	zend_op *opline, *end;
#if ZEND_USE_ABS_JMP_ADDR && !ZEND_USE_ABS_CONST_ADDR
	zend_op *old_opcodes = op_array->opcodes;
#endif

#if !ZEND_USE_ABS_CONST_ADDR
	if (op_array->last_literal) {
		op_array->opcodes = (zend_op *) erealloc(op_array->opcodes,
			ZEND_MM_ALIGNED_SIZE_EX(sizeof(zend_op) * op_array->last, 16) +
			sizeof(zval) * op_array->last_literal);
		memcpy(((char*)op_array->opcodes) + ZEND_MM_ALIGNED_SIZE_EX(sizeof(zend_op) * op_array->last, 16),
			op_array->literals, sizeof(zval) * op_array->last_literal);
		efree(op_array->literals);
		op_array->literals = (zval*)(((char*)op_array->opcodes) + ZEND_MM_ALIGNED_SIZE_EX(sizeof(zend_op) * op_array->last, 16));
	} else {
		if (op_array->literals) {
			efree(op_array->literals);
		}
		op_array->literals = NULL;
	}
#endif

	opline = op_array->opcodes;
	end = opline + op_array->last;
	while (opline < end) {
		if (opline->op1_type == IS_CONST) {
			ZEND_PASS_TWO_UPDATE_CONSTANT(op_array, opline, opline->op1);
		}
		if (opline->op2_type == IS_CONST) {
			ZEND_PASS_TWO_UPDATE_CONSTANT(op_array, opline, opline->op2);
		}
#if ZEND_USE_ABS_JMP_ADDR && !ZEND_USE_ABS_CONST_ADDR
		if (op_array->fn_flags & ZEND_ACC_DONE_PASS_TWO) {
			/* fix jumps to point to new array */
			switch (opline->opcode) {
				case ZEND_JMP:
				case ZEND_FAST_CALL:
					opline->op1.jmp_addr = &op_array->opcodes[opline->op1.jmp_addr - old_opcodes];
					break;
				case ZEND_JMPZNZ:
					/* relative extended_value don't have to be changed */
					/* break omitted intentionally */
				case ZEND_JMPZ:
				case ZEND_JMPNZ:
				case ZEND_JMPZ_EX:
				case ZEND_JMPNZ_EX:
				case ZEND_JMP_SET:
				case ZEND_COALESCE:
				case ZEND_FE_RESET_R:
				case ZEND_FE_RESET_RW:
				case ZEND_ASSERT_CHECK:
					opline->op2.jmp_addr = &op_array->opcodes[opline->op2.jmp_addr - old_opcodes];
					break;
				case ZEND_CATCH:
					if (!(opline->extended_value & ZEND_LAST_CATCH)) {
						opline->op2.jmp_addr = &op_array->opcodes[opline->op2.jmp_addr - old_opcodes];
					}
					break;
				case ZEND_DECLARE_ANON_CLASS:
				case ZEND_DECLARE_ANON_INHERITED_CLASS:
				case ZEND_FE_FETCH_R:
				case ZEND_FE_FETCH_RW:
				case ZEND_SWITCH_LONG:
				case ZEND_SWITCH_STRING:
					/* relative extended_value don't have to be changed */
					break;
			}
		}
#endif
		ZEND_VM_SET_OPCODE_HANDLER(opline);
		opline++;
	}
}