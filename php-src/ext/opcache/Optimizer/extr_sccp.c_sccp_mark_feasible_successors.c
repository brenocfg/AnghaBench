#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_ssa_op ;
struct TYPE_14__ {int* map; } ;
struct TYPE_15__ {TYPE_2__ cfg; } ;
typedef  TYPE_3__ zend_ssa ;
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_13__ {int /*<<< orphan*/  constant; } ;
struct TYPE_16__ {int opcode; int /*<<< orphan*/  extended_value; TYPE_1__ op2; } ;
typedef  TYPE_4__ zend_op ;
struct TYPE_17__ {int* successors; int successors_count; } ;
typedef  TYPE_5__ zend_basic_block ;
struct TYPE_18__ {TYPE_3__* ssa; int /*<<< orphan*/ * op_array; } ;
typedef  TYPE_6__ scdf_ctx ;
typedef  int /*<<< orphan*/  sccp_ctx ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  CT_CONSTANT_EX (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  IS_ARRAY ; 
 scalar_t__ IS_BOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_FALSE ; 
 int /*<<< orphan*/  IS_LONG ; 
 int /*<<< orphan*/  IS_NULL ; 
 int /*<<< orphan*/  IS_PARTIAL_ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_STRING ; 
 scalar_t__ IS_TOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_TRUE ; 
#define  ZEND_ASSERT_CHECK 142 
#define  ZEND_CATCH 141 
#define  ZEND_COALESCE 140 
#define  ZEND_FE_FETCH_R 139 
#define  ZEND_FE_FETCH_RW 138 
#define  ZEND_FE_RESET_R 137 
#define  ZEND_FE_RESET_RW 136 
#define  ZEND_JMPNZ 135 
#define  ZEND_JMPNZ_EX 134 
#define  ZEND_JMPZ 133 
#define  ZEND_JMPZNZ 132 
#define  ZEND_JMPZ_EX 131 
#define  ZEND_JMP_SET 130 
 size_t ZEND_OFFSET_TO_OPLINE_NUM (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
#define  ZEND_SWITCH_LONG 129 
#define  ZEND_SWITCH_STRING 128 
 int /*<<< orphan*/ * Z_ARRVAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ARR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_eval_bool_cast (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_op1_value (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scdf_mark_edge_feasible (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/ * zend_hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_num_elements (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sccp_mark_feasible_successors(
		scdf_ctx *scdf,
		int block_num, zend_basic_block *block,
		zend_op *opline, zend_ssa_op *ssa_op) {
	sccp_ctx *ctx = (sccp_ctx *) scdf;
	zval *op1, zv;
	int s;

	/* We can't determine the branch target at compile-time for these */
	switch (opline->opcode) {
		case ZEND_ASSERT_CHECK:
		case ZEND_CATCH:
		case ZEND_FE_FETCH_R:
		case ZEND_FE_FETCH_RW:
			scdf_mark_edge_feasible(scdf, block_num, block->successors[0]);
			scdf_mark_edge_feasible(scdf, block_num, block->successors[1]);
			return;
	}

	op1 = get_op1_value(ctx, opline, ssa_op);

	/* Branch target can be either one */
	if (!op1 || IS_BOT(op1)) {
		for (s = 0; s < block->successors_count; s++) {
			scdf_mark_edge_feasible(scdf, block_num, block->successors[s]);
		}
		return;
	}

	/* Branch target not yet known */
	if (IS_TOP(op1)) {
		return;
	}

	switch (opline->opcode) {
		case ZEND_JMPZ:
		case ZEND_JMPZNZ:
		case ZEND_JMPZ_EX:
		{
			if (ct_eval_bool_cast(&zv, op1) == FAILURE) {
				scdf_mark_edge_feasible(scdf, block_num, block->successors[0]);
				scdf_mark_edge_feasible(scdf, block_num, block->successors[1]);
				return;
			}
			s = Z_TYPE(zv) == IS_TRUE;
			break;
		}
		case ZEND_JMPNZ:
		case ZEND_JMPNZ_EX:
		case ZEND_JMP_SET:
		{
			if (ct_eval_bool_cast(&zv, op1) == FAILURE) {
				scdf_mark_edge_feasible(scdf, block_num, block->successors[0]);
				scdf_mark_edge_feasible(scdf, block_num, block->successors[1]);
				return;
			}
			s = Z_TYPE(zv) == IS_FALSE;
			break;
		}
		case ZEND_COALESCE:
			s = (Z_TYPE_P(op1) == IS_NULL);
			break;
		case ZEND_FE_RESET_R:
		case ZEND_FE_RESET_RW:
			/* A non-empty partial array is definitely non-empty, but an
			 * empty partial array may be non-empty at runtime. */
			if (Z_TYPE_P(op1) != IS_ARRAY ||
					(IS_PARTIAL_ARRAY(op1) && zend_hash_num_elements(Z_ARR_P(op1)) == 0)) {
				scdf_mark_edge_feasible(scdf, block_num, block->successors[0]);
				scdf_mark_edge_feasible(scdf, block_num, block->successors[1]);
				return;
			}
			s = zend_hash_num_elements(Z_ARR_P(op1)) != 0;
			break;
		case ZEND_SWITCH_LONG:
			if (Z_TYPE_P(op1) == IS_LONG) {
				zend_op_array *op_array = scdf->op_array;
				zend_ssa *ssa = scdf->ssa;
				HashTable *jmptable = Z_ARRVAL_P(CT_CONSTANT_EX(op_array, opline->op2.constant));
				zval *jmp_zv = zend_hash_index_find(jmptable, Z_LVAL_P(op1));
				int target;

				if (jmp_zv) {
					target = ssa->cfg.map[ZEND_OFFSET_TO_OPLINE_NUM(op_array, opline, Z_LVAL_P(jmp_zv))];
				} else {
					target = ssa->cfg.map[ZEND_OFFSET_TO_OPLINE_NUM(op_array, opline, opline->extended_value)];
				}
				scdf_mark_edge_feasible(scdf, block_num, target);
				return;
			}
			s = 0;
			break;
		case ZEND_SWITCH_STRING:
			if (Z_TYPE_P(op1) == IS_STRING) {
				zend_op_array *op_array = scdf->op_array;
				zend_ssa *ssa = scdf->ssa;
				HashTable *jmptable = Z_ARRVAL_P(CT_CONSTANT_EX(op_array, opline->op2.constant));
				zval *jmp_zv = zend_hash_find(jmptable, Z_STR_P(op1));
				int target;

				if (jmp_zv) {
					target = ssa->cfg.map[ZEND_OFFSET_TO_OPLINE_NUM(op_array, opline, Z_LVAL_P(jmp_zv))];
				} else {
					target = ssa->cfg.map[ZEND_OFFSET_TO_OPLINE_NUM(op_array, opline, opline->extended_value)];
				}
				scdf_mark_edge_feasible(scdf, block_num, target);
				return;
			}
			s = 0;
			break;
		default:
			for (s = 0; s < block->successors_count; s++) {
				scdf_mark_edge_feasible(scdf, block_num, block->successors[s]);
			}
			return;
	}
	scdf_mark_edge_feasible(scdf, block_num, block->successors[s]);
}