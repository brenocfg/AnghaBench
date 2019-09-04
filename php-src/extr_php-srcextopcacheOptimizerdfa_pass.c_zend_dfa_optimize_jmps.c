#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_28__ ;
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_43__ {int /*<<< orphan*/ * phi_use_chain; int /*<<< orphan*/  use_chain; } ;
typedef  TYPE_2__ zend_ssa_var ;
struct TYPE_44__ {int op1_use; int op1_use_chain; size_t result_def; } ;
typedef  TYPE_3__ zend_ssa_op ;
struct TYPE_41__ {int blocks_count; int* map; TYPE_7__* blocks; } ;
struct TYPE_45__ {TYPE_1__ cfg; TYPE_2__* vars; TYPE_3__* ops; } ;
typedef  TYPE_4__ zend_ssa ;
struct TYPE_46__ {TYPE_6__* opcodes; } ;
typedef  TYPE_5__ zend_op_array ;
struct TYPE_42__ {int /*<<< orphan*/  constant; int /*<<< orphan*/  num; } ;
struct TYPE_47__ {int opcode; TYPE_28__ op2; TYPE_28__ op1; int /*<<< orphan*/  extended_value; void* op1_type; void* result_type; } ;
typedef  TYPE_6__ zend_op ;
struct TYPE_48__ {int flags; scalar_t__ len; int start; int* successors; int successors_count; } ;
typedef  TYPE_7__ zend_basic_block ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_NODE (TYPE_28__,TYPE_28__) ; 
 int /*<<< orphan*/ * CT_CONSTANT_EX (TYPE_5__*,int /*<<< orphan*/ ) ; 
 void* IS_CONST ; 
 void* IS_CV ; 
 int /*<<< orphan*/  IS_LONG ; 
 int /*<<< orphan*/  IS_NULL ; 
 int /*<<< orphan*/  IS_STRING ; 
 void* IS_UNUSED ; 
 int /*<<< orphan*/  MAKE_NOP (TYPE_6__*) ; 
 int MAY_BE_ARRAY ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_REF ; 
 int MAY_BE_RESOURCE ; 
 int MAY_BE_STRING ; 
 int MAY_BE_UNDEF ; 
 int OP1_INFO () ; 
 int /*<<< orphan*/  SET_UNUSED (TYPE_28__) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int ZEND_BB_REACHABLE ; 
 void* ZEND_CHECK_VAR ; 
#define  ZEND_COALESCE 138 
 void* ZEND_FREE ; 
