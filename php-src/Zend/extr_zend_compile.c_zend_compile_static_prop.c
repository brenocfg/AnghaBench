#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  constant; } ;
struct TYPE_24__ {scalar_t__ op_type; TYPE_1__ u; } ;
typedef  TYPE_2__ znode ;
struct TYPE_23__ {int /*<<< orphan*/  constant; } ;
struct TYPE_25__ {scalar_t__ op1_type; int /*<<< orphan*/  extended_value; TYPE_20__ op2; scalar_t__ op2_type; int /*<<< orphan*/  op1; } ;
typedef  TYPE_3__ zend_op ;
struct TYPE_26__ {struct TYPE_26__** child; } ;
typedef  TYPE_4__ zend_ast ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_VAR_FUNC_ARG ; 
 int /*<<< orphan*/  BP_VAR_W ; 
 int /*<<< orphan*/  CT_CONSTANT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CONST ; 
 int /*<<< orphan*/  SET_NODE (TYPE_20__,TYPE_2__*) ; 
 int /*<<< orphan*/  ZEND_FETCH_CLASS_EXCEPTION ; 
 int /*<<< orphan*/  ZEND_FETCH_REF ; 
 int /*<<< orphan*/  ZEND_FETCH_STATIC_PROP_R ; 
 int /*<<< orphan*/  Z_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_add_class_name_literal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_adjust_for_fetch_type (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_alloc_cache_slot () ; 
 int /*<<< orphan*/  zend_alloc_cache_slots (int) ; 
 int /*<<< orphan*/  zend_compile_class_ref (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_compile_expr (TYPE_2__*,TYPE_4__*) ; 
 TYPE_3__* zend_delayed_emit_op (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* zend_emit_op (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

zend_op *zend_compile_static_prop(znode *result, zend_ast *ast, uint32_t type, int by_ref, int delayed) /* {{{ */
{
	zend_ast *class_ast = ast->child[0];
	zend_ast *prop_ast = ast->child[1];

	znode class_node, prop_node;
	zend_op *opline;

	zend_compile_class_ref(&class_node, class_ast, ZEND_FETCH_CLASS_EXCEPTION);

	zend_compile_expr(&prop_node, prop_ast);

	if (delayed) {
		opline = zend_delayed_emit_op(result, ZEND_FETCH_STATIC_PROP_R, &prop_node, NULL);
	} else {
		opline = zend_emit_op(result, ZEND_FETCH_STATIC_PROP_R, &prop_node, NULL);
	}
	if (opline->op1_type == IS_CONST) {
		convert_to_string(CT_CONSTANT(opline->op1));
		opline->extended_value = zend_alloc_cache_slots(3);
	}
	if (class_node.op_type == IS_CONST) {
		opline->op2_type = IS_CONST;
		opline->op2.constant = zend_add_class_name_literal(
			Z_STR(class_node.u.constant));
		if (opline->op1_type != IS_CONST) {
			opline->extended_value = zend_alloc_cache_slot();
		}
	} else {
		SET_NODE(opline->op2, &class_node);
	}

	if (by_ref && (type == BP_VAR_W || type == BP_VAR_FUNC_ARG)) { /* shared with cache_slot */
		opline->extended_value |= ZEND_FETCH_REF;
	}

	zend_adjust_for_fetch_type(opline, result, type);
	return opline;
}