#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode ;
struct TYPE_20__ {int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ zend_op ;
struct TYPE_21__ {int kind; int /*<<< orphan*/  attr; struct TYPE_21__** child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_VAR_R ; 
 int /*<<< orphan*/  BP_VAR_W ; 
 int /*<<< orphan*/  EMPTY_SWITCH_DEFAULT_CASE () ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  ZEND_ASSIGN ; 
 int /*<<< orphan*/  ZEND_ASSIGN_DIM ; 
 int /*<<< orphan*/  ZEND_ASSIGN_OBJ ; 
 int /*<<< orphan*/  ZEND_ASSIGN_STATIC_PROP ; 
#define  ZEND_AST_ARRAY 132 
#define  ZEND_AST_DIM 131 
#define  ZEND_AST_PROP 130 
#define  ZEND_AST_STATIC_PROP 129 
#define  ZEND_AST_VAR 128 
 int /*<<< orphan*/  ZEND_MAKE_REF ; 
 int /*<<< orphan*/  ZEND_QM_ASSIGN ; 
 scalar_t__ is_this_fetch (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_compile_expr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_compile_list_assign (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_compile_simple_var_no_cv (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_compile_var (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_delayed_compile_begin () ; 
 int /*<<< orphan*/  zend_delayed_compile_dim (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* zend_delayed_compile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_delayed_compile_prop (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_delayed_compile_var (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_emit_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* zend_emit_op_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_emit_op_tmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ensure_writable_variable (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_is_assign_to_self (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_is_variable_or_call (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_propagate_list_refs (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_try_compile_cv (int /*<<< orphan*/ *,TYPE_2__*) ; 

void zend_compile_assign(znode *result, zend_ast *ast) /* {{{ */
{
	zend_ast *var_ast = ast->child[0];
	zend_ast *expr_ast = ast->child[1];

	znode var_node, expr_node;
	zend_op *opline;
	uint32_t offset;

	if (is_this_fetch(var_ast)) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot re-assign $this");
	}

	zend_ensure_writable_variable(var_ast);

	switch (var_ast->kind) {
		case ZEND_AST_VAR:
			offset = zend_delayed_compile_begin();
			zend_delayed_compile_var(&var_node, var_ast, BP_VAR_W, 0);
			zend_compile_expr(&expr_node, expr_ast);
			zend_delayed_compile_end(offset);
			zend_emit_op(result, ZEND_ASSIGN, &var_node, &expr_node);
			return;
		case ZEND_AST_STATIC_PROP:
			offset = zend_delayed_compile_begin();
			zend_delayed_compile_var(result, var_ast, BP_VAR_W, 0);
			zend_compile_expr(&expr_node, expr_ast);

			opline = zend_delayed_compile_end(offset);
			opline->opcode = ZEND_ASSIGN_STATIC_PROP;

			zend_emit_op_data(&expr_node);
			return;
		case ZEND_AST_DIM:
			offset = zend_delayed_compile_begin();
			zend_delayed_compile_dim(result, var_ast, BP_VAR_W);

			if (zend_is_assign_to_self(var_ast, expr_ast)
			 && !is_this_fetch(expr_ast)) {
				/* $a[0] = $a should evaluate the right $a first */
				znode cv_node;

				if (zend_try_compile_cv(&cv_node, expr_ast) == FAILURE) {
					zend_compile_simple_var_no_cv(&expr_node, expr_ast, BP_VAR_R, 0);
				} else {
					zend_emit_op_tmp(&expr_node, ZEND_QM_ASSIGN, &cv_node, NULL);
				}
			} else {
				zend_compile_expr(&expr_node, expr_ast);
			}

			opline = zend_delayed_compile_end(offset);
			opline->opcode = ZEND_ASSIGN_DIM;

			opline = zend_emit_op_data(&expr_node);
			return;
		case ZEND_AST_PROP:
			offset = zend_delayed_compile_begin();
			zend_delayed_compile_prop(result, var_ast, BP_VAR_W);
			zend_compile_expr(&expr_node, expr_ast);

			opline = zend_delayed_compile_end(offset);
			opline->opcode = ZEND_ASSIGN_OBJ;

			zend_emit_op_data(&expr_node);
			return;
		case ZEND_AST_ARRAY:
			if (zend_propagate_list_refs(var_ast)) {
				if (!zend_is_variable_or_call(expr_ast)) {
					zend_error_noreturn(E_COMPILE_ERROR,
						"Cannot assign reference to non referencable value");
				}

				zend_compile_var(&expr_node, expr_ast, BP_VAR_W, 1);
				/* MAKE_REF is usually not necessary for CVs. However, if there are
				 * self-assignments, this forces the RHS to evaluate first. */
				zend_emit_op(&expr_node, ZEND_MAKE_REF, &expr_node, NULL);
			} else {
				if (expr_ast->kind == ZEND_AST_VAR) {
					/* list($a, $b) = $a should evaluate the right $a first */
					znode cv_node;

					if (zend_try_compile_cv(&cv_node, expr_ast) == FAILURE) {
						zend_compile_simple_var_no_cv(&expr_node, expr_ast, BP_VAR_R, 0);
					} else {
						zend_emit_op_tmp(&expr_node, ZEND_QM_ASSIGN, &cv_node, NULL);
					}
				} else {
					zend_compile_expr(&expr_node, expr_ast);
				}
			}

			zend_compile_list_assign(result, var_ast, &expr_node, var_ast->attr);
			return;
		EMPTY_SWITCH_DEFAULT_CASE();
	}
}