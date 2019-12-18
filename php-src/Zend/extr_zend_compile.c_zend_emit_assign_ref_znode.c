#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  znode ;
typedef  int /*<<< orphan*/  zend_ast ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_AST_ASSIGN_REF ; 
 int /*<<< orphan*/ * zend_ast_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_ast_create_znode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_compile_assign_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void zend_emit_assign_ref_znode(zend_ast *var_ast, znode *value_node) /* {{{ */
{
	zend_ast *assign_ast = zend_ast_create(ZEND_AST_ASSIGN_REF, var_ast,
		zend_ast_create_znode(value_node));
	zend_compile_assign_ref(NULL, assign_ast);
}