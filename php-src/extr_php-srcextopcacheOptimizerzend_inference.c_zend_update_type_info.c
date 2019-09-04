#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_62__   TYPE_9__ ;
typedef  struct TYPE_61__   TYPE_8__ ;
typedef  struct TYPE_60__   TYPE_7__ ;
typedef  struct TYPE_59__   TYPE_6__ ;
typedef  struct TYPE_58__   TYPE_5__ ;
typedef  struct TYPE_57__   TYPE_4__ ;
typedef  struct TYPE_56__   TYPE_45__ ;
typedef  struct TYPE_55__   TYPE_3__ ;
typedef  struct TYPE_54__   TYPE_2__ ;
typedef  struct TYPE_53__   TYPE_1__ ;
typedef  struct TYPE_52__   TYPE_16__ ;
typedef  struct TYPE_51__   TYPE_15__ ;
typedef  struct TYPE_50__   TYPE_14__ ;
typedef  struct TYPE_49__   TYPE_13__ ;
typedef  struct TYPE_48__   TYPE_12__ ;
typedef  struct TYPE_47__   TYPE_11__ ;
typedef  struct TYPE_46__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_53__ {int /*<<< orphan*/  max; int /*<<< orphan*/  overflow; int /*<<< orphan*/  min; int /*<<< orphan*/  underflow; } ;
struct TYPE_59__ {int is_instanceof; int type; TYPE_14__* ce; int /*<<< orphan*/  use_as_double; TYPE_1__ range; int /*<<< orphan*/  has_range; } ;
typedef  TYPE_6__ zend_ssa_var_info ;
struct TYPE_60__ {int use_chain; } ;
typedef  TYPE_7__ zend_ssa_var ;
struct TYPE_61__ {scalar_t__ result_def; scalar_t__ op1_def; scalar_t__ op2_def; size_t op1_use; size_t op2_use; size_t result_use; } ;
typedef  TYPE_8__ zend_ssa_op ;
struct TYPE_62__ {int /*<<< orphan*/  rt_constants; TYPE_6__* var_info; TYPE_7__* vars; TYPE_8__* ops; } ;
typedef  TYPE_9__ zend_ssa ;
struct TYPE_46__ {int /*<<< orphan*/  class_table; } ;
typedef  TYPE_10__ zend_script ;
typedef  int /*<<< orphan*/  zend_property_info ;
struct TYPE_47__ {int fn_flags; int num_args; TYPE_16__* arg_info; TYPE_12__* opcodes; TYPE_14__* scope; int /*<<< orphan*/  function_name; } ;
typedef  TYPE_11__ zend_op_array ;
struct TYPE_56__ {int num; } ;
struct TYPE_48__ {int opcode; int op1_type; int extended_value; int op2_type; int result_type; TYPE_45__ op1; TYPE_45__ op2; } ;
typedef  TYPE_12__ zend_op ;
typedef  int zend_long ;
struct TYPE_58__ {int is_instanceof; TYPE_14__* ce; } ;
struct TYPE_49__ {int num_args; TYPE_5__ return_info; TYPE_15__** call_map; TYPE_3__* arg_info; } ;
typedef  TYPE_13__ zend_func_info ;
struct TYPE_50__ {int ce_flags; struct TYPE_50__* parent; } ;
typedef  TYPE_14__ zend_class_entry ;
struct TYPE_51__ {TYPE_4__* callee_func; } ;
typedef  TYPE_15__ zend_call_info ;
typedef  int /*<<< orphan*/  zend_bitset ;
struct TYPE_52__ {int /*<<< orphan*/  pass_by_reference; } ;
typedef  TYPE_16__ zend_arg_info ;
typedef  int uint32_t ;
struct TYPE_57__ {TYPE_11__ const op_array; int /*<<< orphan*/  type; } ;
struct TYPE_54__ {int type; int is_instanceof; TYPE_14__* ce; } ;
struct TYPE_55__ {TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_SSA_OBJ_TYPE (size_t,scalar_t__) ; 
 int /*<<< orphan*/ * CRT_CONSTANT_EX (TYPE_11__ const*,TYPE_12__*,TYPE_45__,int /*<<< orphan*/ ) ; 
 int FUNC_MAY_WARN ; 
 int IS_ARRAY ; 
 int IS_CONST ; 
 int IS_CONSTANT_AST ; 
 int IS_CV ; 
 int IS_OBJECT ; 
 int IS_STRING ; 
 int IS_TMP_VAR ; 
 int IS_UNUSED ; 
 int IS_VAR ; 
 int MAY_BE_ANY ; 
 int MAY_BE_ARRAY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_KEY_LONG ; 
 int MAY_BE_ARRAY_KEY_STRING ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_ARRAY_OF_ARRAY ; 
 int MAY_BE_ARRAY_OF_DOUBLE ; 
 int MAY_BE_ARRAY_OF_LONG ; 
 int MAY_BE_ARRAY_OF_NULL ; 
 int MAY_BE_ARRAY_OF_OBJECT ; 
 int MAY_BE_ARRAY_OF_REF ; 
 int MAY_BE_ARRAY_SHIFT ; 
 int MAY_BE_CLASS ; 
 int MAY_BE_DOUBLE ; 
 int MAY_BE_ERROR ; 
 int MAY_BE_FALSE ; 
 int MAY_BE_LONG ; 
 int MAY_BE_NULL ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_RC1 ; 
 int MAY_BE_RCN ; 
 int MAY_BE_REF ; 
 int MAY_BE_RESOURCE ; 
 int MAY_BE_STRING ; 
 int MAY_BE_TRUE ; 
 int MAY_BE_UNDEF ; 
 int OP1_DATA_INFO () ; 
 int OP1_INFO () ; 
 int OP2_INFO () ; 
 int RES_USE_INFO () ; 
 int /*<<< orphan*/  RETURN_VALUE_USED (TYPE_12__*) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  UPDATE_SSA_OBJ_TYPE (TYPE_14__*,int,scalar_t__) ; 
 int /*<<< orphan*/  UPDATE_SSA_TYPE (int,scalar_t__) ; 
 int ZEND_ACC_LINKED ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
#define  ZEND_ADD 267 
#define  ZEND_ADD_ARRAY_ELEMENT 266 
 int ZEND_ARRAY_ELEMENT_REF ; 
#define  ZEND_ARRAY_KEY_EXISTS 265 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
#define  ZEND_ASSERT_CHECK 264 
#define  ZEND_ASSIGN 263 
#define  ZEND_ASSIGN_ADD 262 
#define  ZEND_ASSIGN_BW_AND 261 
#define  ZEND_ASSIGN_BW_OR 260 
#define  ZEND_ASSIGN_BW_XOR 259 
#define  ZEND_ASSIGN_CONCAT 258 
#define  ZEND_ASSIGN_DIM 257 
#define  ZEND_ASSIGN_DIV 256 
#define  ZEND_ASSIGN_MOD 255 
#define  ZEND_ASSIGN_MUL 254 
#define  ZEND_ASSIGN_OBJ 253 
#define  ZEND_ASSIGN_OBJ_REF 252 
#define  ZEND_ASSIGN_POW 251 
#define  ZEND_ASSIGN_REF 250 
#define  ZEND_ASSIGN_SL 249 
#define  ZEND_ASSIGN_SR 248 
 int ZEND_ASSIGN_STATIC_PROP ; 
#define  ZEND_ASSIGN_SUB 247 
#define  ZEND_BEGIN_SILENCE 246 
#define  ZEND_BIND_GLOBAL 245 
#define  ZEND_BIND_LEXICAL 244 
 int ZEND_BIND_REF ; 
#define  ZEND_BIND_STATIC 243 
#define  ZEND_BOOL 242 
#define  ZEND_BOOL_NOT 241 
#define  ZEND_BOOL_XOR 240 
#define  ZEND_BW_AND 239 
#define  ZEND_BW_NOT 238 
#define  ZEND_BW_OR 237 
#define  ZEND_BW_XOR 236 
#define  ZEND_CASE 235 
#define  ZEND_CAST 234 
#define  ZEND_CATCH 233 
#define  ZEND_CLONE 232 
#define  ZEND_COALESCE 231 
#define  ZEND_CONCAT 230 
#define  ZEND_COPY_TMP 229 
#define  ZEND_COUNT 228 
#define  ZEND_DECLARE_ANON_CLASS 227 
#define  ZEND_DECLARE_ANON_INHERITED_CLASS 226 
#define  ZEND_DEFINED 225 
#define  ZEND_DIV 224 
#define  ZEND_DO_FCALL 223 
#define  ZEND_DO_FCALL_BY_NAME 222 
#define  ZEND_DO_ICALL 221 
#define  ZEND_DO_UCALL 220 
#define  ZEND_FAST_CONCAT 219 
#define  ZEND_FETCH_CLASS 218 
#define  ZEND_FETCH_CLASS_CONSTANT 217 
 int ZEND_FETCH_CLASS_MASK ; 
#define  ZEND_FETCH_CLASS_PARENT 216 
#define  ZEND_FETCH_CLASS_SELF 215 
#define  ZEND_FETCH_CLASS_STATIC 214 
#define  ZEND_FETCH_CONSTANT 213 
#define  ZEND_FETCH_DIM_FUNC_ARG 212 
#define  ZEND_FETCH_DIM_IS 211 
#define  ZEND_FETCH_DIM_R 210 
#define  ZEND_FETCH_DIM_RW 209 
#define  ZEND_FETCH_DIM_UNSET 208 
#define  ZEND_FETCH_DIM_W 207 
#define  ZEND_FETCH_LIST_R 206 
#define  ZEND_FETCH_LIST_W 205 
#define  ZEND_FETCH_OBJ_FUNC_ARG 204 
#define  ZEND_FETCH_OBJ_IS 203 
#define  ZEND_FETCH_OBJ_R 202 
#define  ZEND_FETCH_OBJ_RW 201 
#define  ZEND_FETCH_OBJ_UNSET 200 
#define  ZEND_FETCH_OBJ_W 199 
#define  ZEND_FETCH_STATIC_PROP_FUNC_ARG 198 
#define  ZEND_FETCH_STATIC_PROP_IS 197 
#define  ZEND_FETCH_STATIC_PROP_R 196 
#define  ZEND_FETCH_STATIC_PROP_RW 195 
#define  ZEND_FETCH_STATIC_PROP_UNSET 194 
#define  ZEND_FETCH_STATIC_PROP_W 193 
#define  ZEND_FETCH_THIS 192 
#define  ZEND_FE_FETCH_R 191 
#define  ZEND_FE_FETCH_RW 190 
#define  ZEND_FE_RESET_R 189 
#define  ZEND_FE_RESET_RW 188 
#define  ZEND_FUNC_GET_ARGS 187 
 TYPE_13__* ZEND_FUNC_INFO (TYPE_11__ const*) ; 
#define  ZEND_FUNC_NUM_ARGS 186 
#define  ZEND_GET_CALLED_CLASS 185 
#define  ZEND_GET_CLASS 184 
#define  ZEND_GET_TYPE 183 
#define  ZEND_INCLUDE_OR_EVAL 182 
#define  ZEND_INIT_ARRAY 181 
#define  ZEND_INSTANCEOF 180 
#define  ZEND_IN_ARRAY 179 
#define  ZEND_ISSET_ISEMPTY_CV 178 
#define  ZEND_ISSET_ISEMPTY_DIM_OBJ 177 
#define  ZEND_ISSET_ISEMPTY_PROP_OBJ 176 
#define  ZEND_ISSET_ISEMPTY_STATIC_PROP 175 
#define  ZEND_ISSET_ISEMPTY_VAR 174 
#define  ZEND_IS_EQUAL 173 
#define  ZEND_IS_IDENTICAL 172 
#define  ZEND_IS_NOT_EQUAL 171 
#define  ZEND_IS_NOT_IDENTICAL 170 
#define  ZEND_IS_SMALLER 169 
#define  ZEND_IS_SMALLER_OR_EQUAL 168 
#define  ZEND_JMPNZ_EX 167 
#define  ZEND_JMPZ_EX 166 
#define  ZEND_JMP_SET 165 
 int /*<<< orphan*/  ZEND_LONG_MAX ; 
 int /*<<< orphan*/  ZEND_LONG_MIN ; 
#define  ZEND_MAKE_REF 164 
#define  ZEND_MOD 163 
#define  ZEND_MUL 162 
#define  ZEND_NEW 161 
 int ZEND_OPTIMIZER_IGNORE_OVERLOADING ; 
 int ZEND_OP_DATA ; 
#define  ZEND_POST_DEC 160 
#define  ZEND_POST_DEC_OBJ 159 
#define  ZEND_POST_INC 158 
#define  ZEND_POST_INC_OBJ 157 
#define  ZEND_POW 156 
#define  ZEND_PRE_DEC 155 
#define  ZEND_PRE_DEC_OBJ 154 
#define  ZEND_PRE_INC 153 
#define  ZEND_PRE_INC_OBJ 152 
#define  ZEND_QM_ASSIGN 151 
#define  ZEND_RECV 150 
#define  ZEND_RECV_INIT 149 
 int ZEND_RETURNS_FUNCTION ; 
#define  ZEND_RETURN_BY_REF 148 
#define  ZEND_ROPE_ADD 147 
#define  ZEND_ROPE_END 146 
#define  ZEND_ROPE_INIT 145 
#define  ZEND_SEND_FUNC_ARG 144 
#define  ZEND_SEND_REF 143 
#define  ZEND_SEND_UNPACK 142 
#define  ZEND_SEND_VAR 141 
#define  ZEND_SEND_VAR_EX 140 
#define  ZEND_SEND_VAR_NO_REF 139 
#define  ZEND_SEND_VAR_NO_REF_EX 138 
#define  ZEND_SL 137 
#define  ZEND_SR 136 
#define  ZEND_STRLEN 135 
#define  ZEND_SUB 134 
#define  ZEND_TYPE_CHECK 133 
#define  ZEND_UNSET_CV 132 
#define  ZEND_UNSET_DIM 131 
#define  ZEND_UNSET_OBJ 130 
 int /*<<< orphan*/  ZEND_USER_FUNCTION ; 
#define  ZEND_VERIFY_RETURN_TYPE 129 
#define  ZEND_YIELD 128 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int _IS_BOOL ; 
 int assign_dim_result_type (int,int,int,int) ; 
 int binary_op_result_type (TYPE_9__*,int,int,int,scalar_t__,int) ; 
 TYPE_14__* get_class_entry (TYPE_10__ const*,int /*<<< orphan*/ ) ; 
 int get_compound_assign_op (int const) ; 
 int zend_array_element_type (int,int,int) ; 
 int zend_fetch_arg_info (TYPE_10__ const*,TYPE_16__*,TYPE_14__**) ; 
 int /*<<< orphan*/ * zend_fetch_prop_info (TYPE_11__ const*,TYPE_9__*,TYPE_12__*,int) ; 
 int zend_fetch_prop_type (TYPE_10__ const*,int /*<<< orphan*/ *,TYPE_14__**) ; 
 int /*<<< orphan*/ * zend_fetch_static_prop_info (TYPE_10__ const*,TYPE_11__ const*,TYPE_9__*,TYPE_12__*) ; 
 int zend_get_func_info (TYPE_15__*,TYPE_9__*) ; 
 TYPE_14__* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zend_ssa_next_use (TYPE_8__*,size_t,int) ; 

__attribute__((used)) static int zend_update_type_info(const zend_op_array *op_array,
                                  zend_ssa            *ssa,
                                  const zend_script   *script,
                                  zend_bitset          worklist,
                                  int                  i,
                                  zend_long            optimization_level)
{
	uint32_t t1, t2;
	uint32_t tmp, orig;
	zend_op *opline = op_array->opcodes + i;
	zend_ssa_op *ssa_ops = ssa->ops;
	zend_ssa_var *ssa_vars = ssa->vars;
	zend_ssa_var_info *ssa_var_info = ssa->var_info;
	zend_class_entry *ce;
	int j;

	if (opline->opcode == ZEND_OP_DATA) {
		opline--;
		i--;
	}

	t1 = OP1_INFO();
	t2 = OP2_INFO();

	/* If one of the operands cannot have any type, this means the operand derives from
	 * unreachable code. Propagate the empty result early, so that that the following
	 * code may assume that operands have at least one type. */
	if (!(t1 & (MAY_BE_ANY|MAY_BE_UNDEF|MAY_BE_CLASS|MAY_BE_ERROR))
		|| !(t2 & (MAY_BE_ANY|MAY_BE_UNDEF|MAY_BE_CLASS|MAY_BE_ERROR))) {
		tmp = 0;
		if (ssa_ops[i].result_def >= 0) {
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
		}
		if (ssa_ops[i].op1_def >= 0) {
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
		}
		if (ssa_ops[i].op2_def >= 0) {
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].op2_def);
		}
		return 1;
	}

	switch (opline->opcode) {
		case ZEND_ADD:
		case ZEND_SUB:
		case ZEND_MUL:
		case ZEND_DIV:
		case ZEND_POW:
		case ZEND_MOD:
		case ZEND_BW_OR:
		case ZEND_BW_AND:
		case ZEND_BW_XOR:
		case ZEND_SL:
		case ZEND_SR:
		case ZEND_CONCAT:
			tmp = binary_op_result_type(ssa, opline->opcode, t1, t2, ssa_ops[i].result_def, optimization_level);
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			break;
		case ZEND_BW_NOT:
			tmp = 0;
			if (t1 & MAY_BE_STRING) {
				tmp |= MAY_BE_STRING | MAY_BE_RC1;
			}
			if (t1 & (MAY_BE_ANY-MAY_BE_STRING)) {
				tmp |= MAY_BE_LONG;
			}
			if (!(ZEND_OPTIMIZER_IGNORE_OVERLOADING & optimization_level)) {
				if (t1 & MAY_BE_OBJECT) {
					/* Potentially overloaded operator. */
					tmp |= MAY_BE_OBJECT | MAY_BE_RC1;
				}
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			break;
		case ZEND_BEGIN_SILENCE:
			UPDATE_SSA_TYPE(MAY_BE_LONG, ssa_ops[i].result_def);
			break;
		case ZEND_BOOL_NOT:
		case ZEND_BOOL_XOR:
		case ZEND_IS_IDENTICAL:
		case ZEND_IS_NOT_IDENTICAL:
		case ZEND_IS_EQUAL:
		case ZEND_IS_NOT_EQUAL:
		case ZEND_IS_SMALLER:
		case ZEND_IS_SMALLER_OR_EQUAL:
		case ZEND_INSTANCEOF:
		case ZEND_JMPZ_EX:
		case ZEND_JMPNZ_EX:
		case ZEND_CASE:
		case ZEND_BOOL:
		case ZEND_ISSET_ISEMPTY_CV:
		case ZEND_ISSET_ISEMPTY_VAR:
		case ZEND_ISSET_ISEMPTY_DIM_OBJ:
		case ZEND_ISSET_ISEMPTY_PROP_OBJ:
		case ZEND_ISSET_ISEMPTY_STATIC_PROP:
		case ZEND_ASSERT_CHECK:
		case ZEND_IN_ARRAY:
			UPDATE_SSA_TYPE(MAY_BE_FALSE|MAY_BE_TRUE, ssa_ops[i].result_def);
			break;
		case ZEND_ARRAY_KEY_EXISTS:
			tmp = MAY_BE_FALSE|MAY_BE_TRUE;
			if (t2 & ((MAY_BE_ANY|MAY_BE_UNDEF) - (MAY_BE_ARRAY|MAY_BE_OBJECT))) {
				tmp |= MAY_BE_NULL;
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			break;
		case ZEND_CAST:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = t1;
				if ((t1 & (MAY_BE_ARRAY|MAY_BE_OBJECT)) &&
				    (opline->op1_type == IS_CV) &&
				    (opline->extended_value == IS_ARRAY ||
				     opline->extended_value == IS_OBJECT)) {
					tmp |= MAY_BE_RCN;
				} else if ((t1 & MAY_BE_STRING) &&
				    (opline->op1_type == IS_CV) &&
				    opline->extended_value == IS_STRING) {
					tmp |= MAY_BE_RCN;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			tmp = 0;
			if (opline->extended_value == _IS_BOOL) {
				tmp |= MAY_BE_TRUE|MAY_BE_FALSE;
			} else {
				tmp |= 1 << opline->extended_value;
				if (tmp & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
					if ((tmp & MAY_BE_ANY) == (t1 & MAY_BE_ANY)) {
						tmp |= (t1 & MAY_BE_RC1) | MAY_BE_RCN;
					} else if ((opline->extended_value == IS_ARRAY ||
					            opline->extended_value == IS_OBJECT) &&
					           (t1 & (MAY_BE_ARRAY|MAY_BE_OBJECT))) {
							tmp |= MAY_BE_RC1 | MAY_BE_RCN;
					} else if (opline->extended_value == IS_STRING &&
					           (t1 & (MAY_BE_STRING|MAY_BE_OBJECT))) {
						tmp |= MAY_BE_RC1 | MAY_BE_RCN;
					} else {
						tmp |= MAY_BE_RC1;
					}
				}
			}
			if (opline->extended_value == IS_ARRAY) {
				if (t1 & MAY_BE_ARRAY) {
					tmp |= t1 & (MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF);
				}
				if (t1 & MAY_BE_OBJECT) {
					tmp |= MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				} else {
					tmp |= ((t1 & MAY_BE_ANY) << MAY_BE_ARRAY_SHIFT) | ((t1 & MAY_BE_ANY)? MAY_BE_ARRAY_KEY_LONG : 0);
				}
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			break;
		case ZEND_QM_ASSIGN:
		case ZEND_JMP_SET:
		case ZEND_COALESCE:
		case ZEND_COPY_TMP:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = t1;
				if ((t1 & (MAY_BE_RC1|MAY_BE_REF)) && (opline->op1_type == IS_CV)) {
					tmp |= MAY_BE_RCN;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			tmp = t1 & ~(MAY_BE_UNDEF|MAY_BE_REF);
			if (t1 & MAY_BE_UNDEF) {
				tmp |= MAY_BE_NULL;
			}
			if (t1 & (MAY_BE_RC1|MAY_BE_RCN)) {
				tmp |= (t1 & (MAY_BE_RC1|MAY_BE_RCN));
				if (opline->op1_type == IS_CV) {
					tmp |= MAY_BE_RCN;
				}
			}
			if (opline->opcode != ZEND_QM_ASSIGN) {
				/* COALESCE and JMP_SET result can't be null */
				tmp &= ~MAY_BE_NULL;
				if (opline->opcode == ZEND_JMP_SET) {
					/* JMP_SET result can't be false either */
					tmp &= ~MAY_BE_FALSE;
				}
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].result_def);
			break;
		case ZEND_ASSIGN_ADD:
		case ZEND_ASSIGN_SUB:
		case ZEND_ASSIGN_MUL:
		case ZEND_ASSIGN_DIV:
		case ZEND_ASSIGN_POW:
		case ZEND_ASSIGN_MOD:
		case ZEND_ASSIGN_SL:
		case ZEND_ASSIGN_SR:
		case ZEND_ASSIGN_BW_OR:
		case ZEND_ASSIGN_BW_AND:
		case ZEND_ASSIGN_BW_XOR:
		case ZEND_ASSIGN_CONCAT: {
			zend_property_info *prop_info = NULL;
			orig = 0;
			tmp = 0;
			if (opline->extended_value == ZEND_ASSIGN_OBJ) {
				prop_info = zend_fetch_prop_info(op_array, ssa, opline, i);
				orig = t1;
				t1 = zend_fetch_prop_type(script, prop_info, &ce);
				t2 = OP1_DATA_INFO();
			} else if (opline->extended_value == ZEND_ASSIGN_DIM) {
				if (t1 & MAY_BE_ARRAY_OF_REF) {
			        tmp |= MAY_BE_REF;
				}
				orig = t1;
				t1 = zend_array_element_type(t1, 1, 0);
				t2 = OP1_DATA_INFO();
			} else if (opline->extended_value == ZEND_ASSIGN_STATIC_PROP) {
				prop_info = zend_fetch_static_prop_info(script, op_array, ssa, opline);
				t1 = zend_fetch_prop_type(script, prop_info, &ce);
				t2 = OP1_DATA_INFO();
			} else {
				if (t1 & MAY_BE_REF) {
			        tmp |= MAY_BE_REF;
				}
			}

			tmp |= binary_op_result_type(
				ssa, get_compound_assign_op(opline->opcode), t1, t2, ssa_ops[i].op1_def, optimization_level);
			if (tmp & (MAY_BE_STRING|MAY_BE_ARRAY)) {
				tmp |= MAY_BE_RC1;
			}
			if (tmp & (MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
				tmp |= MAY_BE_RC1 | MAY_BE_RCN;
			}

			if (opline->extended_value == ZEND_ASSIGN_DIM) {
				if (opline->op1_type == IS_CV) {
					orig = assign_dim_result_type(orig, OP2_INFO(), tmp, opline->op2_type);
					UPDATE_SSA_TYPE(orig, ssa_ops[i].op1_def);
					COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
				}
			} else if (opline->extended_value == ZEND_ASSIGN_OBJ) {
				if (opline->op1_type == IS_CV) {
					if (!(orig & MAY_BE_REF)) {
						if (orig & (MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE)) {
							orig &= ~(MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE);
							orig |= MAY_BE_OBJECT | MAY_BE_RC1 | MAY_BE_RCN;
						}
						if (orig & MAY_BE_OBJECT) {
							orig |= (MAY_BE_RC1|MAY_BE_RCN);
						}
					}
					UPDATE_SSA_TYPE(orig, ssa_ops[i].op1_def);
					COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
				}
			} else if (opline->extended_value == ZEND_ASSIGN_STATIC_PROP) {
				/* Nothing to do */
			} else {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				ce = NULL;
				if (opline->extended_value == ZEND_ASSIGN_DIM) {
					if (opline->op2_type == IS_UNUSED) {
						/* When appending to an array and the LONG_MAX key is already used
						 * null will be returned. */
						tmp |= MAY_BE_NULL;
					}
					if (t2 & (MAY_BE_ARRAY | MAY_BE_OBJECT)) {
						/* Arrays and objects cannot be used as keys. */
						tmp |= MAY_BE_NULL;
					}
					if (t1 & (MAY_BE_ANY - (MAY_BE_NULL | MAY_BE_FALSE | MAY_BE_STRING | MAY_BE_ARRAY))) {
						/* null and false are implicitly converted to array, anything else
						 * results in a null return value. */
						tmp |= MAY_BE_NULL;
					}
				} else if (opline->extended_value == ZEND_ASSIGN_OBJ) {
					if (orig & (MAY_BE_ANY - (MAY_BE_NULL | MAY_BE_FALSE | MAY_BE_OBJECT))) {
						/* null and false (and empty string) are implicitly converted to object,
						 * anything else results in a null return value. */
						tmp |= MAY_BE_NULL;
					}

					/* The return value must also satisfy the property type */
					if (prop_info) {
						tmp &= zend_fetch_prop_type(script, prop_info, NULL);
					}
				} else if (opline->extended_value == ZEND_ASSIGN_STATIC_PROP) {
					/* The return value must also satisfy the property type */
					if (prop_info) {
						tmp &= zend_fetch_prop_type(script, prop_info, NULL);
					}
				}
				tmp &= ~MAY_BE_REF;
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
				if (ce) {
					UPDATE_SSA_OBJ_TYPE(ce, 1, ssa_ops[i].result_def);
				}
			}
			break;
		}
		case ZEND_PRE_INC:
		case ZEND_PRE_DEC:
			tmp = 0;
			if (t1 & MAY_BE_REF) {
				tmp |= MAY_BE_REF;
			}
			if (t1 & (MAY_BE_RC1|MAY_BE_RCN)) {
				tmp |= MAY_BE_RC1;
				if (ssa_ops[i].result_def >= 0) {
					tmp |= MAY_BE_RCN;
				}
			}
			if ((t1 & (MAY_BE_ANY|MAY_BE_UNDEF)) == MAY_BE_LONG) {
				if (!ssa_var_info[ssa_ops[i].op1_use].has_range ||
				    (opline->opcode == ZEND_PRE_DEC &&
				     (ssa_var_info[ssa_ops[i].op1_use].range.underflow ||
				      ssa_var_info[ssa_ops[i].op1_use].range.min == ZEND_LONG_MIN)) ||
				     (opline->opcode == ZEND_PRE_INC &&
				      (ssa_var_info[ssa_ops[i].op1_use].range.overflow ||
				       ssa_var_info[ssa_ops[i].op1_use].range.max == ZEND_LONG_MAX))) {
					/* may overflow */
					tmp |= MAY_BE_LONG | MAY_BE_DOUBLE;
				} else {
					tmp |= MAY_BE_LONG;
				}
			} else {
				if (t1 & MAY_BE_ERROR) {
					tmp |= MAY_BE_NULL;
				}
				if (t1 & (MAY_BE_UNDEF | MAY_BE_NULL)) {
					if (opline->opcode == ZEND_PRE_INC) {
						tmp |= MAY_BE_LONG;
					} else {
						tmp |= MAY_BE_NULL;
					}
				}
				if (t1 & MAY_BE_LONG) {
					tmp |= MAY_BE_LONG | MAY_BE_DOUBLE;
				}
				if (t1 & MAY_BE_DOUBLE) {
					tmp |= MAY_BE_DOUBLE;
				}
				if (t1 & MAY_BE_STRING) {
					tmp |= MAY_BE_STRING | MAY_BE_LONG | MAY_BE_DOUBLE;
				}
				tmp |= t1 & (MAY_BE_FALSE | MAY_BE_TRUE | MAY_BE_RESOURCE | MAY_BE_ARRAY | MAY_BE_OBJECT | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF | MAY_BE_ARRAY_KEY_ANY);
			}
			if (ssa_ops[i].op1_def >= 0) {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			break;
		case ZEND_POST_INC:
		case ZEND_POST_DEC:
			if (ssa_ops[i].result_def >= 0) {
				tmp = 0;
				if (t1 & (MAY_BE_RC1|MAY_BE_RCN)) {
					tmp |= MAY_BE_RC1|MAY_BE_RCN;
				}
				tmp |= t1 & ~(MAY_BE_UNDEF|MAY_BE_ERROR|MAY_BE_REF|MAY_BE_RCN);
				if (t1 & MAY_BE_UNDEF) {
					tmp |= MAY_BE_NULL;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			tmp = 0;
			if (t1 & MAY_BE_REF) {
				tmp |= MAY_BE_REF;
			}
			if (t1 & (MAY_BE_RC1|MAY_BE_RCN)) {
				tmp |= MAY_BE_RC1;
			}
			if ((t1 & (MAY_BE_ANY|MAY_BE_UNDEF)) == MAY_BE_LONG) {
				if (!ssa_var_info[ssa_ops[i].op1_use].has_range ||
				     (opline->opcode == ZEND_PRE_DEC &&
				      (ssa_var_info[ssa_ops[i].op1_use].range.underflow ||
				       ssa_var_info[ssa_ops[i].op1_use].range.min == ZEND_LONG_MIN)) ||
				      (opline->opcode == ZEND_PRE_INC &&
				       (ssa_var_info[ssa_ops[i].op1_use].range.overflow ||
				        ssa_var_info[ssa_ops[i].op1_use].range.max == ZEND_LONG_MAX))) {
					/* may overflow */
					tmp |= MAY_BE_LONG | MAY_BE_DOUBLE;
				} else {
					tmp |= MAY_BE_LONG;
				}
			} else {
				if (t1 & MAY_BE_ERROR) {
					tmp |= MAY_BE_NULL;
				}
				if (t1 & (MAY_BE_UNDEF | MAY_BE_NULL)) {
					if (opline->opcode == ZEND_POST_INC) {
						tmp |= MAY_BE_LONG;
					} else {
						tmp |= MAY_BE_NULL;
					}
				}
				if (t1 & MAY_BE_LONG) {
					tmp |= MAY_BE_LONG | MAY_BE_DOUBLE;
				}
				if (t1 & MAY_BE_DOUBLE) {
					tmp |= MAY_BE_DOUBLE;
				}
				if (t1 & MAY_BE_STRING) {
					tmp |= MAY_BE_STRING | MAY_BE_LONG | MAY_BE_DOUBLE;
				}
				tmp |= t1 & (MAY_BE_FALSE | MAY_BE_TRUE | MAY_BE_RESOURCE | MAY_BE_ARRAY | MAY_BE_OBJECT | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF | MAY_BE_ARRAY_KEY_ANY);
			}
			if (ssa_ops[i].op1_def >= 0) {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_ASSIGN_DIM:
			if (opline->op1_type == IS_CV) {
				tmp = assign_dim_result_type(t1, t2, OP1_DATA_INFO(), opline->op2_type);
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				tmp = 0;
				if (t1 & MAY_BE_STRING) {
					tmp |= MAY_BE_STRING;
				}
				if (t1 & ((MAY_BE_ANY|MAY_BE_UNDEF) - MAY_BE_STRING)) {
					tmp |= (OP1_DATA_INFO() & (MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF));

					if (opline->op2_type == IS_UNUSED) {
						/* When appending to an array and the LONG_MAX key is already used
						 * null will be returned. */
						tmp |= MAY_BE_NULL;
					}
					if (t2 & (MAY_BE_ARRAY | MAY_BE_OBJECT)) {
						/* Arrays and objects cannot be used as keys. */
						tmp |= MAY_BE_NULL;
					}
					if (t1 & (MAY_BE_ANY - (MAY_BE_NULL | MAY_BE_FALSE | MAY_BE_STRING | MAY_BE_ARRAY))) {
						/* undef, null and false are implicitly converted to array, anything else
						 * results in a null return value. */
						tmp |= MAY_BE_NULL;
					}
				}
				tmp |= MAY_BE_RC1 | MAY_BE_RCN;
				if (t1 & MAY_BE_OBJECT) {
					tmp |= MAY_BE_REF;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			if ((opline+1)->op1_type == IS_CV && ssa_ops[i+1].op1_def >= 0) {
				opline++;
				i++;
				tmp = OP1_INFO();
				if (tmp & (MAY_BE_ANY | MAY_BE_REF)) {
					if (tmp & MAY_BE_RC1) {
						tmp |= MAY_BE_RCN;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_ASSIGN_OBJ:
			if (opline->op1_type == IS_CV) {
				tmp = t1;
				if (t1 & (MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE)) {
					tmp &= ~(MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE);
					tmp |= MAY_BE_OBJECT | MAY_BE_RC1 | MAY_BE_RCN;
				}
				if (tmp & MAY_BE_OBJECT) {
					tmp |= MAY_BE_RC1 | MAY_BE_RCN;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				// TODO: If there is no __set we might do better
				tmp = zend_fetch_prop_type(script,
					zend_fetch_prop_info(op_array, ssa, opline, i), &ce);
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
				if (ce) {
					UPDATE_SSA_OBJ_TYPE(ce, 1, ssa_ops[i].result_def);
				}
			}
			if ((opline+1)->op1_type == IS_CV) {
				opline++;
				i++;
				tmp = OP1_INFO();
				if (tmp & (MAY_BE_ANY | MAY_BE_REF)) {
					if (tmp & MAY_BE_RC1) {
						tmp |= MAY_BE_RCN;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_PRE_INC_OBJ:
		case ZEND_PRE_DEC_OBJ:
		case ZEND_POST_INC_OBJ:
		case ZEND_POST_DEC_OBJ:
			if (opline->op1_type == IS_CV) {
				tmp = t1;
				if (t1 & (MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE)) {
					tmp &= ~(MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE);
					tmp |= MAY_BE_OBJECT | MAY_BE_RC1 | MAY_BE_RCN;
				}
				if (tmp & MAY_BE_OBJECT) {
					tmp |= MAY_BE_RC1 | MAY_BE_RCN;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				// TODO: ???
				tmp = MAY_BE_RC1 | MAY_BE_RCN | MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			break;
		case ZEND_ASSIGN:
			if (opline->op2_type == IS_CV && ssa_ops[i].op2_def >= 0) {
				tmp = t2;
				if (tmp & (MAY_BE_ANY | MAY_BE_REF)) {
					if (tmp & MAY_BE_RC1) {
						tmp |= MAY_BE_RCN;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op2_def);
			}
			tmp = t2 & ~(MAY_BE_UNDEF|MAY_BE_REF|MAY_BE_RC1|MAY_BE_RCN);
			if (t2 & MAY_BE_UNDEF) {
				tmp |= MAY_BE_NULL;
			}
			if (t1 & MAY_BE_REF) {
				tmp |= MAY_BE_REF;
			}
			if (t2 & MAY_BE_REF) {
				tmp |= MAY_BE_RC1 | MAY_BE_RCN;
			} else if (opline->op2_type & (IS_TMP_VAR|IS_VAR)) {
				tmp |= t2 & (MAY_BE_RC1|MAY_BE_RCN);
			} else if (t2 & (MAY_BE_RC1|MAY_BE_RCN)) {
				tmp |= MAY_BE_RCN;
			}
			if (RETURN_VALUE_USED(opline) && (tmp & MAY_BE_RC1)) {
				tmp |= MAY_BE_RCN;
			}
			if (ssa_ops[i].op1_def >= 0) {
				if (ssa_var_info[ssa_ops[i].op1_def].use_as_double) {
					tmp &= ~MAY_BE_LONG;
					tmp |= MAY_BE_DOUBLE;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op2_use, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				UPDATE_SSA_TYPE(tmp & ~MAY_BE_REF, ssa_ops[i].result_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op2_use, ssa_ops[i].result_def);
			}
			break;
		case ZEND_ASSIGN_REF:
// TODO: ???
			if (opline->op2_type == IS_CV) {
				tmp = (MAY_BE_REF | t2) & ~(MAY_BE_UNDEF|MAY_BE_RC1|MAY_BE_RCN);
				if (t2 & MAY_BE_UNDEF) {
					tmp |= MAY_BE_NULL;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op2_def);
			}
			if (opline->op2_type == IS_VAR && opline->extended_value == ZEND_RETURNS_FUNCTION) {
				tmp = (MAY_BE_REF | MAY_BE_RCN | MAY_BE_RC1 | t2) & ~MAY_BE_UNDEF;
			} else {
				tmp = (MAY_BE_REF | t2) & ~(MAY_BE_UNDEF|MAY_BE_ERROR|MAY_BE_RC1|MAY_BE_RCN);
			}
			if (t2 & MAY_BE_UNDEF) {
				tmp |= MAY_BE_NULL;
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			if (ssa_ops[i].result_def >= 0) {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			break;
		case ZEND_ASSIGN_OBJ_REF:
			if (opline->op1_type == IS_CV) {
				tmp = t1;
				if (t1 & (MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE)) {
					tmp &= ~(MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE);
					tmp |= MAY_BE_OBJECT | MAY_BE_RC1 | MAY_BE_RCN;
				}
				if (tmp & MAY_BE_OBJECT) {
					tmp |= MAY_BE_RC1 | MAY_BE_RCN;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}

			t2 = OP1_DATA_INFO();
			if ((opline+1)->op1_type == IS_VAR && (opline->extended_value & ZEND_RETURNS_FUNCTION)) {
				tmp = (MAY_BE_REF | MAY_BE_RCN | MAY_BE_RC1 | t2) & ~MAY_BE_UNDEF;
			} else {
				tmp = (MAY_BE_REF | t2) & ~(MAY_BE_UNDEF|MAY_BE_ERROR|MAY_BE_RC1|MAY_BE_RCN);
			}
			if (t2 & MAY_BE_UNDEF) {
				tmp |= MAY_BE_NULL;
			}
			if (ssa_ops[i].result_def >= 0) {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			if ((opline+1)->op1_type == IS_CV) {
				opline++;
				i++;
				tmp = (MAY_BE_REF | t2) & ~(MAY_BE_UNDEF|MAY_BE_RC1|MAY_BE_RCN);
				if (t2 & MAY_BE_UNDEF) {
					tmp |= MAY_BE_NULL;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_BIND_GLOBAL:
			tmp = MAY_BE_REF | MAY_BE_ANY
				| MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			break;
		case ZEND_BIND_STATIC:
			tmp = MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF
				| ((opline->extended_value & ZEND_BIND_REF) ? MAY_BE_REF : (MAY_BE_RC1 | MAY_BE_RCN));
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			break;
		case ZEND_SEND_VAR:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = t1;
				if ((t1 & (MAY_BE_RC1|MAY_BE_REF)) && (opline->op1_type == IS_CV)) {
					tmp |= MAY_BE_RCN;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_BIND_LEXICAL:
			if (ssa_ops[i].op2_def >= 0) {
				if (opline->extended_value & ZEND_BIND_REF) {
					tmp = t2 | MAY_BE_REF;
				} else {
					tmp = t2 & ~(MAY_BE_RC1|MAY_BE_RCN);
					if (t2 & (MAY_BE_RC1|MAY_BE_RCN)) {
						tmp |= MAY_BE_RCN;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op2_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op2_use, ssa_ops[i].op2_def);
			}
			break;
		case ZEND_YIELD:
			if (ssa_ops[i].op1_def >= 0) {
				if (op_array->fn_flags & ZEND_ACC_RETURN_REFERENCE) {
					tmp = t1 | MAY_BE_REF;
				} else {
					tmp = t1 & ~(MAY_BE_RC1|MAY_BE_RCN);
					if (t1 & (MAY_BE_RC1|MAY_BE_RCN)) {
						tmp |= MAY_BE_RCN;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				tmp = MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF
					| MAY_BE_RC1 | MAY_BE_RCN;
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			break;
		case ZEND_SEND_VAR_EX:
		case ZEND_SEND_FUNC_ARG:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = (t1 & MAY_BE_UNDEF)|MAY_BE_REF|MAY_BE_RC1|MAY_BE_RCN|MAY_BE_ANY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_SEND_REF:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = MAY_BE_REF|MAY_BE_RC1|MAY_BE_RCN|MAY_BE_ANY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_SEND_UNPACK:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = t1;
				if (t1 & MAY_BE_ARRAY) {
					tmp |= MAY_BE_RC1 | MAY_BE_RCN;
					/* SEND_UNPACK may acquire references into the array */
					tmp |= MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				}
				if (t1 & MAY_BE_OBJECT) {
					tmp |= MAY_BE_RC1 | MAY_BE_RCN;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_FAST_CONCAT:
		case ZEND_ROPE_INIT:
		case ZEND_ROPE_ADD:
		case ZEND_ROPE_END:
			UPDATE_SSA_TYPE(MAY_BE_STRING|MAY_BE_RC1|MAY_BE_RCN, ssa_ops[i].result_def);
			break;
		case ZEND_RECV:
		case ZEND_RECV_INIT:
		{
			/* Typehinting */
			zend_func_info *func_info;
			zend_arg_info *arg_info = NULL;
			if (op_array->arg_info && opline->op1.num <= op_array->num_args) {
				arg_info = &op_array->arg_info[opline->op1.num-1];
			}

			ce = NULL;
			if (arg_info) {
				tmp = zend_fetch_arg_info(script, arg_info, &ce);
				if (opline->opcode == ZEND_RECV_INIT &&
				           Z_TYPE_P(CRT_CONSTANT_EX(op_array, opline, opline->op2, ssa->rt_constants)) == IS_CONSTANT_AST) {
					/* The constant may resolve to NULL */
					tmp |= MAY_BE_NULL;
				}
				if (arg_info->pass_by_reference) {
					tmp |= MAY_BE_REF;
				} else if (tmp & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
					tmp |= MAY_BE_RC1|MAY_BE_RCN;
				}
			} else {
				tmp = MAY_BE_REF|MAY_BE_RC1|MAY_BE_RCN|MAY_BE_ANY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
			}
			func_info = ZEND_FUNC_INFO(op_array);
			if (func_info && (int)opline->op1.num-1 < func_info->num_args) {
				tmp = (tmp & (MAY_BE_RC1|MAY_BE_RCN|MAY_BE_REF)) |
					(tmp & func_info->arg_info[opline->op1.num-1].info.type);
			}
#if 0
			/* We won't receive unused arguments */
			if (ssa_vars[ssa_ops[i].result_def].use_chain < 0 &&
			    ssa_vars[ssa_ops[i].result_def].phi_use_chain == NULL &&
			    op_array->arg_info &&
			    opline->op1.num <= op_array->num_args &&
			    op_array->arg_info[opline->op1.num-1].class_name == NULL &&
			    !op_array->arg_info[opline->op1.num-1].type_hint) {
				tmp = MAY_BE_UNDEF|MAY_BE_RCN;
			}
#endif
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			if (func_info &&
			    (int)opline->op1.num-1 < func_info->num_args &&
			    func_info->arg_info[opline->op1.num-1].info.ce) {
				UPDATE_SSA_OBJ_TYPE(
					func_info->arg_info[opline->op1.num-1].info.ce,
					func_info->arg_info[opline->op1.num-1].info.is_instanceof,
					ssa_ops[i].result_def);
			} else if (ce) {
				UPDATE_SSA_OBJ_TYPE(ce, 1, ssa_ops[i].result_def);
			} else {
				UPDATE_SSA_OBJ_TYPE(NULL, 0, ssa_ops[i].result_def);
			}
			break;
		}
		case ZEND_DECLARE_ANON_CLASS:
		case ZEND_DECLARE_ANON_INHERITED_CLASS:
			UPDATE_SSA_TYPE(MAY_BE_CLASS, ssa_ops[i].result_def);
			if (script && (ce = zend_hash_find_ptr(&script->class_table, Z_STR_P(CRT_CONSTANT_EX(op_array, opline, opline->op1, ssa->rt_constants)))) != NULL) {
				UPDATE_SSA_OBJ_TYPE(ce, 0, ssa_ops[i].result_def);
			}
			break;
		case ZEND_FETCH_CLASS:
			UPDATE_SSA_TYPE(MAY_BE_CLASS, ssa_ops[i].result_def);
			if (opline->op2_type == IS_UNUSED) {
				switch (opline->op1.num & ZEND_FETCH_CLASS_MASK) {
					case ZEND_FETCH_CLASS_SELF:
						if (op_array->scope) {
							UPDATE_SSA_OBJ_TYPE(op_array->scope, 0, ssa_ops[i].result_def);
						} else {
							UPDATE_SSA_OBJ_TYPE(NULL, 0, ssa_ops[i].result_def);
						}
						break;
					case ZEND_FETCH_CLASS_PARENT:
						if (op_array->scope && op_array->scope->parent && (op_array->scope->ce_flags & ZEND_ACC_LINKED)) {
							UPDATE_SSA_OBJ_TYPE(op_array->scope->parent, 0, ssa_ops[i].result_def);
						} else {
							UPDATE_SSA_OBJ_TYPE(NULL, 0, ssa_ops[i].result_def);
						}
						break;
					case ZEND_FETCH_CLASS_STATIC:
					default:
						UPDATE_SSA_OBJ_TYPE(NULL, 0, ssa_ops[i].result_def);
						break;
				}
			} else if (opline->op2_type == IS_CONST) {
				zval *zv = CRT_CONSTANT_EX(op_array, opline, opline->op2, ssa->rt_constants);
				if (Z_TYPE_P(zv) == IS_STRING) {
					ce = get_class_entry(script, Z_STR_P(zv+1));
					UPDATE_SSA_OBJ_TYPE(ce, 0, ssa_ops[i].result_def);
				} else {
					UPDATE_SSA_OBJ_TYPE(NULL, 0, ssa_ops[i].result_def);
				}
			} else {
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op2_use, ssa_ops[i].result_def);
			}
			break;
		case ZEND_NEW:
			tmp = MAY_BE_RC1|MAY_BE_RCN|MAY_BE_OBJECT;
			if (opline->op1_type == IS_CONST &&
			    (ce = get_class_entry(script, Z_STR_P(CRT_CONSTANT_EX(op_array, opline, opline->op1, ssa->rt_constants)+1))) != NULL) {
				UPDATE_SSA_OBJ_TYPE(ce, 0, ssa_ops[i].result_def);
			} else if ((t1 & MAY_BE_CLASS) && ssa_ops[i].op1_use >= 0 && ssa_var_info[ssa_ops[i].op1_use].ce) {
				UPDATE_SSA_OBJ_TYPE(ssa_var_info[ssa_ops[i].op1_use].ce, ssa_var_info[ssa_ops[i].op1_use].is_instanceof, ssa_ops[i].result_def);
			} else {
				UPDATE_SSA_OBJ_TYPE(NULL, 0, ssa_ops[i].result_def);
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			break;
		case ZEND_CLONE:
			UPDATE_SSA_TYPE(MAY_BE_RC1|MAY_BE_RCN|MAY_BE_OBJECT, ssa_ops[i].result_def);
			COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].result_def);
			break;
		case ZEND_INIT_ARRAY:
		case ZEND_ADD_ARRAY_ELEMENT:
			if (opline->op1_type == IS_CV && ssa_ops[i].op1_def >= 0) {
				if (opline->extended_value & ZEND_ARRAY_ELEMENT_REF) {
					tmp = (MAY_BE_REF | t1) & ~(MAY_BE_UNDEF|MAY_BE_RC1|MAY_BE_RCN);
					if (t1 & MAY_BE_UNDEF) {
						tmp |= MAY_BE_NULL;
					}
				} else if ((t1 & (MAY_BE_REF|MAY_BE_RC1|MAY_BE_RCN)) == MAY_BE_REF) {
					tmp = (MAY_BE_REF | t1) & ~(MAY_BE_UNDEF|MAY_BE_RC1|MAY_BE_RCN);
					if (t1 & MAY_BE_UNDEF) {
						tmp |= MAY_BE_NULL;
					}
				} else if (t1 & MAY_BE_REF) {
					tmp = (MAY_BE_RC1 | MAY_BE_RCN | MAY_BE_REF | t1);
				} else {
					tmp = t1;
					if (t1 & MAY_BE_RC1) {
						tmp |= MAY_BE_RCN;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				tmp = MAY_BE_RC1|MAY_BE_ARRAY;
				if (opline->op1_type != IS_UNUSED) {
					tmp |= (t1 & MAY_BE_ANY) << MAY_BE_ARRAY_SHIFT;
					if (t1 & MAY_BE_UNDEF) {
						tmp |= MAY_BE_ARRAY_OF_NULL;
					}
					if (opline->extended_value & ZEND_ARRAY_ELEMENT_REF) {
						tmp |= MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
					}
				}
				if (ssa_ops[i].result_use >= 0) {
					tmp |= ssa_var_info[ssa_ops[i].result_use].type;
				}
				if (opline->op2_type == IS_UNUSED) {
					tmp |= MAY_BE_ARRAY_KEY_LONG;
				} else {
					if (t2 & (MAY_BE_LONG|MAY_BE_FALSE|MAY_BE_TRUE|MAY_BE_DOUBLE)) {
						tmp |= MAY_BE_ARRAY_KEY_LONG;
					}
					if (t2 & (MAY_BE_STRING)) {
						tmp |= MAY_BE_ARRAY_KEY_STRING;
						if (opline->op2_type != IS_CONST) {
							// FIXME: numeric string
							tmp |= MAY_BE_ARRAY_KEY_LONG;
						}
					}
					if (t2 & (MAY_BE_UNDEF | MAY_BE_NULL)) {
						tmp |= MAY_BE_ARRAY_KEY_STRING;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			break;
		case ZEND_UNSET_CV:
			tmp = MAY_BE_UNDEF;
			if (!op_array->function_name) {
				/* In global scope, we know nothing */
				tmp |= MAY_BE_REF;
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			break;
		case ZEND_UNSET_DIM:
		case ZEND_UNSET_OBJ:
			if (ssa_ops[i].op1_def >= 0) {
				UPDATE_SSA_TYPE(t1, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_FE_RESET_R:
		case ZEND_FE_RESET_RW:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = t1;
				if (opline->opcode == ZEND_FE_RESET_RW) {
					tmp |= MAY_BE_REF;
				} else {
					if ((t1 & MAY_BE_RC1) && opline->op1_type != IS_TMP_VAR) {
						tmp |= MAY_BE_RCN;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			if (opline->opcode == ZEND_FE_RESET_RW) {
//???
				tmp = MAY_BE_REF | (t1 & (MAY_BE_ARRAY | MAY_BE_OBJECT));
			} else {
				tmp = MAY_BE_RC1 | MAY_BE_RCN | (t1 & (MAY_BE_ARRAY | MAY_BE_OBJECT | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF));
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].result_def);
			break;
		case ZEND_FE_FETCH_R:
		case ZEND_FE_FETCH_RW:
			tmp = t2;
			if (t1 & MAY_BE_OBJECT) {
				if (opline->opcode == ZEND_FE_FETCH_RW) {
					tmp |= MAY_BE_REF | MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				} else {
					tmp |= MAY_BE_REF | MAY_BE_RCN | MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				}
			}
			if (t1 & MAY_BE_ARRAY) {
				if (opline->opcode == ZEND_FE_FETCH_RW) {
					tmp |= MAY_BE_REF | MAY_BE_RCN | MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				} else {
					tmp |= ((t1 & MAY_BE_ARRAY_OF_ANY) >> MAY_BE_ARRAY_SHIFT);
					if (tmp & MAY_BE_ARRAY) {
						tmp |= MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
					}
					if (t1 & MAY_BE_ARRAY_OF_REF) {
						tmp |= MAY_BE_RC1 | MAY_BE_RCN;
					} else if (tmp & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
						tmp |= MAY_BE_RC1 | MAY_BE_RCN;
					}
				}
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].op2_def);
			if (ssa_ops[i].result_def >= 0) {
				tmp = (ssa_ops[i].result_use >= 0) ? RES_USE_INFO() : 0;
				if (t1 & MAY_BE_OBJECT) {
					tmp |= MAY_BE_RC1 | MAY_BE_RCN | MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				}
				if (t1 & MAY_BE_ARRAY) {
					if (t1 & MAY_BE_ARRAY_KEY_LONG) {
						tmp |= MAY_BE_LONG;
					}
					if (t1 & MAY_BE_ARRAY_KEY_STRING) {
						tmp |= MAY_BE_STRING | MAY_BE_RCN;
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			break;
		case ZEND_FETCH_DIM_R:
		case ZEND_FETCH_DIM_IS:
		case ZEND_FETCH_DIM_RW:
		case ZEND_FETCH_DIM_W:
		case ZEND_FETCH_DIM_UNSET:
		case ZEND_FETCH_DIM_FUNC_ARG:
		case ZEND_FETCH_LIST_R:
		case ZEND_FETCH_LIST_W:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = t1 & ~(MAY_BE_RC1|MAY_BE_RCN);
				if (opline->opcode == ZEND_FETCH_DIM_W ||
				    opline->opcode == ZEND_FETCH_DIM_RW ||
				    opline->opcode == ZEND_FETCH_DIM_FUNC_ARG ||
                    opline->opcode == ZEND_FETCH_LIST_W) {
					if (t1 & (MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE)) {
						if (opline->opcode != ZEND_FETCH_DIM_FUNC_ARG) {
							tmp &= ~(MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE);
						}
						tmp |= MAY_BE_ARRAY | MAY_BE_RC1;
					}
					if (t1 & (MAY_BE_STRING|MAY_BE_ARRAY)) {
						tmp |= MAY_BE_RC1;
						if (opline->opcode == ZEND_FETCH_DIM_FUNC_ARG) {
							tmp |= t1 & MAY_BE_RCN;
						}
					}
					if (t1 & (MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
						tmp |= t1 & (MAY_BE_RC1|MAY_BE_RCN);
					}
					if (opline->op2_type == IS_UNUSED) {
						tmp |= MAY_BE_ARRAY_KEY_LONG;
					} else {
						if (t2 & (MAY_BE_LONG|MAY_BE_FALSE|MAY_BE_TRUE|MAY_BE_RESOURCE|MAY_BE_DOUBLE)) {
							tmp |= MAY_BE_ARRAY_KEY_LONG;
						}
						if (t2 & MAY_BE_STRING) {
							tmp |= MAY_BE_ARRAY_KEY_STRING;
							if (opline->op2_type != IS_CONST) {
								// FIXME: numeric string
								tmp |= MAY_BE_ARRAY_KEY_LONG;
							}
						}
						if (t2 & (MAY_BE_UNDEF | MAY_BE_NULL)) {
							tmp |= MAY_BE_ARRAY_KEY_STRING;
						}
					}
				} else if (opline->opcode == ZEND_FETCH_DIM_UNSET) {
					if (t1 & MAY_BE_ARRAY) {
						tmp |= MAY_BE_RC1;
					}
					if (t1 & (MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
						tmp |= t1 & (MAY_BE_RC1|MAY_BE_RCN);
					}
				}
				j = ssa_vars[ssa_ops[i].result_def].use_chain;
				while (j >= 0) {
					switch (op_array->opcodes[j].opcode) {
						case ZEND_FETCH_DIM_W:
						case ZEND_FETCH_DIM_RW:
						case ZEND_FETCH_DIM_FUNC_ARG:
						case ZEND_FETCH_LIST_W:
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
						case ZEND_ASSIGN_DIM:
							tmp |= MAY_BE_ARRAY | MAY_BE_ARRAY_OF_ARRAY;
							break;
						case ZEND_FETCH_OBJ_W:
						case ZEND_FETCH_OBJ_RW:
						case ZEND_FETCH_OBJ_FUNC_ARG:
						case ZEND_ASSIGN_OBJ:
						case ZEND_ASSIGN_OBJ_REF:
						case ZEND_PRE_INC_OBJ:
						case ZEND_PRE_DEC_OBJ:
						case ZEND_POST_INC_OBJ:
						case ZEND_POST_DEC_OBJ:
							tmp |= MAY_BE_ARRAY_OF_OBJECT;
							break;
						case ZEND_SEND_VAR_EX:
						case ZEND_SEND_FUNC_ARG:
						case ZEND_SEND_VAR_NO_REF:
						case ZEND_SEND_VAR_NO_REF_EX:
						case ZEND_SEND_REF:
						case ZEND_ASSIGN_REF:
						case ZEND_YIELD:
						case ZEND_INIT_ARRAY:
						case ZEND_ADD_ARRAY_ELEMENT:
						case ZEND_RETURN_BY_REF:
						case ZEND_VERIFY_RETURN_TYPE:
						case ZEND_MAKE_REF:
							tmp |= MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
							break;
						case ZEND_PRE_INC:
						case ZEND_PRE_DEC:
						case ZEND_POST_INC:
						case ZEND_POST_DEC:
							if (tmp & MAY_BE_ARRAY_OF_LONG) {
								/* may overflow */
								tmp |= MAY_BE_ARRAY_OF_DOUBLE;
							} else if (!(tmp & (MAY_BE_ARRAY_OF_LONG|MAY_BE_ARRAY_OF_DOUBLE))) {
								tmp |= MAY_BE_ARRAY_OF_LONG | MAY_BE_ARRAY_OF_DOUBLE;
							}
							break;
						case ZEND_UNSET_DIM:
						case ZEND_UNSET_OBJ:
						case ZEND_FETCH_DIM_UNSET:
						case ZEND_FETCH_OBJ_UNSET:
							break;
						default	:
							break;
					}
					j = zend_ssa_next_use(ssa_ops, ssa_ops[i].result_def, j);
				}
				if ((tmp & MAY_BE_ARRAY) && (tmp & MAY_BE_ARRAY_KEY_ANY)) {
					UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				} else {
					/* invalid key type */
					tmp = (tmp & (MAY_BE_RC1|MAY_BE_RCN)) | (t1 & ~(MAY_BE_RC1|MAY_BE_RCN));
					UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				}
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			/* FETCH_LIST on a string behaves like FETCH_R on null */
			tmp = zend_array_element_type(
				opline->opcode != ZEND_FETCH_LIST_R ? t1 : ((t1 & ~MAY_BE_STRING) | MAY_BE_NULL),
				opline->result_type == IS_VAR,
				opline->op2_type == IS_UNUSED);
			if (opline->opcode == ZEND_FETCH_DIM_W ||
			    opline->opcode == ZEND_FETCH_DIM_RW ||
			    opline->opcode == ZEND_FETCH_DIM_FUNC_ARG ||
			    opline->opcode == ZEND_FETCH_LIST_W) {
				if (t1 & (MAY_BE_ERROR|MAY_BE_TRUE|MAY_BE_LONG|MAY_BE_DOUBLE|MAY_BE_RESOURCE|MAY_BE_OBJECT)) {
					tmp |= MAY_BE_ERROR;
				} else if (opline->op2_type == IS_UNUSED) {
					tmp |= MAY_BE_ERROR;
				} else if (t2 & (MAY_BE_ARRAY|MAY_BE_OBJECT)) {
					tmp |= MAY_BE_ERROR;
				}
			} else if (opline->opcode == ZEND_FETCH_DIM_IS && (t1 & MAY_BE_STRING)) {
				tmp |= MAY_BE_NULL;
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			break;
		case ZEND_FETCH_THIS:
			UPDATE_SSA_OBJ_TYPE(op_array->scope, 1, ssa_ops[i].result_def);
			UPDATE_SSA_TYPE(MAY_BE_RC1|MAY_BE_RCN|MAY_BE_OBJECT, ssa_ops[i].result_def);
			break;
		case ZEND_FETCH_OBJ_R:
		case ZEND_FETCH_OBJ_IS:
		case ZEND_FETCH_OBJ_RW:
		case ZEND_FETCH_OBJ_W:
		case ZEND_FETCH_OBJ_UNSET:
		case ZEND_FETCH_OBJ_FUNC_ARG:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = t1;
				if (opline->opcode == ZEND_FETCH_OBJ_W ||
				    opline->opcode == ZEND_FETCH_OBJ_RW ||
				    opline->opcode == ZEND_FETCH_OBJ_FUNC_ARG) {
					if (opline->opcode != ZEND_FETCH_DIM_FUNC_ARG) {
						if (t1 & (MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE)) {
							tmp &= ~(MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE);
							tmp |= MAY_BE_OBJECT | MAY_BE_RC1 | MAY_BE_RCN;
						}
					}
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				COPY_SSA_OBJ_TYPE(ssa_ops[i].op1_use, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				tmp = zend_fetch_prop_type(script,
					zend_fetch_prop_info(op_array, ssa, opline, i), &ce);
				if (opline->result_type != IS_TMP_VAR) {
					tmp |= MAY_BE_REF | MAY_BE_ERROR;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
				if (ce) {
					UPDATE_SSA_OBJ_TYPE(ce, 1, ssa_ops[i].result_def);
				}
			}
			break;
		case ZEND_FETCH_STATIC_PROP_R:
		case ZEND_FETCH_STATIC_PROP_IS:
		case ZEND_FETCH_STATIC_PROP_RW:
		case ZEND_FETCH_STATIC_PROP_W:
		case ZEND_FETCH_STATIC_PROP_UNSET:
		case ZEND_FETCH_STATIC_PROP_FUNC_ARG:
			tmp = zend_fetch_prop_type(script,
				zend_fetch_static_prop_info(script, op_array, ssa, opline), &ce);
			if (opline->result_type != IS_TMP_VAR) {
				tmp |= MAY_BE_REF | MAY_BE_ERROR;
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			if (ce) {
				UPDATE_SSA_OBJ_TYPE(ce, 1, ssa_ops[i].result_def);
			}
			break;
		case ZEND_DO_FCALL:
		case ZEND_DO_ICALL:
		case ZEND_DO_UCALL:
		case ZEND_DO_FCALL_BY_NAME:
			if (ssa_ops[i].result_def >= 0) {
				zend_func_info *func_info = ZEND_FUNC_INFO(op_array);
				zend_call_info *call_info;

				if (!func_info || !func_info->call_map) {
					goto unknown_opcode;
				}
				call_info = func_info->call_map[opline - op_array->opcodes];
				if (!call_info) {
					goto unknown_opcode;
				}
				tmp = zend_get_func_info(call_info, ssa) & ~FUNC_MAY_WARN;
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
				if (call_info->callee_func->type == ZEND_USER_FUNCTION) {
					func_info = ZEND_FUNC_INFO(&call_info->callee_func->op_array);
					if (func_info) {
						UPDATE_SSA_OBJ_TYPE(
							func_info->return_info.ce,
							func_info->return_info.is_instanceof,
							ssa_ops[i].result_def);
					}
				}
			}
			break;
		case ZEND_FETCH_CONSTANT:
		case ZEND_FETCH_CLASS_CONSTANT:
			UPDATE_SSA_TYPE(MAY_BE_RC1|MAY_BE_RCN|MAY_BE_NULL|MAY_BE_FALSE|MAY_BE_TRUE|MAY_BE_LONG|MAY_BE_DOUBLE|MAY_BE_STRING|MAY_BE_RESOURCE|MAY_BE_ARRAY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY, ssa_ops[i].result_def);
			break;
		case ZEND_STRLEN:
			tmp = MAY_BE_LONG;
			if (t1 & (MAY_BE_ANY - (MAY_BE_NULL|MAY_BE_FALSE|MAY_BE_TRUE|MAY_BE_LONG|MAY_BE_DOUBLE|MAY_BE_STRING))) {
				tmp |= MAY_BE_NULL;
			}
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			break;
		case ZEND_COUNT:
		case ZEND_FUNC_NUM_ARGS:
			UPDATE_SSA_TYPE(MAY_BE_LONG, ssa_ops[i].result_def);
			break;
		case ZEND_FUNC_GET_ARGS:
			UPDATE_SSA_TYPE(MAY_BE_RC1| MAY_BE_ARRAY | MAY_BE_ARRAY_KEY_LONG | MAY_BE_ARRAY_OF_ANY, ssa_ops[i].result_def);
			break;
		case ZEND_GET_CLASS:
		case ZEND_GET_CALLED_CLASS:
			UPDATE_SSA_TYPE(MAY_BE_FALSE|MAY_BE_STRING|MAY_BE_RCN, ssa_ops[i].result_def);
			break;
		case ZEND_GET_TYPE:
			UPDATE_SSA_TYPE(MAY_BE_STRING|MAY_BE_RC1|MAY_BE_RCN, ssa_ops[i].result_def);
			break;
		case ZEND_TYPE_CHECK:
		case ZEND_DEFINED:
			UPDATE_SSA_TYPE(MAY_BE_FALSE|MAY_BE_TRUE, ssa_ops[i].result_def);
			break;
		case ZEND_VERIFY_RETURN_TYPE:
			if (t1 & MAY_BE_REF) {
				tmp = t1;
				ce = NULL;
			} else {
				zend_arg_info *ret_info = op_array->arg_info - 1;

				tmp = zend_fetch_arg_info(script, ret_info, &ce);
				if (tmp & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
					tmp |= MAY_BE_RC1 | MAY_BE_RCN;
				}
			}
			if (opline->op1_type & (IS_TMP_VAR|IS_VAR|IS_CV)) {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
				if (ce) {
					UPDATE_SSA_OBJ_TYPE(ce, 1, ssa_ops[i].op1_def);
				} else {
					UPDATE_SSA_OBJ_TYPE(NULL, 0, ssa_ops[i].op1_def);
				}
			} else {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
				if (ce) {
					UPDATE_SSA_OBJ_TYPE(ce, 1, ssa_ops[i].result_def);
				} else {
					UPDATE_SSA_OBJ_TYPE(NULL, 0, ssa_ops[i].result_def);
				}
			}
			break;
		case ZEND_MAKE_REF:
			tmp = MAY_BE_REF|MAY_BE_RC1|MAY_BE_RCN|MAY_BE_ANY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
			UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			if (ssa_ops[i].op1_def >= 0) {
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			break;
		case ZEND_CATCH:
		case ZEND_INCLUDE_OR_EVAL:
			/* Forbidden opcodes */
			ZEND_ASSERT(0);
			break;
		default:
unknown_opcode:
			if (ssa_ops[i].op1_def >= 0) {
				tmp = MAY_BE_ANY | MAY_BE_REF | MAY_BE_RC1 | MAY_BE_RCN | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].op1_def);
			}
			if (ssa_ops[i].result_def >= 0) {
				tmp = MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
				if (opline->result_type == IS_TMP_VAR) {
					tmp |= MAY_BE_RC1 | MAY_BE_RCN;
				} else {
					tmp |= MAY_BE_REF | MAY_BE_RC1 | MAY_BE_RCN;
				}
				UPDATE_SSA_TYPE(tmp, ssa_ops[i].result_def);
			}
			break;
	}

	return SUCCESS;
}