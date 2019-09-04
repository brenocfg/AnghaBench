#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
typedef  int zend_bool ;
struct TYPE_7__ {size_t children; TYPE_2__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_8__ {scalar_t__ kind; struct TYPE_8__** child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 scalar_t__ ZEND_AST_ARRAY ; 
 scalar_t__ ZEND_AST_VAR ; 
 scalar_t__ ZEND_AST_ZVAL ; 
 TYPE_1__* zend_ast_get_list (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_ast_get_zval (TYPE_2__*) ; 
 int zend_string_equals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_get_string (int /*<<< orphan*/ ) ; 

zend_bool zend_list_has_assign_to(zend_ast *list_ast, zend_string *name) /* {{{ */
{
	zend_ast_list *list = zend_ast_get_list(list_ast);
	uint32_t i;
	for (i = 0; i < list->children; i++) {
		zend_ast *elem_ast = list->child[i];
		zend_ast *var_ast;

		if (!elem_ast) {
			continue;
		}
		var_ast = elem_ast->child[0];

		/* Recursively check nested list()s */
		if (var_ast->kind == ZEND_AST_ARRAY && zend_list_has_assign_to(var_ast, name)) {
			return 1;
		}

		if (var_ast->kind == ZEND_AST_VAR && var_ast->child[0]->kind == ZEND_AST_ZVAL) {
			zend_string *var_name = zval_get_string(zend_ast_get_zval(var_ast->child[0]));
			zend_bool result = zend_string_equals(var_name, name);
			zend_string_release_ex(var_name, 0);
			if (result) {
				return 1;
			}
		}
	}

	return 0;
}