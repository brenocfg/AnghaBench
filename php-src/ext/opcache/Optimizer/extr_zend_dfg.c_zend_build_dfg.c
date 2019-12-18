#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int fn_flags; TYPE_5__* opcodes; } ;
typedef  TYPE_4__ zend_op_array ;
struct TYPE_12__ {int /*<<< orphan*/  var; } ;
struct TYPE_14__ {int /*<<< orphan*/  var; } ;
struct TYPE_13__ {int /*<<< orphan*/  var; } ;
struct TYPE_16__ {scalar_t__ opcode; int op1_type; int op2_type; int extended_value; int result_type; TYPE_1__ result; TYPE_3__ op2; TYPE_2__ op1; } ;
typedef  TYPE_5__ zend_op ;
struct TYPE_17__ {int size; int /*<<< orphan*/  out; int /*<<< orphan*/  in; int /*<<< orphan*/  use; int /*<<< orphan*/  def; int /*<<< orphan*/  tmp; } ;
typedef  TYPE_6__ zend_dfg ;
struct TYPE_18__ {int blocks_count; int* predecessors; TYPE_8__* blocks; } ;
typedef  TYPE_7__ zend_cfg ;
typedef  int /*<<< orphan*/  zend_bitset ;
struct TYPE_19__ {int flags; int start; int len; int successors_count; int* successors; size_t predecessor_offset; int predecessors_count; } ;
typedef  TYPE_8__ zend_basic_block ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCA_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFG_BITSET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DFG_ISSET (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  DFG_SET (int /*<<< orphan*/ ,int,int,int) ; 
 int EX_VAR_TO_NUM (int /*<<< orphan*/ ) ; 
 int IS_CV ; 
 int IS_TMP_VAR ; 
 int IS_VAR ; 
 int SUCCESS ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
#define  ZEND_ADD_ARRAY_ELEMENT 173 
 int ZEND_ARRAY_ELEMENT_REF ; 
#define  ZEND_ASSIGN 172 
#define  ZEND_ASSIGN_DIM 171 
#define  ZEND_ASSIGN_DIM_OP 170 
#define  ZEND_ASSIGN_OBJ 169 
#define  ZEND_ASSIGN_OBJ_OP 168 
#define  ZEND_ASSIGN_OBJ_REF 167 
#define  ZEND_ASSIGN_OP 166 
#define  ZEND_ASSIGN_REF 165 
#define  ZEND_ASSIGN_STATIC_PROP_OP 164 
 int ZEND_ASSIGN_STATIC_PROP_REF ; 
 int ZEND_BB_REACHABLE ; 
#define  ZEND_BIND_GLOBAL 163 
#define  ZEND_BIND_LEXICAL 162 
 int ZEND_BIND_REF ; 
#define  ZEND_BIND_STATIC 161 
 int /*<<< orphan*/  ZEND_BITSET_ALLOCA (int,int /*<<< orphan*/ ) ; 
 int ZEND_BITSET_ELM_SIZE ; 
#define  ZEND_CAST 160 
#define  ZEND_COALESCE 159 
#define  ZEND_FETCH_DIM_FUNC_ARG 158 
#define  ZEND_FETCH_DIM_RW 157 
#define  ZEND_FETCH_DIM_UNSET 156 
#define  ZEND_FETCH_DIM_W 155 
#define  ZEND_FETCH_LIST_W 154 
#define  ZEND_FE_FETCH_R 153 
#define  ZEND_FE_FETCH_RW 152 
#define  ZEND_FE_RESET_R 151 
#define  ZEND_FE_RESET_RW 150 
#define  ZEND_INIT_ARRAY 149 
#define  ZEND_JMP_SET 148 
 scalar_t__ ZEND_OP_DATA ; 
#define  ZEND_POST_DEC 147 
#define  ZEND_POST_DEC_OBJ 146 
#define  ZEND_POST_INC 145 
#define  ZEND_POST_INC_OBJ 144 
#define  ZEND_PRE_DEC 143 
#define  ZEND_PRE_DEC_OBJ 142 
#define  ZEND_PRE_INC 141 
#define  ZEND_PRE_INC_OBJ 140 
#define  ZEND_QM_ASSIGN 139 
#define  ZEND_SEND_FUNC_ARG 138 
#define  ZEND_SEND_REF 137 
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
 int /*<<< orphan*/  free_alloca (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  use_heap ; 
 int /*<<< orphan*/  zend_bitset_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_bitset_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_bitset_empty (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_bitset_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_bitset_excl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_bitset_incl (int /*<<< orphan*/ ,int) ; 
 int zend_bitset_last (int /*<<< orphan*/ ,int) ; 
 int zend_bitset_len (int) ; 
 int /*<<< orphan*/  zend_bitset_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_bitset_union_with_difference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int zend_build_dfg(const zend_op_array *op_array, const zend_cfg *cfg, zend_dfg *dfg, uint32_t build_flags) /* {{{ */
{
	int set_size;
	zend_basic_block *blocks = cfg->blocks;
	int blocks_count = cfg->blocks_count;
	zend_bitset tmp, def, use, in, out;
	int k;
	uint32_t var_num;
	int j;

	set_size = dfg->size;
	tmp = dfg->tmp;
	def = dfg->def;
	use = dfg->use;
	in  = dfg->in;
	out = dfg->out;

	/* Collect "def" and "use" sets */
	for (j = 0; j < blocks_count; j++) {
		zend_op *opline, *end;
		if ((blocks[j].flags & ZEND_BB_REACHABLE) == 0) {
			continue;
		}

		opline = op_array->opcodes + blocks[j].start;
		end = opline + blocks[j].len;
		for (; opline < end; opline++) {
			if (opline->opcode != ZEND_OP_DATA) {
				zend_op *next = opline + 1;
				if (next < end && next->opcode == ZEND_OP_DATA) {
					if (next->op1_type & (IS_CV|IS_VAR|IS_TMP_VAR)) {
						var_num = EX_VAR_TO_NUM(next->op1.var);
						if (next->op1_type == IS_CV && (opline->opcode == ZEND_ASSIGN_OBJ_REF
								|| opline->opcode == ZEND_ASSIGN_STATIC_PROP_REF)) {
							DFG_SET(use, set_size, j, var_num);
							DFG_SET(def, set_size, j, var_num);
						} else {
							if (!DFG_ISSET(def, set_size, j, var_num)) {
								DFG_SET(use, set_size, j, var_num);
							}
						}
					}
					if (next->op2_type & (IS_CV|IS_VAR|IS_TMP_VAR)) {
						var_num = EX_VAR_TO_NUM(next->op2.var);
						if (!DFG_ISSET(def, set_size, j, var_num)) {
							DFG_SET(use, set_size, j, var_num);
						}
					}
				}
				if (opline->op1_type == IS_CV) {
					var_num = EX_VAR_TO_NUM(opline->op1.var);
					switch (opline->opcode) {
					case ZEND_ADD_ARRAY_ELEMENT:
					case ZEND_INIT_ARRAY:
						if ((build_flags & ZEND_SSA_RC_INFERENCE)
								|| (opline->extended_value & ZEND_ARRAY_ELEMENT_REF)) {
							goto op1_def;
						}
						goto op1_use;
					case ZEND_FE_RESET_R:
					case ZEND_SEND_VAR:
					case ZEND_CAST:
					case ZEND_QM_ASSIGN:
					case ZEND_JMP_SET:
					case ZEND_COALESCE:
						if (build_flags & ZEND_SSA_RC_INFERENCE) {
							goto op1_def;
						}
						goto op1_use;
					case ZEND_YIELD:
						if ((build_flags & ZEND_SSA_RC_INFERENCE)
								|| (op_array->fn_flags & ZEND_ACC_RETURN_REFERENCE)) {
							goto op1_def;
						}
						goto op1_use;
					case ZEND_UNSET_CV:
					case ZEND_ASSIGN:
					case ZEND_ASSIGN_REF:
					case ZEND_ASSIGN_OBJ_REF:
					case ZEND_BIND_GLOBAL:
					case ZEND_BIND_STATIC:
					case ZEND_SEND_VAR_EX:
					case ZEND_SEND_FUNC_ARG:
					case ZEND_SEND_REF:
					case ZEND_SEND_VAR_NO_REF:
					case ZEND_SEND_VAR_NO_REF_EX:
					case ZEND_FE_RESET_RW:
					case ZEND_ASSIGN_OP:
					case ZEND_ASSIGN_DIM_OP:
					case ZEND_ASSIGN_OBJ_OP:
					case ZEND_ASSIGN_STATIC_PROP_OP:
					case ZEND_PRE_INC:
					case ZEND_PRE_DEC:
					case ZEND_POST_INC:
					case ZEND_POST_DEC:
					case ZEND_ASSIGN_DIM:
					case ZEND_ASSIGN_OBJ:
					case ZEND_UNSET_DIM:
					case ZEND_UNSET_OBJ:
					case ZEND_FETCH_DIM_W:
					case ZEND_FETCH_DIM_RW:
					case ZEND_FETCH_DIM_FUNC_ARG:
					case ZEND_FETCH_DIM_UNSET:
					case ZEND_FETCH_LIST_W:
					case ZEND_VERIFY_RETURN_TYPE:
					case ZEND_PRE_INC_OBJ:
					case ZEND_PRE_DEC_OBJ:
					case ZEND_POST_INC_OBJ:
					case ZEND_POST_DEC_OBJ:
op1_def:
						/* `def` always come along with dtor or separation,
						 * thus the origin var info might be also `use`d in the feature(CG) */
						DFG_SET(use, set_size, j, var_num);
						DFG_SET(def, set_size, j, var_num);
						break;
					default:
op1_use:
						if (!DFG_ISSET(def, set_size, j, var_num)) {
							DFG_SET(use, set_size, j, var_num);
						}
					}
				} else if (opline->op1_type & (IS_VAR|IS_TMP_VAR)) {
					var_num = EX_VAR_TO_NUM(opline->op1.var);
					if (!DFG_ISSET(def, set_size, j, var_num)) {
						DFG_SET(use, set_size, j, var_num);
					}
					if (opline->opcode == ZEND_VERIFY_RETURN_TYPE) {
						DFG_SET(def, set_size, j, var_num);
					}
				}
				if (opline->op2_type == IS_CV) {
					var_num = EX_VAR_TO_NUM(opline->op2.var);
					switch (opline->opcode) {
						case ZEND_ASSIGN:
							if (build_flags & ZEND_SSA_RC_INFERENCE) {
								goto op2_def;
							}
							goto op2_use;
						case ZEND_BIND_LEXICAL:
							if ((build_flags & ZEND_SSA_RC_INFERENCE) || (opline->extended_value & ZEND_BIND_REF)) {
								goto op2_def;
							}
							goto op2_use;
						case ZEND_ASSIGN_REF:
						case ZEND_FE_FETCH_R:
						case ZEND_FE_FETCH_RW:
op2_def:
							// FIXME: include into "use" too ...?
							DFG_SET(use, set_size, j, var_num);
							DFG_SET(def, set_size, j, var_num);
							break;
						default:
op2_use:
							if (!DFG_ISSET(def, set_size, j, var_num)) {
								DFG_SET(use, set_size, j, var_num);
							}
							break;
					}
				} else if (opline->op2_type & (IS_VAR|IS_TMP_VAR)) {
					var_num = EX_VAR_TO_NUM(opline->op2.var);
					if (opline->opcode == ZEND_FE_FETCH_R || opline->opcode == ZEND_FE_FETCH_RW) {
						DFG_SET(def, set_size, j, var_num);
					} else {
						if (!DFG_ISSET(def, set_size, j, var_num)) {
							DFG_SET(use, set_size, j, var_num);
						}
					}
				}
				if (opline->result_type & (IS_CV|IS_VAR|IS_TMP_VAR)) {
					var_num = EX_VAR_TO_NUM(opline->result.var);
					if ((build_flags & ZEND_SSA_USE_CV_RESULTS)
					 && opline->result_type == IS_CV) {
						DFG_SET(use, set_size, j, var_num);
					}
					DFG_SET(def, set_size, j, var_num);
				}
			}
		}
	}

	/* Calculate "in" and "out" sets */
	{
		uint32_t worklist_len = zend_bitset_len(blocks_count);
		zend_bitset worklist;
		ALLOCA_FLAG(use_heap);
		worklist = ZEND_BITSET_ALLOCA(worklist_len, use_heap);
		memset(worklist, 0, worklist_len * ZEND_BITSET_ELM_SIZE);
		for (j = 0; j < blocks_count; j++) {
			zend_bitset_incl(worklist, j);
		}
		while (!zend_bitset_empty(worklist, worklist_len)) {
			/* We use the last block on the worklist, because predecessors tend to be located
			 * before the succeeding block, so this converges faster. */
			j = zend_bitset_last(worklist, worklist_len);
			zend_bitset_excl(worklist, j);

			if ((blocks[j].flags & ZEND_BB_REACHABLE) == 0) {
				continue;
			}
			if (blocks[j].successors_count != 0) {
				zend_bitset_copy(DFG_BITSET(out, set_size, j), DFG_BITSET(in, set_size, blocks[j].successors[0]), set_size);
				for (k = 1; k < blocks[j].successors_count; k++) {
					zend_bitset_union(DFG_BITSET(out, set_size, j), DFG_BITSET(in, set_size, blocks[j].successors[k]), set_size);
				}
			} else {
				zend_bitset_clear(DFG_BITSET(out, set_size, j), set_size);
			}
			zend_bitset_union_with_difference(tmp, DFG_BITSET(use, set_size, j), DFG_BITSET(out, set_size, j), DFG_BITSET(def, set_size, j), set_size);
			if (!zend_bitset_equal(DFG_BITSET(in, set_size, j), tmp, set_size)) {
				zend_bitset_copy(DFG_BITSET(in, set_size, j), tmp, set_size);

				/* Add predecessors of changed block to worklist */
				{
					int *predecessors = &cfg->predecessors[blocks[j].predecessor_offset];
					for (k = 0; k < blocks[j].predecessors_count; k++) {
						zend_bitset_incl(worklist, predecessors[k]);
					}
				}
			}
		}

		free_alloca(worklist, use_heap);
	}

	return SUCCESS;
}