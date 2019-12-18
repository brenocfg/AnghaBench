#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {struct TYPE_5__** child; } ;
typedef  TYPE_1__ zend_ast ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_BIND_REF ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ast_get_str (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_compile_static_var_common (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_const_expr_to_zval (int /*<<< orphan*/ *,TYPE_1__*) ; 

void zend_compile_static_var(zend_ast *ast) /* {{{ */
{
	zend_ast *var_ast = ast->child[0];
	zend_ast *value_ast = ast->child[1];
	zval value_zv;

	if (value_ast) {
		zend_const_expr_to_zval(&value_zv, value_ast);
	} else {
		ZVAL_NULL(&value_zv);
	}

	zend_compile_static_var_common(zend_ast_get_str(var_ast), &value_zv, ZEND_BIND_REF);
}