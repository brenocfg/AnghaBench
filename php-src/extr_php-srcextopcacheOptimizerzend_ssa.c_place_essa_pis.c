#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_29__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_11__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_35__ {TYPE_10__* ce; } ;
struct TYPE_36__ {TYPE_3__ type; } ;
struct TYPE_37__ {TYPE_4__ constraint; } ;
typedef  TYPE_5__ zend_ssa_phi ;
struct TYPE_32__ {int blocks_count; TYPE_11__* blocks; } ;
struct TYPE_38__ {TYPE_1__ cfg; } ;
typedef  TYPE_6__ zend_ssa ;
struct TYPE_39__ {int /*<<< orphan*/  class_table; } ;
typedef  TYPE_7__ zend_script ;
struct TYPE_40__ {TYPE_9__* opcodes; } ;
typedef  TYPE_8__ zend_op_array ;
struct TYPE_33__ {scalar_t__ var; } ;
struct TYPE_34__ {scalar_t__ var; } ;
struct TYPE_41__ {int opcode; scalar_t__ op1_type; scalar_t__ op2_type; scalar_t__ extended_value; TYPE_29__ op2; TYPE_29__ op1; TYPE_2__ result; } ;
typedef  TYPE_9__ zend_op ;
typedef  scalar_t__ zend_long ;
typedef  int /*<<< orphan*/  zend_dfg ;
struct TYPE_30__ {scalar_t__ type; } ;
typedef  TYPE_10__ zend_class_entry ;
struct TYPE_31__ {int start; int len; int flags; int* successors; } ;
typedef  TYPE_11__ zend_basic_block ;
typedef  int /*<<< orphan*/  zend_arena ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CRT_CONSTANT_EX (TYPE_8__ const*,TYPE_9__*,TYPE_29__,scalar_t__) ; 
 int EX_VAR_TO_NUM (scalar_t__) ; 
 scalar_t__ IS_CONST ; 
 scalar_t__ IS_CV ; 
 scalar_t__ IS_FALSE ; 
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_NULL ; 
 scalar_t__ IS_RESOURCE ; 
 scalar_t__ IS_TMP_VAR ; 
 scalar_t__ IS_TRUE ; 
 scalar_t__ IS_VAR ; 
 scalar_t__ MAY_BE_OBJECT ; 
 int ZEND_BB_REACHABLE ; 
 scalar_t__ ZEND_INSTANCEOF ; 
 scalar_t__ ZEND_INTERNAL_CLASS ; 
 scalar_t__ ZEND_IS_EQUAL ; 
 scalar_t__ ZEND_IS_IDENTICAL ; 
 scalar_t__ ZEND_IS_NOT_EQUAL ; 
 scalar_t__ ZEND_IS_NOT_IDENTICAL ; 
 scalar_t__ ZEND_IS_SMALLER ; 
 scalar_t__ ZEND_IS_SMALLER_OR_EQUAL ; 
