#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_10__ {int last_var; int /*<<< orphan*/ * vars; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_11__ {size_t children; TYPE_3__** child; } ;
typedef  TYPE_2__ zend_ast_list ;
struct TYPE_12__ {size_t attr; } ;
typedef  TYPE_3__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 TYPE_1__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  active_op_array ; 
 TYPE_2__* zend_ast_get_list (TYPE_3__*) ; 
 int /*<<< orphan*/ * zend_ast_get_str (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_compile_static_var_common (TYPE_3__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_string_equals (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void zend_compile_closure_uses(zend_ast *ast) /* {{{ */
{
	zend_op_array *op_array = CG(active_op_array);
	zend_ast_list *list = zend_ast_get_list(ast);
	uint32_t i;

	for (i = 0; i < list->children; ++i) {
		zend_ast *var_ast = list->child[i];
		zend_string *var_name = zend_ast_get_str(var_ast);
		uint32_t by_ref = var_ast->attr;
		zval zv;
		ZVAL_NULL(&zv);

		{
			int i;
			for (i = 0; i < op_array->last_var; i++) {
				if (zend_string_equals(op_array->vars[i], var_name)) {
					zend_error_noreturn(E_COMPILE_ERROR,
						"Cannot use lexical variable $%s as a parameter name", ZSTR_VAL(var_name));
				}
			}
		}

		zend_compile_static_var_common(var_ast, &zv, by_ref);
	}
}