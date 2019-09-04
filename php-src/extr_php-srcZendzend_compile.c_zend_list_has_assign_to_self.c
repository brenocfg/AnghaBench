#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_6__ {scalar_t__ kind; TYPE_5__** child; } ;
typedef  TYPE_1__ zend_ast ;
struct TYPE_7__ {scalar_t__ kind; } ;

/* Variables and functions */
 scalar_t__ ZEND_AST_VAR ; 
 scalar_t__ ZEND_AST_ZVAL ; 
 int /*<<< orphan*/  zend_ast_get_zval (TYPE_5__*) ; 
 int /*<<< orphan*/  zend_list_has_assign_to (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_get_string (int /*<<< orphan*/ ) ; 

zend_bool zend_list_has_assign_to_self(zend_ast *list_ast, zend_ast *expr_ast) /* {{{ */
{
	/* Only check simple variables on the RHS, as only CVs cause issues with this. */
	if (expr_ast->kind == ZEND_AST_VAR && expr_ast->child[0]->kind == ZEND_AST_ZVAL) {
		zend_string *name = zval_get_string(zend_ast_get_zval(expr_ast->child[0]));
		zend_bool result = zend_list_has_assign_to(list_ast, name);
		zend_string_release_ex(name, 0);
		return result;
	}
	return 0;
}