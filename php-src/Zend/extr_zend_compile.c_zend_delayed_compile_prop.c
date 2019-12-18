#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  op_type; } ;
typedef  TYPE_1__ znode ;
struct TYPE_25__ {scalar_t__ op2_type; int /*<<< orphan*/  extended_value; int /*<<< orphan*/  op2; } ;
typedef  TYPE_2__ zend_op ;
struct TYPE_26__ {struct TYPE_26__** child; } ;
typedef  TYPE_3__ zend_ast ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_24__ {int /*<<< orphan*/  fn_flags; } ;

/* Variables and functions */
 TYPE_22__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CT_CONSTANT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CONST ; 
 int /*<<< orphan*/  IS_UNUSED ; 
 int /*<<< orphan*/  ZEND_ACC_USES_THIS ; 
 int /*<<< orphan*/  ZEND_FETCH_OBJ_R ; 
 int /*<<< orphan*/  ZEND_FETCH_THIS ; 
 int /*<<< orphan*/  active_op_array ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ ) ; 
 scalar_t__ is_this_fetch (TYPE_3__*) ; 
 scalar_t__ this_guaranteed_exists () ; 
 int /*<<< orphan*/  zend_adjust_for_fetch_type (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_alloc_cache_slots (int) ; 
 int /*<<< orphan*/  zend_compile_expr (TYPE_1__*,TYPE_3__*) ; 
 TYPE_2__* zend_delayed_compile_var (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zend_delayed_emit_op (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zend_emit_op (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_separate_if_call_and_write (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_op *zend_delayed_compile_prop(znode *result, zend_ast *ast, uint32_t type) /* {{{ */
{
	zend_ast *obj_ast = ast->child[0];
	zend_ast *prop_ast = ast->child[1];

	znode obj_node, prop_node;
	zend_op *opline;

	if (is_this_fetch(obj_ast)) {
		if (this_guaranteed_exists()) {
			obj_node.op_type = IS_UNUSED;
		} else {
			zend_emit_op(&obj_node, ZEND_FETCH_THIS, NULL, NULL);
		}
		CG(active_op_array)->fn_flags |= ZEND_ACC_USES_THIS;
	} else {
		opline = zend_delayed_compile_var(&obj_node, obj_ast, type, 0);
		zend_separate_if_call_and_write(&obj_node, obj_ast, type);
	}
	zend_compile_expr(&prop_node, prop_ast);

	opline = zend_delayed_emit_op(result, ZEND_FETCH_OBJ_R, &obj_node, &prop_node);
	if (opline->op2_type == IS_CONST) {
		convert_to_string(CT_CONSTANT(opline->op2));
		opline->extended_value = zend_alloc_cache_slots(3);
	}

	zend_adjust_for_fetch_type(opline, result, type);
	return opline;
}