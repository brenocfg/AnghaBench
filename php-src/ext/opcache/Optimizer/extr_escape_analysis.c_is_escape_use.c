#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int op1_use; size_t op1_def; int op2_use; int result_use; } ;
typedef  TYPE_2__ zend_ssa_op ;
struct TYPE_10__ {TYPE_1__* vars; TYPE_2__* ops; } ;
typedef  TYPE_3__ zend_ssa ;
struct TYPE_11__ {TYPE_5__* opcodes; } ;
typedef  TYPE_4__ zend_op_array ;
struct TYPE_12__ {int opcode; int extended_value; int /*<<< orphan*/  result_type; int /*<<< orphan*/  op2_type; int /*<<< orphan*/  op1_type; } ;
typedef  TYPE_5__ zend_op ;
struct TYPE_8__ {int /*<<< orphan*/  alias; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CV ; 
 int /*<<< orphan*/  IS_UNUSED ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_REF ; 
 int OP1_INFO () ; 
 int OP2_INFO () ; 
#define  ZEND_ADD_ARRAY_ELEMENT 149 
 int ZEND_ARRAY_ELEMENT_REF ; 
#define  ZEND_ASSIGN 148 
#define  ZEND_ASSIGN_DIM 147 
#define  ZEND_ASSIGN_DIM_OP 146 
#define  ZEND_ASSIGN_OBJ 145 
#define  ZEND_ASSIGN_OBJ_OP 144 
#define  ZEND_ASSIGN_OBJ_REF 143 
#define  ZEND_ASSIGN_OP 142 
#define  ZEND_ASSIGN_STATIC_PROP_OP 141 
#define  ZEND_FETCH_DIM_IS 140 
#define  ZEND_FETCH_DIM_R 139 
#define  ZEND_FETCH_OBJ_IS 138 
#define  ZEND_FETCH_OBJ_R 137 
#define  ZEND_INIT_ARRAY 136 
#define  ZEND_ISSET_ISEMPTY_DIM_OBJ 135 
#define  ZEND_ISSET_ISEMPTY_PROP_OBJ 134 
#define  ZEND_OP_DATA 133 
#define  ZEND_POST_DEC_OBJ 132 
#define  ZEND_POST_INC_OBJ 131 
#define  ZEND_PRE_DEC_OBJ 130 
#define  ZEND_PRE_INC_OBJ 129 
#define  ZEND_QM_ASSIGN 128 

__attribute__((used)) static int is_escape_use(zend_op_array *op_array, zend_ssa *ssa, int use, int var) /* {{{ */
{
	zend_ssa_op *op = ssa->ops + use;
	zend_op *opline = op_array->opcodes + use;

	if (op->op1_use == var) {
		switch (opline->opcode) {
			case ZEND_ASSIGN:
				/* no_val */
				break;
			case ZEND_QM_ASSIGN:
				if (opline->op1_type == IS_CV) {
					if (OP1_INFO() & MAY_BE_OBJECT) {
						/* object aliasing */
						return 1;
					}
				}
				break;
			case ZEND_ISSET_ISEMPTY_DIM_OBJ:
			case ZEND_ISSET_ISEMPTY_PROP_OBJ:
			case ZEND_FETCH_DIM_R:
			case ZEND_FETCH_OBJ_R:
			case ZEND_FETCH_DIM_IS:
			case ZEND_FETCH_OBJ_IS:
				break;
			case ZEND_ASSIGN_OP:
				return 1;
			case ZEND_ASSIGN_DIM_OP:
			case ZEND_ASSIGN_OBJ_OP:
			case ZEND_ASSIGN_STATIC_PROP_OP:
			case ZEND_ASSIGN_DIM:
			case ZEND_ASSIGN_OBJ:
			case ZEND_ASSIGN_OBJ_REF:
				break;
			case ZEND_PRE_INC_OBJ:
			case ZEND_PRE_DEC_OBJ:
			case ZEND_POST_INC_OBJ:
			case ZEND_POST_DEC_OBJ:
				break;
			case ZEND_INIT_ARRAY:
			case ZEND_ADD_ARRAY_ELEMENT:
				if (opline->extended_value & ZEND_ARRAY_ELEMENT_REF) {
					return 1;
				}
				if (OP1_INFO() & MAY_BE_OBJECT) {
					/* object aliasing */
					return 1;
				}
				/* reference dependencies processed separately */
				break;
			case ZEND_OP_DATA:
				if ((opline-1)->opcode != ZEND_ASSIGN_DIM
				 && (opline-1)->opcode != ZEND_ASSIGN_OBJ) {
					return 1;
				}
				if (OP1_INFO() & MAY_BE_OBJECT) {
					/* object aliasing */
					return 1;
				}
				opline--;
				op--;
				if (opline->op1_type != IS_CV
				 || (OP1_INFO() & MAY_BE_REF)
				 || (op->op1_def >= 0 && ssa->vars[op->op1_def].alias)) {
					/* asignment into escaping structure */
					return 1;
				}
				/* reference dependencies processed separately */
				break;
			default:
				return 1;
		}
	}

	if (op->op2_use == var) {
		switch (opline->opcode) {
			case ZEND_ASSIGN:
				if (opline->op1_type != IS_CV
				 || (OP1_INFO() & MAY_BE_REF)
				 || (op->op1_def >= 0 && ssa->vars[op->op1_def].alias)) {
					/* asignment into escaping variable */
					return 1;
				}
				if (opline->op2_type == IS_CV || opline->result_type != IS_UNUSED) {
					if (OP2_INFO() & MAY_BE_OBJECT) {
						/* object aliasing */
						return 1;
					}
				}
				break;
			default:
				return 1;
		}
	}

	if (op->result_use == var) {
		switch (opline->opcode) {
			case ZEND_ASSIGN:
			case ZEND_QM_ASSIGN:
			case ZEND_INIT_ARRAY:
			case ZEND_ADD_ARRAY_ELEMENT:
				break;
			default:
				return 1;
		}
	}

	return 0;
}