#define  ZEND_JMPNZ 130 
#define  ZEND_JMPZ 129 
#define  ZEND_JMPZNZ 128 
 scalar_t__ ZEND_LONG_MAX ; 
 scalar_t__ ZEND_LONG_MIN ; 
 scalar_t__ ZEND_POST_DEC ; 
 scalar_t__ ZEND_POST_INC ; 
 scalar_t__ ZEND_PRE_DEC ; 
 scalar_t__ ZEND_PRE_INC ; 
 scalar_t__ ZEND_RT_CONSTANTS ; 
 scalar_t__ ZEND_TYPE_CHECK ; 
 scalar_t__ Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ _const_op_type (int /*<<< orphan*/ *) ; 
 TYPE_5__* add_pi (int /*<<< orphan*/ **,TYPE_8__ const*,int /*<<< orphan*/ *,TYPE_6__*,int,int,int) ; 
 int /*<<< orphan*/  add_will_overflow (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  class_table ; 
 int find_adjusted_tmp_var (TYPE_8__ const*,scalar_t__,TYPE_9__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ mask_for_type_check (scalar_t__) ; 
 int /*<<< orphan*/  pi_not_type_mask (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  pi_range_equals (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  pi_range_max (TYPE_5__*,int,scalar_t__) ; 
 int /*<<< orphan*/  pi_range_min (TYPE_5__*,int,scalar_t__) ; 
 int /*<<< orphan*/  pi_range_not_equals (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  pi_type_mask (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  sub_will_overflow (scalar_t__,scalar_t__) ; 
 TYPE_10__* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void place_essa_pis(
		zend_arena **arena, const zend_script *script, const zend_op_array *op_array,
		uint32_t build_flags, zend_ssa *ssa, zend_dfg *dfg) /* {{{ */ {
	zend_basic_block *blocks = ssa->cfg.blocks;
	int j, blocks_count = ssa->cfg.blocks_count;
	for (j = 0; j < blocks_count; j++) {
		zend_ssa_phi *pi;
		zend_op *opline = op_array->opcodes + blocks[j].start + blocks[j].len - 1;
		int bt; /* successor block number if a condition is true */
		int bf; /* successor block number if a condition is false */

		if ((blocks[j].flags & ZEND_BB_REACHABLE) == 0 || blocks[j].len == 0) {
			continue;
		}
		/* the last instruction of basic block is conditional branch,
		 * based on comparison of CV(s)
		 */
		switch (opline->opcode) {
			case ZEND_JMPZ:
			case ZEND_JMPZNZ:
				bf = blocks[j].successors[0];
				bt = blocks[j].successors[1];
				break;
			case ZEND_JMPNZ:
				bt = blocks[j].successors[0];
				bf = blocks[j].successors[1];
				break;
			default:
				continue;
		}
		if (opline->op1_type == IS_TMP_VAR &&
		    ((opline-1)->opcode == ZEND_IS_EQUAL ||
		     (opline-1)->opcode == ZEND_IS_NOT_EQUAL ||
		     (opline-1)->opcode == ZEND_IS_SMALLER ||
		     (opline-1)->opcode == ZEND_IS_SMALLER_OR_EQUAL) &&
		    opline->op1.var == (opline-1)->result.var) {
			int  var1 = -1;
			int  var2 = -1;
			zend_long val1 = 0;
			zend_long val2 = 0;
//			long val = 0;

			if ((opline-1)->op1_type == IS_CV) {
				var1 = EX_VAR_TO_NUM((opline-1)->op1.var);
			} else if ((opline-1)->op1_type == IS_TMP_VAR) {
				var1 = find_adjusted_tmp_var(
					op_array, build_flags, opline, (opline-1)->op1.var, &val2);
			}

			if ((opline-1)->op2_type == IS_CV) {
				var2 = EX_VAR_TO_NUM((opline-1)->op2.var);
			} else if ((opline-1)->op2_type == IS_TMP_VAR) {
				var2 = find_adjusted_tmp_var(
					op_array, build_flags, opline, (opline-1)->op2.var, &val1);
			}

			if (var1 >= 0 && var2 >= 0) {
				if (!sub_will_overflow(val1, val2) && !sub_will_overflow(val2, val1)) {
					zend_long tmp = val1;
					val1 -= val2;
					val2 -= tmp;
				} else {
					var1 = -1;
					var2 = -1;
				}
			} else if (var1 >= 0 && var2 < 0) {
				zend_long add_val2 = 0;
				if ((opline-1)->op2_type == IS_CONST) {
					zval *zv = CRT_CONSTANT_EX(op_array, (opline-1), (opline-1)->op2, (build_flags & ZEND_RT_CONSTANTS));

					if (Z_TYPE_P(zv) == IS_LONG) {
						add_val2 = Z_LVAL_P(zv);
					} else if (Z_TYPE_P(zv) == IS_FALSE) {
						add_val2 = 0;
					} else if (Z_TYPE_P(zv) == IS_TRUE) {
						add_val2 = 1;
					} else {
						var1 = -1;
					}
				} else {
					var1 = -1;
				}
				if (!add_will_overflow(val2, add_val2)) {
					val2 += add_val2;
				} else {
					var1 = -1;
				}
			} else if (var1 < 0 && var2 >= 0) {
				zend_long add_val1 = 0;
				if ((opline-1)->op1_type == IS_CONST) {
					zval *zv = CRT_CONSTANT_EX(op_array, (opline-1), (opline-1)->op1, (build_flags & ZEND_RT_CONSTANTS));
					if (Z_TYPE_P(zv) == IS_LONG) {
						add_val1 = Z_LVAL_P(CRT_CONSTANT_EX(op_array, (opline-1), (opline-1)->op1, (build_flags & ZEND_RT_CONSTANTS)));
					} else if (Z_TYPE_P(zv) == IS_FALSE) {
						add_val1 = 0;
					} else if (Z_TYPE_P(zv) == IS_TRUE) {
						add_val1 = 1;
					} else {
						var2 = -1;
					}
				} else {
					var2 = -1;
				}
				if (!add_will_overflow(val1, add_val1)) {
					val1 += add_val1;
				} else {
					var2 = -1;
				}
			}

			if (var1 >= 0) {
				if ((opline-1)->opcode == ZEND_IS_EQUAL) {
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var1))) {
						pi_range_equals(pi, var2, val2);
					}
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var1))) {
						pi_range_not_equals(pi, var2, val2);
					}
				} else if ((opline-1)->opcode == ZEND_IS_NOT_EQUAL) {
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var1))) {
						pi_range_equals(pi, var2, val2);
					}
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var1))) {
						pi_range_not_equals(pi, var2, val2);
					}
				} else if ((opline-1)->opcode == ZEND_IS_SMALLER) {
					if (val2 > ZEND_LONG_MIN) {
						if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var1))) {
							pi_range_max(pi, var2, val2-1);
						}
					}
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var1))) {
						pi_range_min(pi, var2, val2);
					}
				} else if ((opline-1)->opcode == ZEND_IS_SMALLER_OR_EQUAL) {
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var1))) {
						pi_range_max(pi, var2, val2);
					}
					if (val2 < ZEND_LONG_MAX) {
						if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var1))) {
							pi_range_min(pi, var2, val2+1);
						}
					}
				}
			}
			if (var2 >= 0) {
				if((opline-1)->opcode == ZEND_IS_EQUAL) {
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var2))) {
						pi_range_equals(pi, var1, val1);
					}
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var2))) {
						pi_range_not_equals(pi, var1, val1);
					}
				} else if ((opline-1)->opcode == ZEND_IS_NOT_EQUAL) {
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var2))) {
						pi_range_equals(pi, var1, val1);
					}
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var2))) {
						pi_range_not_equals(pi, var1, val1);
					}
				} else if ((opline-1)->opcode == ZEND_IS_SMALLER) {
					if (val1 < ZEND_LONG_MAX) {
						if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var2))) {
							pi_range_min(pi, var1, val1+1);
						}
					}
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var2))) {
						pi_range_max(pi, var1, val1);
					}
				} else if ((opline-1)->opcode == ZEND_IS_SMALLER_OR_EQUAL) {
					if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var2))) {
						pi_range_min(pi, var1, val1);
					}
					if (val1 > ZEND_LONG_MIN) {
						if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var2))) {
							pi_range_max(pi, var1, val1-1);
						}
					}
				}
			}
		} else if (opline->op1_type == IS_TMP_VAR &&
		           ((opline-1)->opcode == ZEND_POST_INC ||
		            (opline-1)->opcode == ZEND_POST_DEC) &&
		           opline->op1.var == (opline-1)->result.var &&
		           (opline-1)->op1_type == IS_CV) {
			int var = EX_VAR_TO_NUM((opline-1)->op1.var);

			if ((opline-1)->opcode == ZEND_POST_DEC) {
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var))) {
					pi_range_equals(pi, -1, -1);
				}
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var))) {
					pi_range_not_equals(pi, -1, -1);
				}
			} else if ((opline-1)->opcode == ZEND_POST_INC) {
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var))) {
					pi_range_equals(pi, -1, 1);
				}
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var))) {
					pi_range_not_equals(pi, -1, 1);
				}
			}
		} else if (opline->op1_type == IS_VAR &&
		           ((opline-1)->opcode == ZEND_PRE_INC ||
		            (opline-1)->opcode == ZEND_PRE_DEC) &&
		           opline->op1.var == (opline-1)->result.var &&
		           (opline-1)->op1_type == IS_CV) {
			int var = EX_VAR_TO_NUM((opline-1)->op1.var);

			if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var))) {
				pi_range_equals(pi, -1, 0);
			}
			/* speculative */
			if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var))) {
				pi_range_not_equals(pi, -1, 0);
			}
		} else if (opline->op1_type == IS_TMP_VAR && (opline-1)->opcode == ZEND_TYPE_CHECK &&
				   opline->op1.var == (opline-1)->result.var && (opline-1)->op1_type == IS_CV) {
			int var = EX_VAR_TO_NUM((opline-1)->op1.var);
			uint32_t type = (opline-1)->extended_value;
			if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var))) {
				pi_type_mask(pi, mask_for_type_check(type));
			}
			if (type != IS_RESOURCE) {
				/* is_resource() may return false for closed resources */
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var))) {
					pi_not_type_mask(pi, mask_for_type_check(type));
				}
			}
		} else if (opline->op1_type == IS_TMP_VAR &&
				   ((opline-1)->opcode == ZEND_IS_IDENTICAL
					|| (opline-1)->opcode == ZEND_IS_NOT_IDENTICAL) &&
				   opline->op1.var == (opline-1)->result.var) {
			int var;
			zval *val;
			uint32_t type_mask;
			if ((opline-1)->op1_type == IS_CV && (opline-1)->op2_type == IS_CONST) {
				var = EX_VAR_TO_NUM((opline-1)->op1.var);
				val = CRT_CONSTANT_EX(op_array, (opline-1), (opline-1)->op2, (build_flags & ZEND_RT_CONSTANTS));
			} else if ((opline-1)->op1_type == IS_CONST && (opline-1)->op2_type == IS_CV) {
				var = EX_VAR_TO_NUM((opline-1)->op2.var);
				val = CRT_CONSTANT_EX(op_array, (opline-1), (opline-1)->op1, (build_flags & ZEND_RT_CONSTANTS));
			} else {
				continue;
			}

			/* We're interested in === null/true/false comparisons here, because they eliminate
			 * a type in the false-branch. Other === VAL comparisons are unlikely to be useful. */
			if (Z_TYPE_P(val) != IS_NULL && Z_TYPE_P(val) != IS_TRUE && Z_TYPE_P(val) != IS_FALSE) {
				continue;
			}

			type_mask = _const_op_type(val);
			if ((opline-1)->opcode == ZEND_IS_IDENTICAL) {
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var))) {
					pi_type_mask(pi, type_mask);
				}
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var))) {
					pi_not_type_mask(pi, type_mask);
				}
			} else {
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bf, var))) {
					pi_type_mask(pi, type_mask);
				}
				if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var))) {
					pi_not_type_mask(pi, type_mask);
				}
			}
		} else if (opline->op1_type == IS_TMP_VAR && (opline-1)->opcode == ZEND_INSTANCEOF &&
				   opline->op1.var == (opline-1)->result.var && (opline-1)->op1_type == IS_CV &&
				   (opline-1)->op2_type == IS_CONST) {
			int var = EX_VAR_TO_NUM((opline-1)->op1.var);
			zend_string *lcname = Z_STR_P(CRT_CONSTANT_EX(op_array, (opline-1), (opline-1)->op2, (build_flags & ZEND_RT_CONSTANTS)) + 1);
			zend_class_entry *ce = script ? zend_hash_find_ptr(&script->class_table, lcname) : NULL;
			if (!ce) {
				ce = zend_hash_find_ptr(CG(class_table), lcname);
				if (!ce || ce->type != ZEND_INTERNAL_CLASS) {
					continue;
				}
			}

			if ((pi = add_pi(arena, op_array, dfg, ssa, j, bt, var))) {
				pi_type_mask(pi, MAY_BE_OBJECT);
				pi->constraint.type.ce = ce;
			}
		}
	}
}