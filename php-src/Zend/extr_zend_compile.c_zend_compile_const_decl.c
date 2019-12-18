#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_12__ {int /*<<< orphan*/  constant; } ;
struct TYPE_13__ {TYPE_1__ u; void* op_type; } ;
typedef  TYPE_2__ znode ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_14__ {size_t children; TYPE_4__** child; } ;
typedef  TYPE_3__ zend_ast_list ;
struct TYPE_15__ {struct TYPE_15__** child; } ;
typedef  TYPE_4__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ FC (int /*<<< orphan*/ ) ; 
 void* IS_CONST ; 
 int /*<<< orphan*/  ZEND_DECLARE_CONST ; 
 int /*<<< orphan*/  ZEND_SYMBOL_CONST ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imports_const ; 
 TYPE_3__* zend_ast_get_list (TYPE_4__*) ; 
 int /*<<< orphan*/ * zend_ast_get_str (TYPE_4__*) ; 
 int /*<<< orphan*/  zend_const_expr_to_zval (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  zend_emit_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_get_special_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_hash_find_ptr (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_new_interned_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_prefix_with_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_register_seen_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_equals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void zend_compile_const_decl(zend_ast *ast) /* {{{ */
{
	zend_ast_list *list = zend_ast_get_list(ast);
	uint32_t i;
	for (i = 0; i < list->children; ++i) {
		zend_ast *const_ast = list->child[i];
		zend_ast *name_ast = const_ast->child[0];
		zend_ast *value_ast = const_ast->child[1];
		zend_string *unqualified_name = zend_ast_get_str(name_ast);

		zend_string *name;
		znode name_node, value_node;
		zval *value_zv = &value_node.u.constant;

		value_node.op_type = IS_CONST;
		zend_const_expr_to_zval(value_zv, value_ast);

		if (zend_get_special_const(ZSTR_VAL(unqualified_name), ZSTR_LEN(unqualified_name))) {
			zend_error_noreturn(E_COMPILE_ERROR,
				"Cannot redeclare constant '%s'", ZSTR_VAL(unqualified_name));
		}

		name = zend_prefix_with_ns(unqualified_name);
		name = zend_new_interned_string(name);

		if (FC(imports_const)) {
			zend_string *import_name = zend_hash_find_ptr(FC(imports_const), unqualified_name);
			if (import_name && !zend_string_equals(import_name, name)) {
				zend_error_noreturn(E_COMPILE_ERROR, "Cannot declare const %s because "
					"the name is already in use", ZSTR_VAL(name));
			}
		}

		name_node.op_type = IS_CONST;
		ZVAL_STR(&name_node.u.constant, name);

		zend_emit_op(NULL, ZEND_DECLARE_CONST, &name_node, &value_node);

		zend_register_seen_symbol(name, ZEND_SYMBOL_CONST);
	}
}