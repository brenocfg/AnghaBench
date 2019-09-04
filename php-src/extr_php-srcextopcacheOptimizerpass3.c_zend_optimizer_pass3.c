#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/  var; } ;
typedef  TYPE_1__ znode_op ;
typedef  int zend_uchar ;
struct TYPE_29__ {int optimization_level; } ;
typedef  TYPE_2__ zend_optimizer_ctx ;
struct TYPE_30__ {int last; int fn_flags; TYPE_4__* opcodes; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_31__ {int opcode; int op2_type; int op1_type; int result_type; TYPE_1__ result; TYPE_1__ op1; int /*<<< orphan*/  extended_value; TYPE_1__ op2; } ;
typedef  TYPE_4__ zend_op ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCA_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_JMP (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_JMP2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_NODE (TYPE_1__,TYPE_1__) ; 
 int INV_COND (int) ; 
 int INV_COND_EX (int) ; 
 int const INV_EX_COND (int const) ; 
 int const INV_EX_COND_EX (int const) ; 
 int /*<<< orphan*/  IS_ARRAY ; 
 int IS_CONST ; 
 int IS_CV ; 
 int IS_UNUSED ; 
 int IS_VAR ; 
 int /*<<< orphan*/  MAKE_NOP (TYPE_4__*) ; 
 int /*<<< orphan*/  SAME_VAR (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SET_UNUSED (TYPE_1__) ; 
 int ZEND_ACC_HAS_FINALLY_BLOCK ; 
#define  ZEND_ADD 151 
 int ZEND_ASSIGN ; 
 int ZEND_ASSIGN_ADD ; 
 int ZEND_ASSIGN_BW_AND ; 
 int ZEND_ASSIGN_BW_OR ; 
 int ZEND_ASSIGN_BW_XOR ; 
 int ZEND_ASSIGN_CONCAT ; 
 int ZEND_ASSIGN_DIV ; 
 int ZEND_ASSIGN_MOD ; 
 int ZEND_ASSIGN_MUL ; 
 int ZEND_ASSIGN_POW ; 
 int ZEND_ASSIGN_SL ; 
 int ZEND_ASSIGN_SR ; 
 int ZEND_ASSIGN_SUB ; 
 int ZEND_BOOL ; 
#define  ZEND_BW_AND 150 
#define  ZEND_BW_OR 149 
#define  ZEND_BW_XOR 148 
#define  ZEND_COALESCE 147 
#define  ZEND_CONCAT 146 
#define  ZEND_DIV 145 
 int const ZEND_FREE ; 
#define  ZEND_JMP 144 
#define  ZEND_JMPNZ 143 
#define  ZEND_JMPNZ_EX 142 
#define  ZEND_JMPZ 141 
#define  ZEND_JMPZNZ 140 
#define  ZEND_JMPZ_EX 139 
#define  ZEND_JMP_SET 138 
#define  ZEND_MOD 137 
#define  ZEND_MUL 136 
 int ZEND_NOP ; 
 TYPE_4__* ZEND_OFFSET_TO_OPLINE (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ZEND_OP1_JMP_ADDR (TYPE_4__*) ; 
 int /*<<< orphan*/  ZEND_OP1_LITERAL (TYPE_4__*) ; 
 TYPE_4__* ZEND_OP2_JMP_ADDR (TYPE_4__*) ; 
 int /*<<< orphan*/  ZEND_OPLINE_TO_OFFSET (TYPE_4__*,TYPE_4__*) ; 
 int ZEND_OPTIMIZER_IGNORE_OVERLOADING ; 
#define  ZEND_POST_DEC 135 
#define  ZEND_POST_DEC_OBJ 134 
#define  ZEND_POST_INC 133 
#define  ZEND_POST_INC_OBJ 132 
#define  ZEND_POW 131 
 int /*<<< orphan*/  ZEND_SET_OP_JMP_ADDR (TYPE_4__*,TYPE_1__,TYPE_4__*) ; 
#define  ZEND_SL 130 
#define  ZEND_SR 129 
#define  ZEND_SUB 128 
 int /*<<< orphan*/  Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  continue_jmp_ex_optimization ; 
 int /*<<< orphan*/  continue_jmpznz_optimization ; 
 scalar_t__ do_alloca (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done_jmp_optimization ; 
 int /*<<< orphan*/  free_alloca (TYPE_4__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_heap ; 

void zend_optimizer_pass3(zend_op_array *op_array, zend_optimizer_ctx *ctx)
{
	zend_op *opline;
	zend_op *end = op_array->opcodes + op_array->last;
	zend_op **jmp_hitlist;
	int jmp_hitlist_count;
	int i;
	uint32_t opline_num = 0;
	ALLOCA_FLAG(use_heap);

	jmp_hitlist = (zend_op**)do_alloca(sizeof(zend_op*)*op_array->last, use_heap);
	opline = op_array->opcodes;

	while (opline < end) {
		jmp_hitlist_count = 0;

		switch (opline->opcode) {
			case ZEND_ADD:
			case ZEND_SUB:
			case ZEND_MUL:
			case ZEND_DIV:
			case ZEND_MOD:
			case ZEND_POW:
			case ZEND_CONCAT:
			case ZEND_SL:
			case ZEND_SR:
			case ZEND_BW_OR:
			case ZEND_BW_AND:
			case ZEND_BW_XOR:
				{
					zend_op *next_opline = opline + 1;

					while (next_opline < end && next_opline->opcode == ZEND_NOP) {
						++next_opline;
					}

					if (next_opline >= end || next_opline->opcode != ZEND_ASSIGN) {
						break;
					}

					/* change $i=expr+$i to $i=$i+expr so that the following optimization
					 * works on it. Only do this if we are ignoring operator overloading,
					 * as operand order might be significant otherwise. */
					if ((ctx->optimization_level & ZEND_OPTIMIZER_IGNORE_OVERLOADING)
						&& (opline->op2_type & (IS_VAR | IS_CV))
						&& opline->op2.var == next_opline->op1.var &&
						(opline->opcode == ZEND_ADD ||
						 opline->opcode == ZEND_MUL ||
						 opline->opcode == ZEND_BW_OR ||
						 opline->opcode == ZEND_BW_AND ||
						 opline->opcode == ZEND_BW_XOR)) {
						zend_uchar tmp_type = opline->op1_type;
						znode_op tmp = opline->op1;

						if (opline->opcode != ZEND_ADD
								|| (opline->op1_type == IS_CONST
									&& Z_TYPE(ZEND_OP1_LITERAL(opline)) != IS_ARRAY)) {
							/* protection from array add: $a = array + $a is not commutative! */
							COPY_NODE(opline->op1, opline->op2);
							COPY_NODE(opline->op2, tmp);
						}
					}

					if ((opline->op1_type & (IS_VAR | IS_CV))
						&& opline->op1.var == next_opline->op1.var
						&& opline->op1_type == next_opline->op1_type) {
						switch (opline->opcode) {
							case ZEND_ADD:
								opline->opcode = ZEND_ASSIGN_ADD;
								break;
							case ZEND_SUB:
								opline->opcode = ZEND_ASSIGN_SUB;
								break;
							case ZEND_MUL:
								opline->opcode = ZEND_ASSIGN_MUL;
								break;
							case ZEND_DIV:
								opline->opcode = ZEND_ASSIGN_DIV;
								break;
							case ZEND_MOD:
								opline->opcode = ZEND_ASSIGN_MOD;
								break;
							case ZEND_POW:
								opline->opcode = ZEND_ASSIGN_POW;
								break;
							case ZEND_CONCAT:
								opline->opcode = ZEND_ASSIGN_CONCAT;
								break;
							case ZEND_SL:
								opline->opcode = ZEND_ASSIGN_SL;
								break;
							case ZEND_SR:
								opline->opcode = ZEND_ASSIGN_SR;
								break;
							case ZEND_BW_OR:
								opline->opcode = ZEND_ASSIGN_BW_OR;
								break;
							case ZEND_BW_AND:
								opline->opcode = ZEND_ASSIGN_BW_AND;
								break;
							case ZEND_BW_XOR:
								opline->opcode = ZEND_ASSIGN_BW_XOR;
								break;
						}
						COPY_NODE(opline->result, next_opline->result);
						MAKE_NOP(next_opline);
						opline++;
						opline_num++;
					}
				}
				break;

			case ZEND_JMP:
				if (op_array->fn_flags & ZEND_ACC_HAS_FINALLY_BLOCK) {
					break;
				}

				/* convert L: JMP L+1 to NOP */
				if (ZEND_OP1_JMP_ADDR(opline) == opline + 1) {
					MAKE_NOP(opline);
					goto done_jmp_optimization;
				}

				/* convert JMP L1 ... L1: JMP L2 to JMP L2 .. L1: JMP L2 */
				while (ZEND_OP1_JMP_ADDR(opline) < end
						&& ZEND_OP1_JMP_ADDR(opline)->opcode == ZEND_JMP) {
					zend_op *target = ZEND_OP1_JMP_ADDR(opline);
					CHECK_JMP(target, done_jmp_optimization);
					ZEND_SET_OP_JMP_ADDR(opline, opline->op1, ZEND_OP1_JMP_ADDR(target));
				}
				break;

			case ZEND_JMP_SET:
			case ZEND_COALESCE:
				if (op_array->fn_flags & ZEND_ACC_HAS_FINALLY_BLOCK) {
					break;
				}

				while (ZEND_OP2_JMP_ADDR(opline) < end) {
					zend_op *target = ZEND_OP2_JMP_ADDR(opline);
					if (target->opcode == ZEND_JMP) {
						ZEND_SET_OP_JMP_ADDR(opline, opline->op2, ZEND_OP1_JMP_ADDR(target));
					} else {
						break;
					}
				}
				break;
			case ZEND_JMPZ:
			case ZEND_JMPNZ:
				if (op_array->fn_flags & ZEND_ACC_HAS_FINALLY_BLOCK) {
					break;
				}

				while (ZEND_OP2_JMP_ADDR(opline) < end) {
					zend_op *target = ZEND_OP2_JMP_ADDR(opline);

					if (target->opcode == ZEND_JMP) {
						/* plain JMP */
						/* JMPZ(X,L1), L1: JMP(L2) => JMPZ(X,L2), L1: JMP(L2) */
						CHECK_JMP(target, done_jmp_optimization);
						ZEND_SET_OP_JMP_ADDR(opline, opline->op2, ZEND_OP1_JMP_ADDR(target));
					} else if (target->opcode == opline->opcode &&
					           SAME_VAR(opline->op1, target->op1)) {
						/* same opcode and same var as this opcode */
						/* JMPZ(X,L1), L1: JMPZ(X,L2) => JMPZ(X,L2), L1: JMPZ(X,L2) */
						CHECK_JMP2(target, done_jmp_optimization);
						ZEND_SET_OP_JMP_ADDR(opline, opline->op2, ZEND_OP2_JMP_ADDR(target));
					} else if (target->opcode == opline->opcode + 3 &&
					           SAME_VAR(opline->op1, target->op1)) {
						/* convert JMPZ(X,L1), L1: T JMPZ_EX(X,L2) to
						   T = JMPZ_EX(X, L2) */
						ZEND_SET_OP_JMP_ADDR(opline, opline->op2, ZEND_OP2_JMP_ADDR(target));
						opline->opcode += 3;
						COPY_NODE(opline->result, target->result);
						break;
					} else if (target->opcode == INV_COND(opline->opcode) &&
					           SAME_VAR(opline->op1, target->op1)) {
						/* convert JMPZ(X,L1), L1: JMPNZ(X,L2) to
						   JMPZ(X,L1+1) */
						ZEND_SET_OP_JMP_ADDR(opline, opline->op2, target + 1);
						break;
					} else if (target->opcode == INV_COND_EX(opline->opcode) &&
					           SAME_VAR(opline->op1, target->op1)) {
						/* convert JMPZ(X,L1), L1: T = JMPNZ_EX(X,L2) to
						   T = JMPZ_EX(X,L1+1) */
						ZEND_SET_OP_JMP_ADDR(opline, opline->op2, target + 1);
						opline->opcode += 3;
						COPY_NODE(opline->result, target->result);
						break;
					} else {
						break;
					}
				}
				break;

			case ZEND_JMPZ_EX:
			case ZEND_JMPNZ_EX: {
					zend_uchar T_type = opline->result_type;
					znode_op T = opline->result;

					if (op_array->fn_flags & ZEND_ACC_HAS_FINALLY_BLOCK) {
						break;
					}

					/* convert L: T = JMPZ_EX X,L+1 to T = BOOL(X) */
					/* convert L: T = JMPZ_EX T,L+1 to NOP */
					if (ZEND_OP2_JMP_ADDR(opline) == opline + 1) {
						if (opline->op1.var == opline->result.var) {
							MAKE_NOP(opline);
						} else {
							opline->opcode = ZEND_BOOL;
							SET_UNUSED(opline->op2);
						}
						goto done_jmp_optimization;
					}

					while (ZEND_OP2_JMP_ADDR(opline) < end) {
						zend_op *target = ZEND_OP2_JMP_ADDR(opline);

						if (target->opcode == opline->opcode-3 &&
							SAME_VAR(target->op1, T)) {
						   /* convert T=JMPZ_EX(X,L1), L1: JMPZ(T,L2) to
							  JMPZ_EX(X,L2) */
							CHECK_JMP2(target, continue_jmp_ex_optimization);
							ZEND_SET_OP_JMP_ADDR(opline, opline->op2, ZEND_OP2_JMP_ADDR(target));
						} else if (target->opcode == opline->opcode &&
							SAME_VAR(target->op1, T) &&
							SAME_VAR(target->result, T)) {
						   /* convert T=JMPZ_EX(X,L1), L1: T=JMPZ_EX(T,L2) to
							  JMPZ_EX(X,L2) */
							CHECK_JMP2(target, continue_jmp_ex_optimization);
							ZEND_SET_OP_JMP_ADDR(opline, opline->op2, ZEND_OP2_JMP_ADDR(target));
						} else if (target->opcode == ZEND_JMPZNZ &&
								  SAME_VAR(target->op1, T)) {
							/* Check for JMPZNZ with same cond variable */
							zend_op *new_target;

							CHECK_JMP2(target, continue_jmp_ex_optimization);
							if (opline->opcode == ZEND_JMPZ_EX) {
								new_target = ZEND_OP2_JMP_ADDR(target);
							} else {
								/* JMPNZ_EX */
								new_target = ZEND_OFFSET_TO_OPLINE(target, target->extended_value);
							}
							ZEND_SET_OP_JMP_ADDR(opline, opline->op2, new_target);
						} else if ((target->opcode == INV_EX_COND_EX(opline->opcode) ||
									target->opcode == INV_EX_COND(opline->opcode)) &&
									SAME_VAR(opline->op1, target->op1)) {
						   /* convert JMPZ_EX(X,L1), L1: JMPNZ_EX(X,L2) to
							  JMPZ_EX(X,L1+1) */
							ZEND_SET_OP_JMP_ADDR(opline, opline->op2, target + 1);
							break;
						} else if (target->opcode == INV_EX_COND(opline->opcode) &&
									SAME_VAR(target->op1, T)) {
						   /* convert T=JMPZ_EX(X,L1), L1: JMPNZ(T,L2) to
							  JMPZ_EX(X,L1+1) */
							ZEND_SET_OP_JMP_ADDR(opline, opline->op2, target + 1);
							break;
						} else if (target->opcode == INV_EX_COND_EX(opline->opcode) &&
									SAME_VAR(target->op1, T) &&
									SAME_VAR(target->result, T)) {
						   /* convert T=JMPZ_EX(X,L1), L1: T=JMPNZ_EX(T,L2) to
							  JMPZ_EX(X,L1+1) */
							ZEND_SET_OP_JMP_ADDR(opline, opline->op2, target + 1);
							break;
						} else if (target->opcode == ZEND_BOOL &&
						           SAME_VAR(opline->result, target->op1)) {
							/* convert Y = JMPZ_EX(X,L1), L1: Z = BOOL(Y) to
							   Z = JMPZ_EX(X,L1+1) */
							opline->result.var = target->result.var;
							ZEND_SET_OP_JMP_ADDR(opline, opline->op2, target + 1);
							break;
						} else {
							break;
						}
					} /* while */
continue_jmp_ex_optimization:
					break;
#if 0
					/* If Ti = JMPZ_EX(X, L) and Ti is not used, convert to JMPZ(X, L) */
					{
						zend_op *op;
						for(op = opline+1; op<end; op++) {
							if(op->result_type == IS_TMP_VAR &&
							   op->result.var == opline->result.var) {
								break; /* can pass to part 2 */
							}

							if(op->opcode == ZEND_JMP ||
							   op->opcode == ZEND_JMPZ ||
							   op->opcode == ZEND_JMPZ_EX ||
							   op->opcode == ZEND_JMPNZ ||
							   op->opcode == ZEND_JMPNZ_EX ||
							   op->opcode == ZEND_JMPZNZ ||
							   op->opcode == ZEND_CASE ||
							   op->opcode == ZEND_RETURN ||
							   op->opcode == ZEND_RETURN_BY_REF ||
							   op->opcode == ZEND_FAST_RET ||
							   op->opcode == ZEND_FE_FETCH_R ||
							   op->opcode == ZEND_FE_FETCH_RW ||
							   op->opcode == ZEND_EXIT) {
								break;
							}

							if(op->op1_type == IS_TMP_VAR &&
							   op->op1.var == opline->result.var) {
								goto done_jmp_optimization;
							}

							if(op->op2_type == IS_TMP_VAR &&
							   op->op2.var == opline->result.var) {
								goto done_jmp_optimization;
							}
						} /* for */

						for(op = &op_array->opcodes[opline->op2.opline_num]; op<end; op++) {

							if(op->result_type == IS_TMP_VAR &&
							   op->result.var == opline->result.var) {
								break; /* can pass to optimization */
							}

							if(op->opcode == ZEND_JMP ||
							   op->opcode == ZEND_JMPZ ||
							   op->opcode == ZEND_JMPZ_EX ||
							   op->opcode == ZEND_JMPNZ ||
							   op->opcode == ZEND_JMPNZ_EX ||
							   op->opcode == ZEND_JMPZNZ ||
							   op->opcode == ZEND_CASE ||
							   op->opcode == ZEND_RETURN ||
							   op->opcode == ZEND_RETURN_BY_REF ||
							   op->opcode == ZEND_FAST_RET ||
							   op->opcode == ZEND_FE_FETCH_R ||
							   op->opcode == ZEND_FE_FETCH_RW ||
							   op->opcode == ZEND_EXIT) {
								break;
							}

							if(op->op1_type == IS_TMP_VAR &&
							   op->op1.var == opline->result.var) {
								goto done_jmp_optimization;
							}

							if(op->op2_type == IS_TMP_VAR &&
							   op->op2.var == opline->result.var) {
								goto done_jmp_optimization;
							}
						}

						opline->opcode = opline->opcode-3; /* JMP_EX -> JMP */
						SET_UNUSED(opline->result);
						break;
					}
#endif
				}
				break;

			case ZEND_JMPZNZ:
				if (op_array->fn_flags & ZEND_ACC_HAS_FINALLY_BLOCK) {
					break;
				}

				/* JMPZNZ(X,L1,L2), L1: JMP(L3) => JMPZNZ(X,L3,L2), L1: JMP(L3) */
				while (ZEND_OP2_JMP_ADDR(opline) < end
						&& ZEND_OP2_JMP_ADDR(opline)->opcode == ZEND_JMP) {
					zend_op *target = ZEND_OP2_JMP_ADDR(opline);
					CHECK_JMP(target, continue_jmpznz_optimization);
					ZEND_SET_OP_JMP_ADDR(opline, opline->op2, ZEND_OP1_JMP_ADDR(target));
				}
continue_jmpznz_optimization:
				/* JMPZNZ(X,L1,L2), L2: JMP(L3) => JMPZNZ(X,L1,L3), L2: JMP(L3) */
				while (ZEND_OFFSET_TO_OPLINE(opline, opline->extended_value) < end
						&& ZEND_OFFSET_TO_OPLINE(opline, opline->extended_value)->opcode == ZEND_JMP) {
					zend_op *target = ZEND_OFFSET_TO_OPLINE(opline, opline->extended_value);
					CHECK_JMP(target, done_jmp_optimization);
					opline->extended_value = ZEND_OPLINE_TO_OFFSET(opline, ZEND_OP1_JMP_ADDR(target));
				}
				break;

			case ZEND_POST_INC_OBJ:
			case ZEND_POST_DEC_OBJ:
			case ZEND_POST_INC:
			case ZEND_POST_DEC: {
					/* POST_INC, FREE => PRE_INC */
					zend_op *next_op = opline + 1;

					if (next_op >= end) {
						break;
					}
					if (next_op->opcode == ZEND_FREE &&
						next_op->op1.var == opline->result.var) {
						MAKE_NOP(next_op);
						opline->opcode -= 2;
						opline->result_type = IS_UNUSED;
					}
				}
				break;
		}
done_jmp_optimization:
		opline++;
		opline_num++;
	}
	free_alloca(jmp_hitlist, use_heap);
}