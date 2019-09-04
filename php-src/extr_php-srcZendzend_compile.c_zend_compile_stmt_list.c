#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t children; int /*<<< orphan*/ * child; } ;
typedef  TYPE_1__ zend_ast_list ;
typedef  int /*<<< orphan*/  zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 TYPE_1__* zend_ast_get_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_compile_stmt (int /*<<< orphan*/ ) ; 

void zend_compile_stmt_list(zend_ast *ast) /* {{{ */
{
	zend_ast_list *list = zend_ast_get_list(ast);
	uint32_t i;
	for (i = 0; i < list->children; ++i) {
		zend_compile_stmt(list->child[i]);
	}
}