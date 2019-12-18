#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  constant; } ;
struct TYPE_23__ {scalar_t__ op_type; TYPE_1__ u; } ;
typedef  TYPE_2__ znode ;
typedef  int /*<<< orphan*/  zend_op ;
typedef  int zend_bool ;
struct TYPE_24__ {scalar_t__ children; TYPE_4__** child; } ;
typedef  TYPE_3__ zend_ast_list ;
struct TYPE_25__ {scalar_t__ kind; int attr; struct TYPE_25__** child; } ;
typedef  TYPE_4__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ IS_CONST ; 
 scalar_t__ IS_CV ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ ZEND_AST_ARRAY ; 
 scalar_t__ ZEND_AST_UNPACK ; 
 int /*<<< orphan*/  ZEND_FETCH_DIM_W ; 
 int /*<<< orphan*/  ZEND_FETCH_LIST_R ; 
 int /*<<< orphan*/  ZEND_FETCH_LIST_W ; 
 int /*<<< orphan*/  ZEND_MAKE_REF ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_3__* zend_ast_get_list (TYPE_4__*) ; 
 int /*<<< orphan*/  zend_compile_expr (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  zend_do_free (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_emit_assign_ref_znode (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_emit_assign_znode (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * zend_emit_op (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zend_handle_numeric_dim (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zend_verify_list_assign_target (TYPE_4__*,int) ; 
 int /*<<< orphan*/  zval_make_interned_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_compile_list_assign(
		znode *result, zend_ast *ast, znode *expr_node, zend_bool old_style) /* {{{ */
{
	zend_ast_list *list = zend_ast_get_list(ast);
	uint32_t i;
	zend_bool has_elems = 0;
	zend_bool is_keyed =
		list->children > 0 && list->child[0] != NULL && list->child[0]->child[1] != NULL;

	if (list->children && expr_node->op_type == IS_CONST && Z_TYPE(expr_node->u.constant) == IS_STRING) {
		zval_make_interned_string(&expr_node->u.constant);
	}

	for (i = 0; i < list->children; ++i) {
		zend_ast *elem_ast = list->child[i];
		zend_ast *var_ast, *key_ast;
		znode fetch_result, dim_node;
		zend_op *opline;

		if (elem_ast == NULL) {
			if (is_keyed) {
				zend_error(E_COMPILE_ERROR,
					"Cannot use empty array entries in keyed array assignment");
			} else {
				continue;
			}
		}

		if (elem_ast->kind == ZEND_AST_UNPACK) {
			zend_error(E_COMPILE_ERROR,
					"Spread operator is not supported in assignments");
		}

		var_ast = elem_ast->child[0];
		key_ast = elem_ast->child[1];
		has_elems = 1;

		if (is_keyed) {
			if (key_ast == NULL) {
				zend_error(E_COMPILE_ERROR,
					"Cannot mix keyed and unkeyed array entries in assignments");
			}

			zend_compile_expr(&dim_node, key_ast);
		} else {
			if (key_ast != NULL) {
				zend_error(E_COMPILE_ERROR,
					"Cannot mix keyed and unkeyed array entries in assignments");
			}

			dim_node.op_type = IS_CONST;
			ZVAL_LONG(&dim_node.u.constant, i);
		}

		if (expr_node->op_type == IS_CONST) {
			Z_TRY_ADDREF(expr_node->u.constant);
		}

		zend_verify_list_assign_target(var_ast, old_style);

		opline = zend_emit_op(&fetch_result,
			elem_ast->attr ? (expr_node->op_type == IS_CV ? ZEND_FETCH_DIM_W : ZEND_FETCH_LIST_W) : ZEND_FETCH_LIST_R, expr_node, &dim_node);

		if (dim_node.op_type == IS_CONST) {
			zend_handle_numeric_dim(opline, &dim_node);
		}

		if (var_ast->kind == ZEND_AST_ARRAY) {
			if (elem_ast->attr) {
				zend_emit_op(&fetch_result, ZEND_MAKE_REF, &fetch_result, NULL);
			}
			zend_compile_list_assign(NULL, var_ast, &fetch_result, var_ast->attr);
		} else if (elem_ast->attr) {
			zend_emit_assign_ref_znode(var_ast, &fetch_result);
		} else {
			zend_emit_assign_znode(var_ast, &fetch_result);
		}
	}

	if (has_elems == 0) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot use empty list");
	}

	if (result) {
		*result = *expr_node;
	} else {
		zend_do_free(expr_node);
	}
}