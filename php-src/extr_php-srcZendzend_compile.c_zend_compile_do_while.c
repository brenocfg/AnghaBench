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
typedef  int /*<<< orphan*/  znode ;
struct TYPE_5__ {struct TYPE_5__** child; } ;
typedef  TYPE_1__ zend_ast ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_JMPNZ ; 
 int /*<<< orphan*/  ZEND_NOP ; 
 int /*<<< orphan*/  get_next_op_number () ; 
 int /*<<< orphan*/  zend_begin_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_compile_expr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_compile_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_emit_cond_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_end_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void zend_compile_do_while(zend_ast *ast) /* {{{ */
{
	zend_ast *stmt_ast = ast->child[0];
	zend_ast *cond_ast = ast->child[1];

	znode cond_node;
	uint32_t opnum_start, opnum_cond;

	zend_begin_loop(ZEND_NOP, NULL, 0);

	opnum_start = get_next_op_number();
	zend_compile_stmt(stmt_ast);

	opnum_cond = get_next_op_number();
	zend_compile_expr(&cond_node, cond_ast);

	zend_emit_cond_jump(ZEND_JMPNZ, &cond_node, opnum_start);

	zend_end_loop(opnum_cond, NULL);
}