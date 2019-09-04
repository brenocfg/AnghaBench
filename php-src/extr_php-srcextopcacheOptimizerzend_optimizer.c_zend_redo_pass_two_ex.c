#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_12__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ zend_ssa ;
struct TYPE_13__ {int last_literal; int last; TYPE_4__* opcodes; int /*<<< orphan*/ * literals; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_14__ {scalar_t__ op1_type; scalar_t__ opcode; scalar_t__ result_type; scalar_t__ op2_type; int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; } ;
typedef  TYPE_4__ zend_op ;
typedef  int uint32_t ;
struct TYPE_11__ {scalar_t__ op1_def; } ;

/* Variables and functions */
 scalar_t__ IS_CONST ; 
 scalar_t__ IS_UNUSED ; 
 int MAY_BE_ANY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_REF ; 
 int MAY_BE_UNDEF ; 
 int OP1_DEF_INFO () ; 
 int OP1_INFO () ; 
 int OP2_INFO () ; 
 int RES_INFO () ; 
 int ZEND_MM_ALIGNED_SIZE_EX (int,int) ; 
 int /*<<< orphan*/  ZEND_PASS_TWO_UPDATE_CONSTANT (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_POST_DEC ; 
 scalar_t__ ZEND_POST_INC ; 
 scalar_t__ ZEND_PRE_DEC ; 
 scalar_t__ ZEND_PRE_INC ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 scalar_t__ erealloc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zend_vm_set_opcode_handler_ex (TYPE_4__*,int,int,int) ; 

__attribute__((used)) static void zend_redo_pass_two_ex(zend_op_array *op_array, zend_ssa *ssa)
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
		uint32_t op1_info = opline->op1_type == IS_UNUSED ? 0 : (OP1_INFO() & (MAY_BE_UNDEF|MAY_BE_ANY|MAY_BE_REF|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_KEY_ANY));
		uint32_t op2_info = opline->op1_type == IS_UNUSED ? 0 : (OP2_INFO() & (MAY_BE_UNDEF|MAY_BE_ANY|MAY_BE_REF|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_KEY_ANY));
		uint32_t res_info =
			(opline->opcode == ZEND_PRE_INC ||
			 opline->opcode == ZEND_PRE_DEC ||
			 opline->opcode == ZEND_POST_INC ||
			 opline->opcode == ZEND_POST_DEC) ?
				((ssa->ops[opline - op_array->opcodes].op1_def >= 0) ? (OP1_DEF_INFO() & (MAY_BE_UNDEF|MAY_BE_ANY|MAY_BE_REF|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_KEY_ANY)) : MAY_BE_ANY) :
				(opline->result_type == IS_UNUSED ? 0 : (RES_INFO() & (MAY_BE_UNDEF|MAY_BE_ANY|MAY_BE_REF|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_KEY_ANY)));

		if (opline->op1_type == IS_CONST) {
			ZEND_PASS_TWO_UPDATE_CONSTANT(op_array, opline, opline->op1);
		}
		if (opline->op2_type == IS_CONST) {
			ZEND_PASS_TWO_UPDATE_CONSTANT(op_array, opline, opline->op2);
		}

		zend_vm_set_opcode_handler_ex(opline, op1_info, op2_info, res_info);
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
		opline++;
	}
}