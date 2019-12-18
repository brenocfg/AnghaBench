#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int op1_def; } ;
typedef  TYPE_1__ zend_ssa_op ;
struct TYPE_8__ {int fn_flags; } ;
typedef  TYPE_2__ zend_op_array ;
struct TYPE_9__ {int opcode; int extended_value; } ;
typedef  TYPE_3__ zend_op ;
typedef  int zend_bool ;

/* Variables and functions */
 int ZEND_ACC_RETURN_REFERENCE ; 
#define  ZEND_ADD_ARRAY_ELEMENT 174 
 int ZEND_ARRAY_ELEMENT_REF ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
#define  ZEND_ASSIGN 173 
#define  ZEND_ASSIGN_DIM 172 
#define  ZEND_ASSIGN_DIM_OP 171 
#define  ZEND_ASSIGN_OBJ 170 
#define  ZEND_ASSIGN_OBJ_OP 169 
#define  ZEND_ASSIGN_OBJ_REF 168 
#define  ZEND_ASSIGN_OP 167 
#define  ZEND_ASSIGN_REF 166 
#define  ZEND_ASSIGN_STATIC_PROP_OP 165 
 int const ZEND_ASSIGN_STATIC_PROP_REF ; 
#define  ZEND_BIND_GLOBAL 164 
#define  ZEND_BIND_STATIC 163 
#define  ZEND_FETCH_DIM_FUNC_ARG 162 
#define  ZEND_FETCH_DIM_RW 161 
#define  ZEND_FETCH_DIM_UNSET 160 
#define  ZEND_FETCH_DIM_W 159 
#define  ZEND_FETCH_LIST_W 158 
#define  ZEND_FETCH_OBJ_FUNC_ARG 157 
#define  ZEND_FETCH_OBJ_RW 156 
#define  ZEND_FETCH_OBJ_UNSET 155 
#define  ZEND_FETCH_OBJ_W 154 
#define  ZEND_FE_RESET_RW 153 
#define  ZEND_INIT_ARRAY 152 
#define  ZEND_ISSET_ISEMPTY_CV 151 
#define  ZEND_MAKE_REF 150 
#define  ZEND_OP_DATA 149 
#define  ZEND_POST_DEC 148 
#define  ZEND_POST_DEC_OBJ 147 
#define  ZEND_POST_INC 146 
#define  ZEND_POST_INC_OBJ 145 
#define  ZEND_PRE_DEC 144 
#define  ZEND_PRE_DEC_OBJ 143 
#define  ZEND_PRE_INC 142 
#define  ZEND_PRE_INC_OBJ 141 
#define  ZEND_ROPE_ADD 140 
#define  ZEND_ROPE_END 139 
#define  ZEND_SEND_ARRAY 138 
#define  ZEND_SEND_FUNC_ARG 137 
#define  ZEND_SEND_REF 136 
#define  ZEND_SEND_UNPACK 135 
#define  ZEND_SEND_USER 134 
#define  ZEND_SEND_VAR_EX 133 
#define  ZEND_UNSET_CV 132 
#define  ZEND_UNSET_DIM 131 
#define  ZEND_UNSET_OBJ 130 
#define  ZEND_VERIFY_RETURN_TYPE 129 
#define  ZEND_YIELD 128 

__attribute__((used)) static zend_bool can_replace_op1(
		const zend_op_array *op_array, zend_op *opline, zend_ssa_op *ssa_op) {
	switch (opline->opcode) {
		case ZEND_PRE_INC:
		case ZEND_PRE_DEC:
		case ZEND_PRE_INC_OBJ:
		case ZEND_PRE_DEC_OBJ:
		case ZEND_POST_INC:
		case ZEND_POST_DEC:
		case ZEND_POST_INC_OBJ:
		case ZEND_POST_DEC_OBJ:
		case ZEND_ASSIGN:
		case ZEND_ASSIGN_REF:
		case ZEND_ASSIGN_DIM:
		case ZEND_ASSIGN_OBJ:
		case ZEND_ASSIGN_OBJ_REF:
		case ZEND_ASSIGN_OP:
		case ZEND_ASSIGN_DIM_OP:
		case ZEND_ASSIGN_OBJ_OP:
		case ZEND_ASSIGN_STATIC_PROP_OP:
		case ZEND_FETCH_DIM_W:
		case ZEND_FETCH_DIM_RW:
		case ZEND_FETCH_DIM_UNSET:
		case ZEND_FETCH_DIM_FUNC_ARG:
		case ZEND_FETCH_OBJ_W:
		case ZEND_FETCH_OBJ_RW:
		case ZEND_FETCH_OBJ_UNSET:
		case ZEND_FETCH_OBJ_FUNC_ARG:
		case ZEND_FETCH_LIST_W:
		case ZEND_UNSET_DIM:
		case ZEND_UNSET_OBJ:
		case ZEND_SEND_REF:
		case ZEND_SEND_VAR_EX:
		case ZEND_SEND_FUNC_ARG:
		case ZEND_SEND_UNPACK:
		case ZEND_SEND_ARRAY:
		case ZEND_SEND_USER:
		case ZEND_FE_RESET_RW:
			return 0;
		/* Do not accept CONST */
		case ZEND_ROPE_ADD:
		case ZEND_ROPE_END:
		case ZEND_BIND_STATIC:
		case ZEND_BIND_GLOBAL:
		case ZEND_MAKE_REF:
		case ZEND_UNSET_CV:
		case ZEND_ISSET_ISEMPTY_CV:
			return 0;
		case ZEND_INIT_ARRAY:
		case ZEND_ADD_ARRAY_ELEMENT:
			return !(opline->extended_value & ZEND_ARRAY_ELEMENT_REF);
		case ZEND_YIELD:
			return !(op_array->fn_flags & ZEND_ACC_RETURN_REFERENCE);
		case ZEND_VERIFY_RETURN_TYPE:
			// TODO: This would require a non-local change ???
			return 0;
		case ZEND_OP_DATA:
			return (opline - 1)->opcode != ZEND_ASSIGN_OBJ_REF &&
				(opline - 1)->opcode != ZEND_ASSIGN_STATIC_PROP_REF;
		default:
			if (ssa_op->op1_def != -1) {
				ZEND_ASSERT(0);
				return 0;
			}
	}

	return 1;
}