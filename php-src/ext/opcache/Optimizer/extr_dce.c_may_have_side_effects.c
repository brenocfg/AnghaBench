#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_14__ {size_t op1_def; size_t op2_use; int /*<<< orphan*/  op1_use; } ;
typedef  TYPE_3__ zend_ssa_op ;
struct TYPE_15__ {TYPE_1__* vars; } ;
typedef  TYPE_4__ zend_ssa ;
struct TYPE_16__ {TYPE_2__* static_variables; } ;
typedef  TYPE_5__ zend_op_array ;
struct TYPE_17__ {int opcode; int extended_value; int /*<<< orphan*/  op1_type; int /*<<< orphan*/  op2_type; } ;
typedef  TYPE_6__ zend_op ;
typedef  int zend_bool ;
typedef  int uint32_t ;
struct TYPE_13__ {scalar_t__ arData; } ;
struct TYPE_12__ {int /*<<< orphan*/  escape_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESCAPE_STATE_NO_ESCAPE ; 
 int /*<<< orphan*/  IS_CONST ; 
 int /*<<< orphan*/  IS_CONSTANT_AST ; 
 int MAY_BE_REF ; 
 int MAY_BE_UNDEF ; 
 int MAY_HAVE_DTOR ; 
 int OP1_INFO () ; 
 int OP2_INFO () ; 
#define  ZEND_ADD 219 
#define  ZEND_ADD_ARRAY_ELEMENT 218 
#define  ZEND_ASSERT_CHECK 217 
#define  ZEND_ASSIGN 216 
#define  ZEND_ASSIGN_DIM 215 
#define  ZEND_ASSIGN_OBJ 214 
#define  ZEND_ASSIGN_OP 213 
#define  ZEND_ASSIGN_REF 212 
#define  ZEND_BEGIN_SILENCE 211 
 int ZEND_BIND_REF ; 
#define  ZEND_BIND_STATIC 210 
#define  ZEND_BOOL 209 
#define  ZEND_BOOL_NOT 208 
#define  ZEND_BOOL_XOR 207 
#define  ZEND_BW_AND 206 
#define  ZEND_BW_NOT 205 
#define  ZEND_BW_OR 204 
#define  ZEND_BW_XOR 203 
#define  ZEND_CASE 202 
#define  ZEND_CAST 201 
#define  ZEND_CHECK_VAR 200 
#define  ZEND_COALESCE 199 
#define  ZEND_CONCAT 198 
#define  ZEND_COUNT 197 
#define  ZEND_DEFINED 196 
#define  ZEND_DIV 195 
#define  ZEND_DO_FCALL 194 
#define  ZEND_DO_FCALL_BY_NAME 193 
#define  ZEND_DO_ICALL 192 
#define  ZEND_DO_UCALL 191 
#define  ZEND_ECHO 190 
#define  ZEND_END_SILENCE 189 
#define  ZEND_EXT_FCALL_BEGIN 188 
#define  ZEND_EXT_FCALL_END 187 
#define  ZEND_EXT_NOP 186 
#define  ZEND_EXT_STMT 185 
#define  ZEND_FAST_CONCAT 184 
#define  ZEND_FETCH_DIM_IS 183 
#define  ZEND_FETCH_IS 182 
#define  ZEND_FREE 181 
#define  ZEND_FUNC_GET_ARGS 180 
#define  ZEND_FUNC_NUM_ARGS 179 
#define  ZEND_GET_TYPE 178 
#define  ZEND_INCLUDE_OR_EVAL 177 
#define  ZEND_INIT_ARRAY 176 
#define  ZEND_IN_ARRAY 175 
#define  ZEND_ISSET_ISEMPTY_CV 174 
#define  ZEND_ISSET_ISEMPTY_DIM_OBJ 173 
#define  ZEND_ISSET_ISEMPTY_THIS 172 
#define  ZEND_ISSET_ISEMPTY_VAR 171 
#define  ZEND_IS_EQUAL 170 
#define  ZEND_IS_IDENTICAL 169 
#define  ZEND_IS_NOT_EQUAL 168 
#define  ZEND_IS_NOT_IDENTICAL 167 
#define  ZEND_IS_SMALLER 166 
#define  ZEND_IS_SMALLER_OR_EQUAL 165 
#define  ZEND_JMP 164 
#define  ZEND_JMPNZ 163 
#define  ZEND_JMPNZ_EX 162 
#define  ZEND_JMPZ 161 
#define  ZEND_JMPZNZ 160 
#define  ZEND_JMPZ_EX 159 
#define  ZEND_JMP_SET 158 
#define  ZEND_MOD 157 
#define  ZEND_MUL 156 
#define  ZEND_NOP 155 
#define  ZEND_POST_DEC 154 
#define  ZEND_POST_DEC_OBJ 153 
#define  ZEND_POST_INC 152 
#define  ZEND_POST_INC_OBJ 151 
#define  ZEND_POW 150 
#define  ZEND_PRE_DEC 149 
#define  ZEND_PRE_DEC_OBJ 148 
#define  ZEND_PRE_INC 147 
#define  ZEND_PRE_INC_OBJ 146 
#define  ZEND_QM_ASSIGN 145 
#define  ZEND_RECV 144 
#define  ZEND_RECV_INIT 143 
#define  ZEND_ROPE_ADD 142 
#define  ZEND_ROPE_END 141 
#define  ZEND_ROPE_INIT 140 
#define  ZEND_SL 139 
#define  ZEND_SPACESHIP 138 
#define  ZEND_SR 137 
#define  ZEND_STRLEN 136 
#define  ZEND_SUB 135 
#define  ZEND_THROW 134 
#define  ZEND_TICKS 133 
#define  ZEND_TYPE_CHECK 132 
#define  ZEND_UNSET_CV 131 
#define  ZEND_UNSET_VAR 130 
#define  ZEND_YIELD 129 
#define  ZEND_YIELD_FROM 128 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int is_bad_mod (TYPE_4__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline zend_bool may_have_side_effects(
		zend_op_array *op_array, zend_ssa *ssa,
		const zend_op *opline, const zend_ssa_op *ssa_op,
		zend_bool reorder_dtor_effects) {
	switch (opline->opcode) {
		case ZEND_NOP:
		case ZEND_IS_IDENTICAL:
		case ZEND_IS_NOT_IDENTICAL:
		case ZEND_QM_ASSIGN:
		case ZEND_FREE:
		case ZEND_TYPE_CHECK:
		case ZEND_DEFINED:
		case ZEND_ADD:
		case ZEND_SUB:
		case ZEND_MUL:
		case ZEND_POW:
		case ZEND_BW_OR:
		case ZEND_BW_AND:
		case ZEND_BW_XOR:
		case ZEND_CONCAT:
		case ZEND_FAST_CONCAT:
		case ZEND_DIV:
		case ZEND_MOD:
		case ZEND_BOOL_XOR:
		case ZEND_BOOL:
		case ZEND_BOOL_NOT:
		case ZEND_BW_NOT:
		case ZEND_SL:
		case ZEND_SR:
		case ZEND_IS_EQUAL:
		case ZEND_IS_NOT_EQUAL:
		case ZEND_IS_SMALLER:
		case ZEND_IS_SMALLER_OR_EQUAL:
		case ZEND_CASE:
		case ZEND_CAST:
		case ZEND_ROPE_INIT:
		case ZEND_ROPE_ADD:
		case ZEND_INIT_ARRAY:
		case ZEND_ADD_ARRAY_ELEMENT:
		case ZEND_SPACESHIP:
		case ZEND_STRLEN:
		case ZEND_COUNT:
		case ZEND_GET_TYPE:
		case ZEND_ISSET_ISEMPTY_THIS:
		case ZEND_ISSET_ISEMPTY_DIM_OBJ:
		case ZEND_FETCH_DIM_IS:
		case ZEND_ISSET_ISEMPTY_CV:
		case ZEND_ISSET_ISEMPTY_VAR:
		case ZEND_FETCH_IS:
		case ZEND_IN_ARRAY:
		case ZEND_FUNC_NUM_ARGS:
		case ZEND_FUNC_GET_ARGS:
			/* No side effects */
			return 0;
		case ZEND_ROPE_END:
			/* TODO: Rope dce optimization, see #76446 */
			return 1;
		case ZEND_JMP:
		case ZEND_JMPZ:
		case ZEND_JMPNZ:
		case ZEND_JMPZNZ:
		case ZEND_JMPZ_EX:
		case ZEND_JMPNZ_EX:
		case ZEND_JMP_SET:
		case ZEND_COALESCE:
		case ZEND_ASSERT_CHECK:
			/* For our purposes a jumps and branches are side effects. */
			return 1;
		case ZEND_BEGIN_SILENCE:
		case ZEND_END_SILENCE:
		case ZEND_ECHO:
		case ZEND_INCLUDE_OR_EVAL:
		case ZEND_THROW:
		case ZEND_EXT_STMT:
		case ZEND_EXT_FCALL_BEGIN:
		case ZEND_EXT_FCALL_END:
		case ZEND_EXT_NOP:
		case ZEND_TICKS:
		case ZEND_YIELD:
		case ZEND_YIELD_FROM:
			/* Intrinsic side effects */
			return 1;
		case ZEND_DO_FCALL:
		case ZEND_DO_FCALL_BY_NAME:
		case ZEND_DO_ICALL:
		case ZEND_DO_UCALL:
			/* For now assume all calls have side effects */
			return 1;
		case ZEND_RECV:
		case ZEND_RECV_INIT:
			/* Even though RECV_INIT can be side-effect free, these cannot be simply dropped
			 * due to the prologue skipping code. */
			return 1;
		case ZEND_ASSIGN_REF:
			return 1;
		case ZEND_ASSIGN:
		{
			if (is_bad_mod(ssa, ssa_op->op1_use, ssa_op->op1_def)) {
				return 1;
			}
			if (!reorder_dtor_effects) {
				if (opline->op2_type != IS_CONST
					&& (OP2_INFO() & MAY_HAVE_DTOR)
					&& ssa->vars[ssa_op->op2_use].escape_state != ESCAPE_STATE_NO_ESCAPE) {
					/* DCE might shorten lifetime */
					return 1;
				}
			}
			return 0;
		}
		case ZEND_UNSET_VAR:
			return 1;
		case ZEND_UNSET_CV:
		{
			uint32_t t1 = OP1_INFO();
			if (t1 & MAY_BE_REF) {
				/* We don't consider uses as the LHS of an assignment as real uses during DCE, so
				 * an unset may be considered dead even if there is a later assignment to the
				 * variable. Removing the unset in this case would not be correct if the variable
				 * is a reference, because unset breaks references. */
				return 1;
			}
			return 0;
		}
		case ZEND_PRE_INC:
		case ZEND_POST_INC:
		case ZEND_PRE_DEC:
		case ZEND_POST_DEC:
			return is_bad_mod(ssa, ssa_op->op1_use, ssa_op->op1_def);
		case ZEND_ASSIGN_OP:
			return is_bad_mod(ssa, ssa_op->op1_use, ssa_op->op1_def)
				|| ssa->vars[ssa_op->op1_def].escape_state != ESCAPE_STATE_NO_ESCAPE;
		case ZEND_ASSIGN_DIM:
		case ZEND_ASSIGN_OBJ:
			if (is_bad_mod(ssa, ssa_op->op1_use, ssa_op->op1_def)
				|| ssa->vars[ssa_op->op1_def].escape_state != ESCAPE_STATE_NO_ESCAPE) {
				return 1;
			}
			if (!reorder_dtor_effects) {
				opline++;
				ssa_op++;
				if (opline->op1_type != IS_CONST
					&& (OP1_INFO() & MAY_HAVE_DTOR)) {
					/* DCE might shorten lifetime */
					return 1;
				}
			}
			return 0;
		case ZEND_PRE_INC_OBJ:
		case ZEND_PRE_DEC_OBJ:
		case ZEND_POST_INC_OBJ:
		case ZEND_POST_DEC_OBJ:
			if (is_bad_mod(ssa, ssa_op->op1_use, ssa_op->op1_def)
				|| ssa->vars[ssa_op->op1_def].escape_state != ESCAPE_STATE_NO_ESCAPE) {
				return 1;
			}
			return 0;
		case ZEND_BIND_STATIC:
			if (op_array->static_variables
			 && (opline->extended_value & ZEND_BIND_REF) != 0) {
				zval *value =
					(zval*)((char*)op_array->static_variables->arData +
						(opline->extended_value & ~ZEND_BIND_REF));
				if (Z_TYPE_P(value) == IS_CONSTANT_AST) {
					/* AST may contain undefined constants */
					return 1;
				}
			}
			return 0;
		case ZEND_CHECK_VAR:
			return (OP1_INFO() & MAY_BE_UNDEF) != 0;
		default:
			/* For everything we didn't handle, assume a side-effect */
			return 1;
	}
}