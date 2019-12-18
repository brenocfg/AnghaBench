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
struct TYPE_11__ {size_t children; TYPE_2__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_12__ {int /*<<< orphan*/ * child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  size_t uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  uses; } ;
typedef  TYPE_3__ closure_info ;

/* Variables and functions */
 int /*<<< orphan*/  find_implicit_binds_recursively (TYPE_3__*,TYPE_2__*) ; 
 TYPE_1__* zend_ast_get_list (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_ast_get_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_implicit_binds(closure_info *info, zend_ast *params_ast, zend_ast *stmt_ast)
{
	zend_ast_list *param_list = zend_ast_get_list(params_ast);
	uint32_t i;

	zend_hash_init(&info->uses, param_list->children, NULL, NULL, 0);

	find_implicit_binds_recursively(info, stmt_ast);

	/* Remove variables that are parameters */
	for (i = 0; i < param_list->children; i++) {
		zend_ast *param_ast = param_list->child[i];
		zend_hash_del(&info->uses, zend_ast_get_str(param_ast->child[1]));
	}
}