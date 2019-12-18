#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_14__ {size_t children; TYPE_3__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_15__ {TYPE_3__** child; } ;
typedef  TYPE_2__ zend_ast_decl ;
struct TYPE_16__ {scalar_t__ kind; struct TYPE_16__** child; } ;
typedef  TYPE_3__ zend_ast ;
typedef  size_t uint32_t ;
struct TYPE_17__ {int varvars_used; int /*<<< orphan*/  uses; } ;
typedef  TYPE_4__ closure_info ;

/* Variables and functions */
 scalar_t__ IS_STRING ; 
 scalar_t__ ZEND_AST_ARROW_FUNC ; 
 scalar_t__ ZEND_AST_CLOSURE ; 
 scalar_t__ ZEND_AST_VAR ; 
 scalar_t__ ZEND_AST_ZVAL ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ ) ; 
 TYPE_1__* zend_ast_get_list (TYPE_3__*) ; 
 size_t zend_ast_get_num_children (TYPE_3__*) ; 
 int /*<<< orphan*/ * zend_ast_get_str (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_ast_get_zval (TYPE_3__*) ; 
 scalar_t__ zend_ast_is_list (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_ast_is_special (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_hash_add_empty_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_is_auto_global (int /*<<< orphan*/ *) ; 
 scalar_t__ zend_string_equals_literal (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void find_implicit_binds_recursively(closure_info *info, zend_ast *ast) {
	if (!ast) {
		return;
	}

	if (ast->kind == ZEND_AST_VAR) {
		zend_ast *name_ast = ast->child[0];
		if (name_ast->kind == ZEND_AST_ZVAL && Z_TYPE_P(zend_ast_get_zval(name_ast)) == IS_STRING) {
			zend_string *name = zend_ast_get_str(name_ast);
			if (zend_is_auto_global(name)) {
				/* These is no need to explicitly import auto-globals. */
				return;
			}

			if (zend_string_equals_literal(name, "this")) {
				/* $this does not need to be explicitly imported. */
				return;
			}

			zend_hash_add_empty_element(&info->uses, name);
		} else {
			info->varvars_used = 1;
			find_implicit_binds_recursively(info, name_ast);
		}
	} else if (zend_ast_is_list(ast)) {
		zend_ast_list *list = zend_ast_get_list(ast);
		uint32_t i;
		for (i = 0; i < list->children; i++) {
			find_implicit_binds_recursively(info, list->child[i]);
		}
	} else if (ast->kind == ZEND_AST_CLOSURE) {
		/* For normal closures add the use() list. */
		zend_ast_decl *closure_ast = (zend_ast_decl *) ast;
		zend_ast *uses_ast = closure_ast->child[1];
		if (uses_ast) {
			zend_ast_list *uses_list = zend_ast_get_list(uses_ast);
			uint32_t i;
			for (i = 0; i < uses_list->children; i++) {
				zend_hash_add_empty_element(&info->uses, zend_ast_get_str(uses_list->child[i]));
			}
		}
	} else if (ast->kind == ZEND_AST_ARROW_FUNC) {
		/* For arrow functions recursively check the expression. */
		zend_ast_decl *closure_ast = (zend_ast_decl *) ast;
		find_implicit_binds_recursively(info, closure_ast->child[2]);
	} else if (!zend_ast_is_special(ast)) {
		uint32_t i, children = zend_ast_get_num_children(ast);
		for (i = 0; i < children; i++) {
			find_implicit_binds_recursively(info, ast->child[i]);
		}
	}
}