#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_11__ {int fn_flags; int /*<<< orphan*/ * function_name; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_12__ {int /*<<< orphan*/  op1; void* op1_type; int /*<<< orphan*/  opcode; int /*<<< orphan*/  extended_value; } ;
typedef  TYPE_2__ zend_op ;
typedef  scalar_t__ zend_bool ;
struct TYPE_13__ {int /*<<< orphan*/  lex_pos; int /*<<< orphan*/ * name; } ;
typedef  TYPE_3__ zend_ast_decl ;

/* Variables and functions */
 int /*<<< orphan*/  CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ FC (int /*<<< orphan*/ ) ; 
 void* IS_CONST ; 
 int /*<<< orphan*/  LITERAL_STR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ UNEXPECTED (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_CLOSURE ; 
 int /*<<< orphan*/  ZEND_DECLARE_FUNCTION ; 
 int /*<<< orphan*/  ZEND_DECLARE_LAMBDA_FUNCTION ; 
 int /*<<< orphan*/  ZEND_SYMBOL_FUNCTION ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_bind_function_error (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  function_table ; 
 TYPE_2__* get_next_op () ; 
 int /*<<< orphan*/  imports_function ; 
 int /*<<< orphan*/  zend_add_literal_string (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zend_alloc_cache_slot () ; 
 int /*<<< orphan*/ * zend_build_runtime_definition_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* zend_emit_op_tmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * zend_hash_add_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr_lc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_update_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zend_prefix_with_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_register_seen_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_equals_ci (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_string_equals_literal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ zend_string_equals_literal_ci (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_begin_func_decl(znode *result, zend_op_array *op_array, zend_ast_decl *decl, zend_bool toplevel) /* {{{ */
{
	zend_string *unqualified_name, *name, *lcname, *key;
	zend_op *opline;

	unqualified_name = decl->name;
	op_array->function_name = name = zend_prefix_with_ns(unqualified_name);
	lcname = zend_string_tolower(name);

	if (FC(imports_function)) {
		zend_string *import_name = zend_hash_find_ptr_lc(
			FC(imports_function), ZSTR_VAL(unqualified_name), ZSTR_LEN(unqualified_name));
		if (import_name && !zend_string_equals_ci(lcname, import_name)) {
			zend_error_noreturn(E_COMPILE_ERROR, "Cannot declare function %s "
				"because the name is already in use", ZSTR_VAL(name));
		}
	}

	if (zend_string_equals_literal(lcname, "__autoload")) {
		zend_error_noreturn(E_COMPILE_ERROR,
			"__autoload() is no longer supported, use spl_autoload_register() instead");
	}

	if (zend_string_equals_literal_ci(unqualified_name, "assert")) {
		zend_error(E_COMPILE_ERROR,
			"Defining a custom assert() function is not allowed, "
			"as the function has special semantics");
	}

	zend_register_seen_symbol(lcname, ZEND_SYMBOL_FUNCTION);
	if (toplevel) {
		if (UNEXPECTED(zend_hash_add_ptr(CG(function_table), lcname, op_array) == NULL)) {
			do_bind_function_error(lcname, op_array, 1);
		}
		zend_string_release_ex(lcname, 0);
		return;
	}

	key = zend_build_runtime_definition_key(lcname, decl->lex_pos);
	zend_hash_update_ptr(CG(function_table), key, op_array);

	if (op_array->fn_flags & ZEND_ACC_CLOSURE) {
		opline = zend_emit_op_tmp(result, ZEND_DECLARE_LAMBDA_FUNCTION, NULL, NULL);
		opline->extended_value = zend_alloc_cache_slot();
		opline->op1_type = IS_CONST;
		LITERAL_STR(opline->op1, key);
	} else {
		opline = get_next_op();
		opline->opcode = ZEND_DECLARE_FUNCTION;
		opline->op1_type = IS_CONST;
		LITERAL_STR(opline->op1, zend_string_copy(lcname));
		/* RTD key is placed after lcname literal in op1 */
		zend_add_literal_string(&key);
	}
	zend_string_release_ex(lcname, 0);
}