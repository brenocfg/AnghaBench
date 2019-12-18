#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ op_type; } ;
typedef  TYPE_1__ znode ;
struct TYPE_20__ {scalar_t__ opcode; int /*<<< orphan*/  extended_value; } ;
typedef  TYPE_2__ zend_op ;
struct TYPE_21__ {scalar_t__ kind; struct TYPE_21__** child; } ;
typedef  TYPE_3__ zend_ast ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_VAR_W ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 scalar_t__ IS_CV ; 
 scalar_t__ IS_VAR ; 
 scalar_t__ ZEND_ASSIGN_OBJ_REF ; 
 int /*<<< orphan*/  ZEND_ASSIGN_REF ; 
 scalar_t__ ZEND_ASSIGN_STATIC_PROP_REF ; 
 scalar_t__ ZEND_AST_VAR ; 
 scalar_t__ ZEND_AST_ZVAL ; 
 scalar_t__ ZEND_FETCH_OBJ_W ; 
 int /*<<< orphan*/  ZEND_FETCH_REF ; 
 scalar_t__ ZEND_FETCH_STATIC_PROP_W ; 
 int /*<<< orphan*/  ZEND_MAKE_REF ; 
 int /*<<< orphan*/  ZEND_RETURNS_FUNCTION ; 
 scalar_t__ is_this_fetch (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_compile_var (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_delayed_compile_begin () ; 
 TYPE_2__* zend_delayed_compile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_delayed_compile_var (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* zend_emit_op (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_emit_op_data (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_ensure_writable_variable (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zend_is_call (TYPE_3__*) ; 

void zend_compile_assign_ref(znode *result, zend_ast *ast) /* {{{ */
{
	zend_ast *target_ast = ast->child[0];
	zend_ast *source_ast = ast->child[1];

	znode target_node, source_node;
	zend_op *opline;
	uint32_t offset, flags;

	if (is_this_fetch(target_ast)) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot re-assign $this");
	}
	zend_ensure_writable_variable(target_ast);

	offset = zend_delayed_compile_begin();
	zend_delayed_compile_var(&target_node, target_ast, BP_VAR_W, 1);
	zend_compile_var(&source_node, source_ast, BP_VAR_W, 1);

	if ((target_ast->kind != ZEND_AST_VAR
	  || target_ast->child[0]->kind != ZEND_AST_ZVAL)
	 && source_node.op_type != IS_CV) {
		/* Both LHS and RHS expressions may modify the same data structure,
		 * and the modification during RHS evaluation may dangle the pointer
		 * to the result of the LHS evaluation.
		 * Use MAKE_REF instruction to replace direct pointer with REFERENCE.
		 * See: Bug #71539
		 */
		zend_emit_op(&source_node, ZEND_MAKE_REF, &source_node, NULL);
	}

	opline = zend_delayed_compile_end(offset);

	if (source_node.op_type != IS_VAR && zend_is_call(source_ast)) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot use result of built-in function in write context");
	}

	flags = zend_is_call(source_ast) ? ZEND_RETURNS_FUNCTION : 0;

	if (opline && opline->opcode == ZEND_FETCH_OBJ_W) {
		opline->opcode = ZEND_ASSIGN_OBJ_REF;
		opline->extended_value &= ~ZEND_FETCH_REF;
		opline->extended_value |= flags;
		zend_emit_op_data(&source_node);
		if (result != NULL) {
			*result = target_node;
		}
	} else if (opline && opline->opcode == ZEND_FETCH_STATIC_PROP_W) {
		opline->opcode = ZEND_ASSIGN_STATIC_PROP_REF;
		opline->extended_value &= ~ZEND_FETCH_REF;
		opline->extended_value |= flags;
		zend_emit_op_data(&source_node);
		if (result != NULL) {
			*result = target_node;
		}
	} else {
		opline = zend_emit_op(result, ZEND_ASSIGN_REF, &target_node, &source_node);
		opline->extended_value = flags;
	}
}