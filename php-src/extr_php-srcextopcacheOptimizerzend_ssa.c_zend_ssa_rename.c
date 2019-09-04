#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {size_t min_var; int min_ssa_var; size_t max_var; int max_ssa_var; } ;
struct TYPE_24__ {TYPE_4__ range; } ;
struct TYPE_26__ {int ssa_var; size_t var; int pi; int* sources; struct TYPE_26__* next; TYPE_5__ constraint; scalar_t__ has_range_constraint; } ;
typedef  TYPE_7__ zend_ssa_phi ;
struct TYPE_27__ {int op1_use; int op2_use; int op2_def; int op1_def; int result_use; int result_def; } ;
typedef  TYPE_8__ zend_ssa_op ;
struct TYPE_28__ {TYPE_7__* phis; } ;
typedef  TYPE_9__ zend_ssa_block ;
struct TYPE_25__ {int* predecessors; TYPE_13__* blocks; } ;
struct TYPE_16__ {int vars_count; TYPE_6__ cfg; TYPE_8__* ops; TYPE_9__* blocks; } ;
typedef  TYPE_10__ zend_ssa ;
struct TYPE_17__ {int last_var; int T; int fn_flags; TYPE_12__* opcodes; } ;
typedef  TYPE_11__ zend_op_array ;
struct TYPE_22__ {int /*<<< orphan*/  var; } ;
struct TYPE_21__ {int /*<<< orphan*/  var; } ;
struct TYPE_20__ {int /*<<< orphan*/  var; } ;
struct TYPE_18__ {scalar_t__ opcode; int op1_type; int op2_type; int extended_value; int result_type; TYPE_3__ result; TYPE_2__ op1; TYPE_1__ op2; } ;
typedef  TYPE_12__ zend_op ;
struct TYPE_19__ {int next_child; int start; int len; int successors_count; int* successors; int predecessors_count; int predecessor_offset; int children; } ;
typedef  TYPE_13__ zend_basic_block ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCA_FLAG (scalar_t__) ; 
 size_t EX_VAR_TO_NUM (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 int IS_CV ; 
 int IS_TMP_VAR ; 
 int IS_VAR ; 
 scalar_t__ SUCCESS ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
#define  ZEND_ADD_ARRAY_ELEMENT 186 
 int ZEND_ARRAY_ELEMENT_REF ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
#define  ZEND_ASSIGN 185 
#define  ZEND_ASSIGN_ADD 184 
#define  ZEND_ASSIGN_BW_AND 183 
#define  ZEND_ASSIGN_BW_OR 182 
#define  ZEND_ASSIGN_BW_XOR 181 
#define  ZEND_ASSIGN_CONCAT 180 
#define  ZEND_ASSIGN_DIM 179 
#define  ZEND_ASSIGN_DIV 178 
#define  ZEND_ASSIGN_MOD 177 
#define  ZEND_ASSIGN_MUL 176 
#define  ZEND_ASSIGN_OBJ 175 
#define  ZEND_ASSIGN_OBJ_REF 174 
#define  ZEND_ASSIGN_POW 173 
#define  ZEND_ASSIGN_REF 172 
#define  ZEND_ASSIGN_SL 171 
#define  ZEND_ASSIGN_SR 170 
#define  ZEND_ASSIGN_STATIC_PROP_REF 169 
#define  ZEND_ASSIGN_SUB 168 
#define  ZEND_BIND_GLOBAL 167 
#define  ZEND_BIND_LEXICAL 166 
 int ZEND_BIND_REF ; 
#define  ZEND_BIND_STATIC 165 
#define  ZEND_CAST 164 
#define  ZEND_COALESCE 163 
#define  ZEND_FETCH_DIM_FUNC_ARG 162 
#define  ZEND_FETCH_DIM_RW 161 
#define  ZEND_FETCH_DIM_UNSET 160 
#define  ZEND_FETCH_DIM_W 159 
#define  ZEND_FETCH_LIST_W 158 
#define  ZEND_FETCH_OBJ_FUNC_ARG 157 
#define  ZEND_FETCH_OBJ_RW 156 
#define  ZEND_FETCH_OBJ_UNSET 155 
#define  ZEND_FETCH_OBJ_W 154 
 scalar_t__ ZEND_FE_FETCH_R ; 
 scalar_t__ ZEND_FE_FETCH_RW ; 
#define  ZEND_FE_RESET_R 153 
#define  ZEND_FE_RESET_RW 152 
#define  ZEND_INIT_ARRAY 151 
#define  ZEND_JMP_SET 150 
#define  ZEND_MAKE_REF 149 
 scalar_t__ ZEND_OP_DATA ; 
#define  ZEND_POST_DEC 148 
#define  ZEND_POST_DEC_OBJ 147 
#define  ZEND_POST_INC 146 
#define  ZEND_POST_INC_OBJ 145 
#define  ZEND_PRE_DEC 144 
#define  ZEND_PRE_DEC_OBJ 143 
#define  ZEND_PRE_INC 142 
#define  ZEND_PRE_INC_OBJ 141 
#define  ZEND_QM_ASSIGN 140 
 int ZEND_RECV ; 
#define  ZEND_SEND_FUNC_ARG 139 
#define  ZEND_SEND_REF 138 
#define  ZEND_SEND_UNPACK 137 
#define  ZEND_SEND_VAR 136 
#define  ZEND_SEND_VAR_EX 135 
#define  ZEND_SEND_VAR_NO_REF 134 
#define  ZEND_SEND_VAR_NO_REF_EX 133 
 int ZEND_SSA_RC_INFERENCE ; 
 int ZEND_SSA_USE_CV_RESULTS ; 
#define  ZEND_UNSET_CV 132 
#define  ZEND_UNSET_DIM 131 
#define  ZEND_UNSET_OBJ 130 
#define  ZEND_VERIFY_RETURN_TYPE 129 
#define  ZEND_YIELD 128 
 int* do_alloca (int,scalar_t__) ; 
 int /*<<< orphan*/  free_alloca (int*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ use_heap ; 

__attribute__((used)) static int zend_ssa_rename(const zend_op_array *op_array, uint32_t build_flags, zend_ssa *ssa, int *var, int n) /* {{{ */
{
	zend_basic_block *blocks = ssa->cfg.blocks;
	zend_ssa_block *ssa_blocks = ssa->blocks;
	zend_ssa_op *ssa_ops = ssa->ops;
	int ssa_vars_count = ssa->vars_count;
	int i, j;
	zend_op *opline, *end;
	int *tmp = NULL;
	ALLOCA_FLAG(use_heap = 0);

	// FIXME: Can we optimize this copying out in some cases?
	if (blocks[n].next_child >= 0) {
		tmp = do_alloca(sizeof(int) * (op_array->last_var + op_array->T), use_heap);
		memcpy(tmp, var, sizeof(int) * (op_array->last_var + op_array->T));
		var = tmp;
	}

	if (ssa_blocks[n].phis) {
		zend_ssa_phi *phi = ssa_blocks[n].phis;
		do {
			if (phi->ssa_var < 0) {
				phi->ssa_var = ssa_vars_count;
				var[phi->var] = ssa_vars_count;
				ssa_vars_count++;
			} else {
				var[phi->var] = phi->ssa_var;
			}
			phi = phi->next;
		} while (phi);
	}

	opline = op_array->opcodes + blocks[n].start;
	end = opline + blocks[n].len;
	for (; opline < end; opline++) {
		uint32_t k = opline - op_array->opcodes;
		if (opline->opcode != ZEND_OP_DATA) {
			zend_op *next = opline + 1;
			if (next < end && next->opcode == ZEND_OP_DATA) {
				if (next->op1_type == IS_CV) {
					ssa_ops[k + 1].op1_use = var[EX_VAR_TO_NUM(next->op1.var)];
					//USE_SSA_VAR(next->op1.var);
				} else if (next->op1_type & (IS_VAR|IS_TMP_VAR)) {
					ssa_ops[k + 1].op1_use = var[EX_VAR_TO_NUM(next->op1.var)];
					//USE_SSA_VAR(op_array->last_var + next->op1.var);
				}
				if (next->op2_type == IS_CV) {
					ssa_ops[k + 1].op2_use = var[EX_VAR_TO_NUM(next->op2.var)];
					//USE_SSA_VAR(next->op2.var);
				} else if (next->op2_type & (IS_VAR|IS_TMP_VAR)) {
					ssa_ops[k + 1].op2_use = var[EX_VAR_TO_NUM(next->op2.var)];
					//USE_SSA_VAR(op_array->last_var + next->op2.var);
				}
			}
			if (opline->op1_type & (IS_CV|IS_VAR|IS_TMP_VAR)) {
				ssa_ops[k].op1_use = var[EX_VAR_TO_NUM(opline->op1.var)];
				//USE_SSA_VAR(op_array->last_var + opline->op1.var)
			}
			if (opline->opcode == ZEND_FE_FETCH_R || opline->opcode == ZEND_FE_FETCH_RW) {
				if (opline->op2_type == IS_CV) {
					ssa_ops[k].op2_use = var[EX_VAR_TO_NUM(opline->op2.var)];
				}
				ssa_ops[k].op2_def = ssa_vars_count;
				var[EX_VAR_TO_NUM(opline->op2.var)] = ssa_vars_count;
				ssa_vars_count++;
				//NEW_SSA_VAR(opline->op2.var)
			} else if (opline->op2_type & (IS_CV|IS_VAR|IS_TMP_VAR)) {
				ssa_ops[k].op2_use = var[EX_VAR_TO_NUM(opline->op2.var)];
				//USE_SSA_VAR(op_array->last_var + opline->op2.var)
			}
			switch (opline->opcode) {
				case ZEND_ASSIGN:
					if ((build_flags & ZEND_SSA_RC_INFERENCE) && opline->op2_type == IS_CV) {
						ssa_ops[k].op2_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op2.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op2.var)
					}
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_ASSIGN_REF:
//TODO: ???
					if (opline->op2_type == IS_CV) {
						ssa_ops[k].op2_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op2.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op2.var)
					}
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_BIND_GLOBAL:
				case ZEND_BIND_STATIC:
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_ASSIGN_DIM:
				case ZEND_ASSIGN_OBJ:
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					if ((build_flags & ZEND_SSA_RC_INFERENCE) && next->op1_type == IS_CV) {
						ssa_ops[k + 1].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(next->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(next->op1.var)
					}
					break;
				case ZEND_ASSIGN_OBJ_REF:
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					/* break missing intentionally */
				case ZEND_ASSIGN_STATIC_PROP_REF:
					if (next->op1_type == IS_CV) {
						ssa_ops[k + 1].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(next->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(next->op1.var)
					}
					break;
				case ZEND_PRE_INC_OBJ:
				case ZEND_PRE_DEC_OBJ:
				case ZEND_POST_INC_OBJ:
				case ZEND_POST_DEC_OBJ:
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_ADD_ARRAY_ELEMENT:
					ssa_ops[k].result_use = var[EX_VAR_TO_NUM(opline->result.var)];
				case ZEND_INIT_ARRAY:
					if (((build_flags & ZEND_SSA_RC_INFERENCE)
								|| (opline->extended_value & ZEND_ARRAY_ELEMENT_REF))
							&& opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline+->op1.var)
					}
					break;
				case ZEND_SEND_VAR:
				case ZEND_CAST:
				case ZEND_QM_ASSIGN:
				case ZEND_JMP_SET:
				case ZEND_COALESCE:
					if ((build_flags & ZEND_SSA_RC_INFERENCE) && opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_SEND_VAR_NO_REF:
				case ZEND_SEND_VAR_NO_REF_EX:
				case ZEND_SEND_VAR_EX:
				case ZEND_SEND_FUNC_ARG:
				case ZEND_SEND_REF:
				case ZEND_SEND_UNPACK:
				case ZEND_FE_RESET_RW:
				case ZEND_MAKE_REF:
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_FE_RESET_R:
					if ((build_flags & ZEND_SSA_RC_INFERENCE) && opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_ASSIGN_ADD:
				case ZEND_ASSIGN_SUB:
				case ZEND_ASSIGN_MUL:
				case ZEND_ASSIGN_DIV:
				case ZEND_ASSIGN_MOD:
				case ZEND_ASSIGN_SL:
				case ZEND_ASSIGN_SR:
				case ZEND_ASSIGN_CONCAT:
				case ZEND_ASSIGN_BW_OR:
				case ZEND_ASSIGN_BW_AND:
				case ZEND_ASSIGN_BW_XOR:
				case ZEND_ASSIGN_POW:
				case ZEND_PRE_INC:
				case ZEND_PRE_DEC:
				case ZEND_POST_INC:
				case ZEND_POST_DEC:
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_UNSET_CV:
					ssa_ops[k].op1_def = ssa_vars_count;
					var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
					ssa_vars_count++;
					break;
				case ZEND_UNSET_DIM:
				case ZEND_UNSET_OBJ:
				case ZEND_FETCH_DIM_W:
				case ZEND_FETCH_DIM_RW:
				case ZEND_FETCH_DIM_FUNC_ARG:
				case ZEND_FETCH_DIM_UNSET:
				case ZEND_FETCH_OBJ_W:
				case ZEND_FETCH_OBJ_RW:
				case ZEND_FETCH_OBJ_FUNC_ARG:
				case ZEND_FETCH_OBJ_UNSET:
				case ZEND_FETCH_LIST_W:
					if (opline->op1_type == IS_CV) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				case ZEND_BIND_LEXICAL:
					if ((opline->extended_value & ZEND_BIND_REF) || (build_flags & ZEND_SSA_RC_INFERENCE)) {
						ssa_ops[k].op2_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op2.var)] = ssa_vars_count;
						ssa_vars_count++;
					}
					break;
				case ZEND_YIELD:
					if (opline->op1_type == IS_CV
							&& ((op_array->fn_flags & ZEND_ACC_RETURN_REFERENCE)
								|| (build_flags & ZEND_SSA_RC_INFERENCE))) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
					}
					break;
				case ZEND_VERIFY_RETURN_TYPE:
					if (opline->op1_type & (IS_TMP_VAR|IS_VAR|IS_CV)) {
						ssa_ops[k].op1_def = ssa_vars_count;
						var[EX_VAR_TO_NUM(opline->op1.var)] = ssa_vars_count;
						ssa_vars_count++;
						//NEW_SSA_VAR(opline->op1.var)
					}
					break;
				default:
					break;
			}
			if (opline->result_type == IS_CV) {
				if ((build_flags & ZEND_SSA_USE_CV_RESULTS)
				 && opline->opcode != ZEND_RECV) {
					ssa_ops[k].result_use = var[EX_VAR_TO_NUM(opline->result.var)];
				}
				ssa_ops[k].result_def = ssa_vars_count;
				var[EX_VAR_TO_NUM(opline->result.var)] = ssa_vars_count;
				ssa_vars_count++;
				//NEW_SSA_VAR(opline->result.var)
			} else if (opline->result_type & (IS_VAR|IS_TMP_VAR)) {
				ssa_ops[k].result_def = ssa_vars_count;
				var[EX_VAR_TO_NUM(opline->result.var)] = ssa_vars_count;
				ssa_vars_count++;
				//NEW_SSA_VAR(op_array->last_var + opline->result.var)
			}
		}
	}

	for (i = 0; i < blocks[n].successors_count; i++) {
		int succ = blocks[n].successors[i];
		zend_ssa_phi *p;
		for (p = ssa_blocks[succ].phis; p; p = p->next) {
			if (p->pi == n) {
				/* e-SSA Pi */
				if (p->has_range_constraint) {
					if (p->constraint.range.min_var >= 0) {
						p->constraint.range.min_ssa_var = var[p->constraint.range.min_var];
					}
					if (p->constraint.range.max_var >= 0) {
						p->constraint.range.max_ssa_var = var[p->constraint.range.max_var];
					}
				}
				for (j = 0; j < blocks[succ].predecessors_count; j++) {
					p->sources[j] = var[p->var];
				}
				if (p->ssa_var < 0) {
					p->ssa_var = ssa_vars_count;
					ssa_vars_count++;
				}
			} else if (p->pi < 0) {
				/* Normal Phi */
				for (j = 0; j < blocks[succ].predecessors_count; j++)
					if (ssa->cfg.predecessors[blocks[succ].predecessor_offset + j] == n) {
						break;
					}
				ZEND_ASSERT(j < blocks[succ].predecessors_count);
				p->sources[j] = var[p->var];
			}
		}
		for (p = ssa_blocks[succ].phis; p && (p->pi >= 0); p = p->next) {
			if (p->pi == n) {
				zend_ssa_phi *q = p->next;
				while (q) {
					if (q->pi < 0 && q->var == p->var) {
						for (j = 0; j < blocks[succ].predecessors_count; j++) {
							if (ssa->cfg.predecessors[blocks[succ].predecessor_offset + j] == n) {
								break;
							}
						}
						ZEND_ASSERT(j < blocks[succ].predecessors_count);
						q->sources[j] = p->ssa_var;
					}
					q = q->next;
				}
			}
		}
	}

	ssa->vars_count = ssa_vars_count;

	j = blocks[n].children;
	while (j >= 0) {
		// FIXME: Tail call optimization?
		if (zend_ssa_rename(op_array, build_flags, ssa, var, j) != SUCCESS)
			return FAILURE;
		j = blocks[j].next_child;
	}

	if (tmp) {
		free_alloca(tmp, use_heap);
	}

	return SUCCESS;
}