#define  ZEND_JMP 137 
#define  ZEND_JMPNZ 136 
#define  ZEND_JMPNZ_EX 135 
#define  ZEND_JMPZ 134 
#define  ZEND_JMPZNZ 133 
#define  ZEND_JMPZ_EX 132 
#define  ZEND_JMP_SET 131 
#define  ZEND_NOP 130 
 TYPE_6__* ZEND_OFFSET_TO_OPLINE (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int ZEND_OFFSET_TO_OPLINE_NUM (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ZEND_OP2_JMP_ADDR (TYPE_6__*) ; 
 void* ZEND_QM_ASSIGN ; 
 int /*<<< orphan*/  ZEND_SET_OP_JMP_ADDR (TYPE_6__*,TYPE_28__,TYPE_6__*) ; 
#define  ZEND_SWITCH_LONG 129 
#define  ZEND_SWITCH_STRING 128 
 int /*<<< orphan*/ * Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compress_block (TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/  take_successor_0 (TYPE_4__*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  take_successor_1 (TYPE_4__*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  take_successor_ex (TYPE_4__*,int,TYPE_7__*,int) ; 
 int /*<<< orphan*/ * zend_hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_is_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ssa_remove_instr (TYPE_4__*,TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_ssa_remove_result_def (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_ssa_unlink_block (TYPE_5__*,TYPE_4__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  zend_ssa_unlink_use_chain (TYPE_4__*,int,int) ; 

__attribute__((used)) static int zend_dfa_optimize_jmps(zend_op_array *op_array, zend_ssa *ssa)
{
	int removed_ops = 0;
	int block_num = 0;

	for (block_num = 1; block_num < ssa->cfg.blocks_count; block_num++) {
		zend_basic_block *block = &ssa->cfg.blocks[block_num];

		if (!(block->flags & ZEND_BB_REACHABLE)) {
			continue;
		}
		compress_block(op_array, block);
		if (block->len == 0) {
			zend_ssa_unlink_block(op_array, ssa, block, block_num);
		}
	}

	block_num = 0;
	while (block_num < ssa->cfg.blocks_count
		&& !(ssa->cfg.blocks[block_num].flags & ZEND_BB_REACHABLE)) {
		block_num++;
	}
	while (block_num < ssa->cfg.blocks_count) {
		int next_block_num = block_num + 1;
		zend_basic_block *block = &ssa->cfg.blocks[block_num];
		uint32_t op_num;
		zend_op *opline;
		zend_ssa_op *ssa_op;

		while (next_block_num < ssa->cfg.blocks_count
			&& !(ssa->cfg.blocks[next_block_num].flags & ZEND_BB_REACHABLE)) {
			next_block_num++;
		}

		if (block->len) {
			op_num = block->start + block->len - 1;
			opline = op_array->opcodes + op_num;
			ssa_op = ssa->ops + op_num;

			switch (opline->opcode) {
				case ZEND_JMP:
optimize_jmp:
					if (block->successors[0] == next_block_num) {
						MAKE_NOP(opline);
						removed_ops++;
						goto optimize_nop;
					}
					break;
				case ZEND_JMPZ:
optimize_jmpz:
					if (opline->op1_type == IS_CONST) {
						if (zend_is_true(CT_CONSTANT_EX(op_array, opline->op1.constant))) {
							MAKE_NOP(opline);
							removed_ops++;
							take_successor_1(ssa, block_num, block);
							goto optimize_nop;
						} else {
							opline->opcode = ZEND_JMP;
							COPY_NODE(opline->op1, opline->op2);
							take_successor_0(ssa, block_num, block);
							goto optimize_jmp;
						}
					} else {
						if (block->successors[0] == next_block_num) {
							take_successor_0(ssa, block_num, block);
							if (opline->op1_type == IS_CV && (OP1_INFO() & MAY_BE_UNDEF)) {
								opline->opcode = ZEND_CHECK_VAR;
								opline->op2.num = 0;
							} else if (opline->op1_type == IS_CV || !(OP1_INFO() & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE|MAY_BE_REF))) {
								zend_ssa_remove_instr(ssa, opline, ssa_op);
								removed_ops++;
								goto optimize_nop;
							} else {
								opline->opcode = ZEND_FREE;
								opline->op2.num = 0;
							}
						}
					}
					break;
				case ZEND_JMPNZ:
optimize_jmpnz:
					if (opline->op1_type == IS_CONST) {
						if (zend_is_true(CT_CONSTANT_EX(op_array, opline->op1.constant))) {
							opline->opcode = ZEND_JMP;
							COPY_NODE(opline->op1, opline->op2);
							take_successor_0(ssa, block_num, block);
							goto optimize_jmp;
						} else {
							MAKE_NOP(opline);
							removed_ops++;
							take_successor_1(ssa, block_num, block);
							goto optimize_nop;
						}
					} else if (block->successors_count == 2) {
						if (block->successors[0] == next_block_num) {
							take_successor_0(ssa, block_num, block);
							if (opline->op1_type == IS_CV && (OP1_INFO() & MAY_BE_UNDEF)) {
								opline->opcode = ZEND_CHECK_VAR;
								opline->op2.num = 0;
							} else if (opline->op1_type == IS_CV || !(OP1_INFO() & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE|MAY_BE_REF))) {
								zend_ssa_remove_instr(ssa, opline, ssa_op);
								removed_ops++;
								goto optimize_nop;
							} else {
								opline->opcode = ZEND_FREE;
								opline->op2.num = 0;
							}
						}
					}
					break;
				case ZEND_JMPZNZ:
					if (opline->op1_type == IS_CONST) {
						if (zend_is_true(CT_CONSTANT_EX(op_array, opline->op1.constant))) {
							zend_op *target_opline = ZEND_OFFSET_TO_OPLINE(opline, opline->extended_value);
							ZEND_SET_OP_JMP_ADDR(opline, opline->op1, target_opline);
							take_successor_1(ssa, block_num, block);
						} else {
							zend_op *target_opline = ZEND_OP2_JMP_ADDR(opline);
							ZEND_SET_OP_JMP_ADDR(opline, opline->op1, target_opline);
							take_successor_0(ssa, block_num, block);
						}
						opline->op1_type = IS_UNUSED;
						opline->extended_value = 0;
						opline->opcode = ZEND_JMP;
						goto optimize_jmp;
					} else if (block->successors_count == 2) {
						if (block->successors[0] == block->successors[1]) {
							take_successor_0(ssa, block_num, block);
							if (block->successors[0] == next_block_num) {
								if (opline->op1_type == IS_CV && (OP1_INFO() & MAY_BE_UNDEF)) {
									opline->opcode = ZEND_CHECK_VAR;
									opline->op2.num = 0;
								} else if (opline->op1_type == IS_CV || !(OP1_INFO() & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE|MAY_BE_REF))) {
									zend_ssa_remove_instr(ssa, opline, ssa_op);
									removed_ops++;
									goto optimize_nop;
								} else {
									opline->opcode = ZEND_FREE;
									opline->op2.num = 0;
								}
							} else if ((opline->op1_type == IS_CV && !(OP1_INFO() & MAY_BE_UNDEF)) || !(OP1_INFO() & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE|MAY_BE_REF))) {
								ZEND_ASSERT(ssa_op->op1_use >= 0);
								zend_ssa_unlink_use_chain(ssa, op_num, ssa_op->op1_use);
								ssa_op->op1_use = -1;
								ssa_op->op1_use_chain = -1;
								opline->opcode = ZEND_JMP;
								opline->op1_type = IS_UNUSED;
								opline->op1.num = opline->op2.num;
								goto optimize_jmp;
							}
						}
					}
					break;
				case ZEND_JMPZ_EX:
					if (ssa->vars[ssa_op->result_def].use_chain < 0
							&& ssa->vars[ssa_op->result_def].phi_use_chain == NULL) {
						opline->opcode = ZEND_JMPZ;
						opline->result_type = IS_UNUSED;
						zend_ssa_remove_result_def(ssa, ssa_op);
						goto optimize_jmpz;
					} else if (opline->op1_type == IS_CONST) {
						if (zend_is_true(CT_CONSTANT_EX(op_array, opline->op1.constant))) {
							opline->opcode = ZEND_QM_ASSIGN;
							take_successor_1(ssa, block_num, block);
						}
					}
					break;
				case ZEND_JMPNZ_EX:
					if (ssa->vars[ssa_op->result_def].use_chain < 0
							&& ssa->vars[ssa_op->result_def].phi_use_chain == NULL) {
						opline->opcode = ZEND_JMPNZ;
						opline->result_type = IS_UNUSED;
						zend_ssa_remove_result_def(ssa, ssa_op);
						goto optimize_jmpnz;
					} else if (opline->op1_type == IS_CONST) {
						if (!zend_is_true(CT_CONSTANT_EX(op_array, opline->op1.constant))) {
							opline->opcode = ZEND_QM_ASSIGN;
							take_successor_1(ssa, block_num, block);
						}
					}
					break;
				case ZEND_JMP_SET:
					if (ssa->vars[ssa_op->result_def].use_chain < 0
							&& ssa->vars[ssa_op->result_def].phi_use_chain == NULL) {
						opline->opcode = ZEND_JMPNZ;
						opline->result_type = IS_UNUSED;
						zend_ssa_remove_result_def(ssa, ssa_op);
						goto optimize_jmpnz;
					} else if (opline->op1_type == IS_CONST) {
						if (!zend_is_true(CT_CONSTANT_EX(op_array, opline->op1.constant))) {
							MAKE_NOP(opline);
							removed_ops++;
							take_successor_1(ssa, block_num, block);
							zend_ssa_remove_result_def(ssa, ssa_op);
							goto optimize_nop;
						}
					}
					break;
				case ZEND_COALESCE:
				{
					zend_ssa_var *var = &ssa->vars[ssa_op->result_def];
					if (opline->op1_type == IS_CONST
							&& var->use_chain < 0 && var->phi_use_chain == NULL) {
						if (Z_TYPE_P(CT_CONSTANT_EX(op_array, opline->op1.constant)) == IS_NULL) {
							zend_ssa_remove_result_def(ssa, ssa_op);
							MAKE_NOP(opline);
							removed_ops++;
							take_successor_1(ssa, block_num, block);
							goto optimize_nop;
						} else {
							opline->opcode = ZEND_JMP;
							opline->result_type = IS_UNUSED;
							zend_ssa_remove_result_def(ssa, ssa_op);
							COPY_NODE(opline->op1, opline->op2);
							take_successor_0(ssa, block_num, block);
							goto optimize_jmp;
						}
					}
					break;
				}
				case ZEND_SWITCH_LONG:
					if (opline->op1_type == IS_CONST) {
						zval *zv = CT_CONSTANT_EX(op_array, opline->op1.constant);
						if (Z_TYPE_P(zv) != IS_LONG) {
							removed_ops++;
							MAKE_NOP(opline);
							opline->extended_value = 0;
							take_successor_ex(ssa, block_num, block, block->successors[0]);
							goto optimize_nop;
						} else {
							HashTable *jmptable = Z_ARRVAL_P(CT_CONSTANT_EX(op_array, opline->op2.constant));
							zval *jmp_zv = zend_hash_index_find(jmptable, Z_LVAL_P(zv));
							uint32_t target;

							if (jmp_zv) {
								target = ZEND_OFFSET_TO_OPLINE_NUM(op_array, opline, Z_LVAL_P(jmp_zv));
							} else {
								target = ZEND_OFFSET_TO_OPLINE_NUM(op_array, opline, opline->extended_value);
							}
							opline->opcode = ZEND_JMP;
							opline->extended_value = 0;
							SET_UNUSED(opline->op1);
							ZEND_SET_OP_JMP_ADDR(opline, opline->op1, op_array->opcodes + target);
							SET_UNUSED(opline->op2);
							take_successor_ex(ssa, block_num, block, ssa->cfg.map[target]);
							goto optimize_jmp;
						}
					}
					break;
				case ZEND_SWITCH_STRING:
					if (opline->op1_type == IS_CONST) {
						zval *zv = CT_CONSTANT_EX(op_array, opline->op1.constant);
						if (Z_TYPE_P(zv) != IS_STRING) {
							removed_ops++;
							MAKE_NOP(opline);
							opline->extended_value = 0;
							take_successor_ex(ssa, block_num, block, block->successors[0]);
							goto optimize_nop;
						} else {
							HashTable *jmptable = Z_ARRVAL_P(CT_CONSTANT_EX(op_array, opline->op2.constant));
							zval *jmp_zv = zend_hash_find(jmptable, Z_STR_P(zv));
							uint32_t target;

							if (jmp_zv) {
								target = ZEND_OFFSET_TO_OPLINE_NUM(op_array, opline, Z_LVAL_P(jmp_zv));
							} else {
								target = ZEND_OFFSET_TO_OPLINE_NUM(op_array, opline, opline->extended_value);
							}
							opline->opcode = ZEND_JMP;
							opline->extended_value = 0;
							SET_UNUSED(opline->op1);
							ZEND_SET_OP_JMP_ADDR(opline, opline->op1, op_array->opcodes + target);
							SET_UNUSED(opline->op2);
							take_successor_ex(ssa, block_num, block, ssa->cfg.map[target]);
							goto optimize_jmp;
						}
					}
					break;
				case ZEND_NOP:
optimize_nop:
					compress_block(op_array, block);
					if (block->len == 0) {
						if (block_num > 0) {
							zend_ssa_unlink_block(op_array, ssa, block, block_num);
							/* backtrack to previous basic block */
							do {
								block_num--;
							} while (block_num >= 0
								&& !(ssa->cfg.blocks[block_num].flags & ZEND_BB_REACHABLE));
							if (block_num >= 0) {
								continue;
							}
						}
					}
					break;
				default:
					break;
			}
		}

		block_num = next_block_num;
	}

	return removed_ops;
}