#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_6__ {size_t children; TYPE_2__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_7__ {scalar_t__ kind; int /*<<< orphan*/  attr; struct TYPE_7__** child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 scalar_t__ ZEND_AST_ARRAY ; 
 TYPE_1__* zend_ast_get_list (TYPE_2__*) ; 

__attribute__((used)) static zend_bool zend_propagate_list_refs(zend_ast *ast) { /* {{{ */
	zend_ast_list *list = zend_ast_get_list(ast);
	zend_bool has_refs = 0;
	uint32_t i;

	for (i = 0; i < list->children; ++i) {
		zend_ast *elem_ast = list->child[i];

		if (elem_ast) {
			zend_ast *var_ast = elem_ast->child[0];
			if (var_ast->kind == ZEND_AST_ARRAY) {
				elem_ast->attr = zend_propagate_list_refs(var_ast);
			}
			has_refs |= elem_ast->attr;
		}
	}

	return has_refs;
}