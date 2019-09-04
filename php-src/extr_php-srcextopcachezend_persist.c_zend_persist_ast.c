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
struct TYPE_11__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ zend_ast_zval ;
struct TYPE_12__ {int children; TYPE_3__** child; } ;
typedef  TYPE_2__ zend_ast_list ;
struct TYPE_13__ {scalar_t__ kind; struct TYPE_13__** child; } ;
typedef  TYPE_3__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 scalar_t__ ZEND_AST_CONSTANT ; 
 scalar_t__ ZEND_AST_ZVAL ; 
 TYPE_2__* zend_ast_get_list (TYPE_3__*) ; 
 size_t zend_ast_get_num_children (TYPE_3__*) ; 
 scalar_t__ zend_ast_is_list (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_persist_zval (int /*<<< orphan*/ *) ; 
 void* zend_shared_memdup (TYPE_3__*,int) ; 

__attribute__((used)) static zend_ast *zend_persist_ast(zend_ast *ast)
{
	uint32_t i;
	zend_ast *node;

	if (ast->kind == ZEND_AST_ZVAL || ast->kind == ZEND_AST_CONSTANT) {
		zend_ast_zval *copy = zend_shared_memdup(ast, sizeof(zend_ast_zval));
		zend_persist_zval(&copy->val);
		node = (zend_ast *) copy;
	} else if (zend_ast_is_list(ast)) {
		zend_ast_list *list = zend_ast_get_list(ast);
		zend_ast_list *copy = zend_shared_memdup(ast,
			sizeof(zend_ast_list) - sizeof(zend_ast *) + sizeof(zend_ast *) * list->children);
		for (i = 0; i < list->children; i++) {
			if (copy->child[i]) {
				copy->child[i] = zend_persist_ast(copy->child[i]);
			}
		}
		node = (zend_ast *) copy;
	} else {
		uint32_t children = zend_ast_get_num_children(ast);
		node = zend_shared_memdup(ast, sizeof(zend_ast) - sizeof(zend_ast *) + sizeof(zend_ast *) * children);
		for (i = 0; i < children; i++) {
			if (node->child[i]) {
				node->child[i] = zend_persist_ast(node->child[i]);
			}
		}
	}

	return node;
}