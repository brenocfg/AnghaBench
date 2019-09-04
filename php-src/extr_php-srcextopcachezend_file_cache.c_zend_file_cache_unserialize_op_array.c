#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ op1_type; scalar_t__ op2_type; int type; struct TYPE_20__* name; int /*<<< orphan*/  op2; int /*<<< orphan*/  op1; } ;
typedef  TYPE_1__ zval ;
typedef  int /*<<< orphan*/  zend_type ;
typedef  TYPE_1__ zend_string ;
typedef  int /*<<< orphan*/  zend_persistent_script ;
struct TYPE_21__ {int last_literal; int last; int num_args; int fn_flags; int last_var; int /*<<< orphan*/  run_time_cache; TYPE_1__* static_variables; int /*<<< orphan*/  static_variables_ptr; TYPE_1__* prototype; TYPE_1__* try_catch_array; TYPE_1__* doc_comment; TYPE_1__* scope; TYPE_1__* live_range; TYPE_1__* filename; TYPE_1__* function_name; TYPE_1__** vars; TYPE_1__* arg_info; TYPE_1__* opcodes; TYPE_1__* literals; int /*<<< orphan*/ * refcount; } ;
typedef  TYPE_3__ zend_op_array ;
typedef  TYPE_1__ zend_op ;
typedef  int zend_bool ;
typedef  TYPE_1__ zend_arg_info ;
typedef  TYPE_1__ HashTable ;

