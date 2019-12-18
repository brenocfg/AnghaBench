#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_uchar ;
struct TYPE_16__ {int last; int fn_flags; int /*<<< orphan*/  arg_info; TYPE_4__* opcodes; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_15__ {scalar_t__ var; } ;
struct TYPE_14__ {scalar_t__ var; void* constant; } ;
struct TYPE_17__ {scalar_t__ op1_type; int opcode; scalar_t__ op2_type; TYPE_2__ op2; TYPE_1__ op1; int /*<<< orphan*/  extended_value; } ;
typedef  TYPE_4__ zend_op ;
struct TYPE_18__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ zend_arg_info ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 void* IS_CONST ; 
 int /*<<< orphan*/  IS_STRING ; 
 int /*<<< orphan*/  MAKE_NOP (TYPE_4__*) ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
#define  ZEND_ASSIGN_DIM 146 
#define  ZEND_CASE 145 
#define  ZEND_FETCH_DIM_FUNC_ARG 144 
#define  ZEND_FETCH_DIM_RW 143 
#define  ZEND_FETCH_DIM_UNSET 142 
#define  ZEND_FETCH_DIM_W 141 
#define  ZEND_FETCH_LIST_R 140 
#define  ZEND_FETCH_LIST_W 139 
 int ZEND_FREE ; 
 int /*<<< orphan*/  ZEND_FREE_ON_RETURN ; 
 int /*<<< orphan*/  ZEND_FREE_SWITCH ; 
 int const ZEND_IS_EQUAL ; 
 int ZEND_RETURN ; 
#define  ZEND_RETURN_BY_REF 138 
#define  ZEND_SEND_FUNC_ARG 137 
#define  ZEND_SEND_USER 136 
 void* ZEND_SEND_VAL ; 
 void* ZEND_SEND_VAL_EX ; 
#define  ZEND_SEND_VAR 135 
#define  ZEND_SEND_VAR_EX 134 
#define  ZEND_SEND_VAR_NO_REF 133 
#define  ZEND_SEND_VAR_NO_REF_EX 132 
#define  ZEND_SEPARATE 131 
#define  ZEND_SWITCH_LONG 130 
#define  ZEND_SWITCH_STRING 129 
 int /*<<< orphan*/  ZEND_TYPE_CONTAINS_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ZEND_VERIFY_RETURN_TYPE 128 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 void* zend_optimizer_add_literal (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int zend_optimizer_update_op1_const (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int zend_optimizer_update_op2_const (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_hash_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

int zend_optimizer_replace_by_const(zend_op_array *op_array,
                                    zend_op       *opline,
                                    zend_uchar     type,
                                    uint32_t       var,
                                    zval          *val)
{
	zend_op *end = op_array->opcodes + op_array->last;

	while (opline < end) {
		if (opline->op1_type == type &&
			opline->op1.var == var) {
			switch (opline->opcode) {
				case ZEND_FETCH_DIM_W:
				case ZEND_FETCH_DIM_RW:
				case ZEND_FETCH_DIM_FUNC_ARG:
				case ZEND_FETCH_DIM_UNSET:
				case ZEND_FETCH_LIST_W:
				case ZEND_ASSIGN_DIM:
				case ZEND_SEPARATE:
				case ZEND_RETURN_BY_REF:
					return 0;
				case ZEND_SEND_VAR:
					opline->extended_value = 0;
					opline->opcode = ZEND_SEND_VAL;
					break;
				case ZEND_SEND_VAR_EX:
				case ZEND_SEND_FUNC_ARG:
					opline->extended_value = 0;
					opline->opcode = ZEND_SEND_VAL_EX;
					break;
				case ZEND_SEND_VAR_NO_REF:
					return 0;
				case ZEND_SEND_VAR_NO_REF_EX:
					opline->opcode = ZEND_SEND_VAL;
					break;
				case ZEND_SEND_USER:
					opline->opcode = ZEND_SEND_VAL_EX;
					break;
				/* In most cases IS_TMP_VAR operand may be used only once.
				 * The operands are usually destroyed by the opcode handler.
				 * ZEND_CASE and ZEND_FETCH_LIST_R are exceptions, they keeps operand
				 * unchanged, and allows its reuse. these instructions
				 * usually terminated by ZEND_FREE that finally kills the value.
				 */
				case ZEND_FETCH_LIST_R: {
					zend_op *m = opline;

					do {
						if (m->opcode == ZEND_FETCH_LIST_R &&
							m->op1_type == type &&
							m->op1.var == var) {
							zval v;
							ZVAL_COPY(&v, val);
							if (Z_TYPE(v) == IS_STRING) {
								zend_string_hash_val(Z_STR(v));
							}
							m->op1.constant = zend_optimizer_add_literal(op_array, &v);
							m->op1_type = IS_CONST;
						}
						m++;
					} while (m->opcode != ZEND_FREE || m->op1_type != type || m->op1.var != var);

					ZEND_ASSERT(m->opcode == ZEND_FREE && m->op1_type == type && m->op1.var == var);
					MAKE_NOP(m);
					zval_ptr_dtor_nogc(val);
					return 1;
				}
				case ZEND_SWITCH_LONG:
				case ZEND_SWITCH_STRING:
				case ZEND_CASE: {
					zend_op *end = op_array->opcodes + op_array->last;
					while (opline < end) {
						if (opline->op1_type == type && opline->op1.var == var) {
							if (opline->opcode == ZEND_CASE
									|| opline->opcode == ZEND_SWITCH_LONG
									|| opline->opcode == ZEND_SWITCH_STRING) {
								zval v;

								if (opline->opcode == ZEND_CASE) {
									opline->opcode = ZEND_IS_EQUAL;
								}
								ZVAL_COPY(&v, val);
								if (Z_TYPE(v) == IS_STRING) {
									zend_string_hash_val(Z_STR(v));
								}
								opline->op1.constant = zend_optimizer_add_literal(op_array, &v);
								opline->op1_type = IS_CONST;
							} else if (opline->opcode == ZEND_FREE) {
								if (opline->extended_value == ZEND_FREE_SWITCH) {
									/* We found the end of the switch. */
									MAKE_NOP(opline);
									break;
								}

								ZEND_ASSERT(opline->extended_value == ZEND_FREE_ON_RETURN);
								MAKE_NOP(opline);
							} else {
								ZEND_ASSERT(0);
							}
						}
						opline++;
					}
					zval_ptr_dtor_nogc(val);
					return 1;
				}
				case ZEND_VERIFY_RETURN_TYPE: {
					zend_arg_info *ret_info = op_array->arg_info - 1;
					if (!ZEND_TYPE_CONTAINS_CODE(ret_info->type, Z_TYPE_P(val))
						|| (op_array->fn_flags & ZEND_ACC_RETURN_REFERENCE)) {
						return 0;
					}
					MAKE_NOP(opline);

					/* zend_handle_loops_and_finally may inserts other oplines */
					do {
						++opline;
					} while (opline->opcode != ZEND_RETURN && opline->opcode != ZEND_RETURN_BY_REF);
					ZEND_ASSERT(opline->op1.var == var);

					break;
				  }
				default:
					break;
			}
			return zend_optimizer_update_op1_const(op_array, opline, val);
		}

		if (opline->op2_type == type &&
			opline->op2.var == var) {
			return zend_optimizer_update_op2_const(op_array, opline, val);
		}
		opline++;
	}

	return 1;
}