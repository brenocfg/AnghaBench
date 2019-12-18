#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode ;
struct TYPE_4__ {struct TYPE_4__** child; } ;
typedef  TYPE_1__ zend_ast ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_THROW ; 
 int /*<<< orphan*/  zend_compile_expr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_emit_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void zend_compile_throw(zend_ast *ast) /* {{{ */
{
	zend_ast *expr_ast = ast->child[0];

	znode expr_node;
	zend_compile_expr(&expr_node, expr_ast);

	zend_emit_op(NULL, ZEND_THROW, &expr_node, NULL);
}