/* Variables and functions */
 scalar_t__ IS_CONST ; 
 int /*<<< orphan*/  IS_UNSERIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_PTR (TYPE_1__*) ; 
 int /*<<< orphan*/  UNSERIALIZE_STR (TYPE_1__*) ; 
 int ZEND_ACC_HAS_RETURN_TYPE ; 
 int ZEND_ACC_IMMUTABLE ; 
 int ZEND_ACC_VARIADIC ; 
 TYPE_1__* ZEND_MAP_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_MAP_PTR_INIT (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  ZEND_MAP_PTR_NEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_PASS_TWO_UPDATE_CONSTANT (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ZEND_TYPE_ENCODE_CLASS (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ZVAL_PTR_DTOR ; 
 int Z_UL (int) ; 
 int /*<<< orphan*/  zend_deserialize_opcode_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_hash (TYPE_1__*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *,void*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_file_cache_unserialize_zval (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void zend_file_cache_unserialize_op_array(zend_op_array           *op_array,
                                                 zend_persistent_script  *script,
                                                 void                    *buf)
{
	if (op_array->static_variables && !IS_UNSERIALIZED(op_array->static_variables)) {
		HashTable *ht;

		UNSERIALIZE_PTR(op_array->static_variables);
		ht = op_array->static_variables;
		zend_file_cache_unserialize_hash(ht,
				script, buf, zend_file_cache_unserialize_zval, ZVAL_PTR_DTOR);
	}

	if (op_array->refcount) {
		op_array->refcount = NULL;
		UNSERIALIZE_PTR(op_array->literals);
		UNSERIALIZE_PTR(op_array->opcodes);
		UNSERIALIZE_PTR(op_array->arg_info);
		UNSERIALIZE_PTR(op_array->vars);
		UNSERIALIZE_STR(op_array->function_name);
		UNSERIALIZE_STR(op_array->filename);
		UNSERIALIZE_PTR(op_array->live_range);
		UNSERIALIZE_PTR(op_array->scope);
		UNSERIALIZE_STR(op_array->doc_comment);
		UNSERIALIZE_PTR(op_array->try_catch_array);
		UNSERIALIZE_PTR(op_array->prototype);
		return;
	}

	if (op_array->literals && !IS_UNSERIALIZED(op_array->literals)) {
		zval *p, *end;

		UNSERIALIZE_PTR(op_array->literals);
		p = op_array->literals;
		end = p + op_array->last_literal;
		while (p < end) {
			zend_file_cache_unserialize_zval(p, script, buf);
			p++;
		}
	}

	if (!IS_UNSERIALIZED(op_array->opcodes)) {
		zend_op *opline, *end;

		UNSERIALIZE_PTR(op_array->opcodes);
		opline = op_array->opcodes;
		end = opline + op_array->last;
		while (opline < end) {
#if ZEND_USE_ABS_CONST_ADDR
			if (opline->op1_type == IS_CONST) {
				UNSERIALIZE_PTR(opline->op1.zv);
			}
			if (opline->op2_type == IS_CONST) {
				UNSERIALIZE_PTR(opline->op2.zv);
			}
#else
			if (opline->op1_type == IS_CONST) {
				ZEND_PASS_TWO_UPDATE_CONSTANT(op_array, opline, opline->op1);
			}
			if (opline->op2_type == IS_CONST) {
				ZEND_PASS_TWO_UPDATE_CONSTANT(op_array, opline, opline->op2);
			}
#endif
#if ZEND_USE_ABS_JMP_ADDR
			switch (opline->opcode) {
				case ZEND_JMP:
				case ZEND_FAST_CALL:
					UNSERIALIZE_PTR(opline->op1.jmp_addr);
					break;
				case ZEND_JMPZNZ:
					/* relative extended_value don't have to be changed */
					/* break omitted intentionally */
				case ZEND_JMPZ:
				case ZEND_JMPNZ:
				case ZEND_JMPZ_EX:
				case ZEND_JMPNZ_EX:
				case ZEND_JMP_SET:
				case ZEND_COALESCE:
				case ZEND_FE_RESET_R:
				case ZEND_FE_RESET_RW:
				case ZEND_ASSERT_CHECK:
					UNSERIALIZE_PTR(opline->op2.jmp_addr);
					break;
				case ZEND_CATCH:
					if (!(opline->extended_value & ZEND_LAST_CATCH)) {
						UNSERIALIZE_PTR(opline->op2.jmp_addr);
					}
					break;
				case ZEND_DECLARE_ANON_CLASS:
				case ZEND_DECLARE_ANON_INHERITED_CLASS:
				case ZEND_FE_FETCH_R:
				case ZEND_FE_FETCH_RW:
				case ZEND_SWITCH_LONG:
				case ZEND_SWITCH_STRING:
					/* relative extended_value don't have to be changed */
					break;
			}
#endif
			zend_deserialize_opcode_handler(opline);
			opline++;
		}

		if (op_array->arg_info) {
			zend_arg_info *p, *end;
			UNSERIALIZE_PTR(op_array->arg_info);
			p = op_array->arg_info;
			end = p + op_array->num_args;
			if (op_array->fn_flags & ZEND_ACC_HAS_RETURN_TYPE) {
				p--;
			}
			if (op_array->fn_flags & ZEND_ACC_VARIADIC) {
				end++;
			}
			while (p < end) {
				if (!IS_UNSERIALIZED(p->name)) {
					UNSERIALIZE_STR(p->name);
				}
				if (p->type & (Z_UL(1) << (sizeof(zend_type)*8-1))) { /* type is class */
					zend_bool allow_null = (p->type & (Z_UL(1) << (sizeof(zend_type)*8-2))) != 0; /* type allow null */
					zend_string *type_name = (zend_string*)(p->type & ~(((Z_UL(1) << (sizeof(zend_type)*8-1))) | ((Z_UL(1) << (sizeof(zend_type)*8-2)))));

					UNSERIALIZE_STR(type_name);
					p->type = ZEND_TYPE_ENCODE_CLASS(type_name, allow_null);
				}
				p++;
			}
		}

		if (op_array->vars) {
			zend_string **p, **end;

			UNSERIALIZE_PTR(op_array->vars);
			p = op_array->vars;
			end = p + op_array->last_var;
			while (p < end) {
				if (!IS_UNSERIALIZED(*p)) {
					UNSERIALIZE_STR(*p);
				}
				p++;
			}
		}

		UNSERIALIZE_STR(op_array->function_name);
		UNSERIALIZE_STR(op_array->filename);
		UNSERIALIZE_PTR(op_array->live_range);
		UNSERIALIZE_PTR(op_array->scope);
		UNSERIALIZE_STR(op_array->doc_comment);
		UNSERIALIZE_PTR(op_array->try_catch_array);
		UNSERIALIZE_PTR(op_array->prototype);

		if (op_array->fn_flags & ZEND_ACC_IMMUTABLE) {
			if (op_array->static_variables) {
				ZEND_MAP_PTR_NEW(op_array->static_variables_ptr);
			} else {
				ZEND_MAP_PTR_INIT(op_array->static_variables_ptr, &op_array->static_variables);
			}
			ZEND_MAP_PTR_NEW(op_array->run_time_cache);
		} else {
			ZEND_MAP_PTR_INIT(op_array->static_variables_ptr, &op_array->static_variables);
			UNSERIALIZE_PTR(ZEND_MAP_PTR(op_array->run_time_cache));
		}
	}
}