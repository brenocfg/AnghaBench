#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_8__ {size_t children; TYPE_2__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_9__ {scalar_t__ attr; int /*<<< orphan*/ * child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_AST_USE ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR_P (int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_ast_create_list (int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* zend_ast_get_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_ast_get_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_ast_get_zval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_compile_use (TYPE_2__*) ; 
 int /*<<< orphan*/ * zend_concat_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zend_compile_group_use(zend_ast *ast) /* {{{ */
{
	uint32_t i;
	zend_string *ns = zend_ast_get_str(ast->child[0]);
	zend_ast_list *list = zend_ast_get_list(ast->child[1]);

	for (i = 0; i < list->children; i++) {
		zend_ast *inline_use, *use = list->child[i];
		zval *name_zval = zend_ast_get_zval(use->child[0]);
		zend_string *name = Z_STR_P(name_zval);
		zend_string *compound_ns = zend_concat_names(ZSTR_VAL(ns), ZSTR_LEN(ns), ZSTR_VAL(name), ZSTR_LEN(name));
		zend_string_release_ex(name, 0);
		ZVAL_STR(name_zval, compound_ns);
		inline_use = zend_ast_create_list(1, ZEND_AST_USE, use);
		inline_use->attr = ast->attr ? ast->attr : use->attr;
		zend_compile_use(inline_use);
	}
}