#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  var; } ;
struct TYPE_24__ {int /*<<< orphan*/  constant; TYPE_1__ op; } ;
struct TYPE_26__ {scalar_t__ op_type; TYPE_3__ u; } ;
typedef  TYPE_5__ znode ;
struct TYPE_21__ {int /*<<< orphan*/  constant; } ;
struct TYPE_25__ {int /*<<< orphan*/  num; } ;
struct TYPE_23__ {int /*<<< orphan*/  var; } ;
struct TYPE_27__ {scalar_t__ result_type; TYPE_19__ op1; TYPE_4__ op2; scalar_t__ op1_type; TYPE_2__ result; } ;
typedef  TYPE_6__ zend_op ;
struct TYPE_28__ {scalar_t__ kind; struct TYPE_28__** child; } ;
typedef  TYPE_7__ zend_ast ;

/* Variables and functions */
 scalar_t__ IS_CONST ; 
 int /*<<< orphan*/  SET_NODE (TYPE_19__,TYPE_5__*) ; 
 scalar_t__ ZEND_AST_CLASS ; 
 int /*<<< orphan*/  ZEND_FETCH_CLASS_EXCEPTION ; 
 int /*<<< orphan*/  ZEND_NEW ; 
 int /*<<< orphan*/  Z_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_add_class_name_literal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_alloc_cache_slot () ; 
 int /*<<< orphan*/  zend_compile_call_common (TYPE_5__*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* zend_compile_class_decl (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_compile_class_ref (TYPE_5__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_do_free (TYPE_5__*) ; 
 TYPE_6__* zend_emit_op (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void zend_compile_new(znode *result, zend_ast *ast) /* {{{ */
{
	zend_ast *class_ast = ast->child[0];
	zend_ast *args_ast = ast->child[1];

	znode class_node, ctor_result;
	zend_op *opline;

	if (class_ast->kind == ZEND_AST_CLASS) {
		/* anon class declaration */
		opline = zend_compile_class_decl(class_ast, 0);
		class_node.op_type = opline->result_type;
		class_node.u.op.var = opline->result.var;
	} else {
		zend_compile_class_ref(&class_node, class_ast, ZEND_FETCH_CLASS_EXCEPTION);
	}

	opline = zend_emit_op(result, ZEND_NEW, NULL, NULL);

	if (class_node.op_type == IS_CONST) {
		opline->op1_type = IS_CONST;
		opline->op1.constant = zend_add_class_name_literal(
			Z_STR(class_node.u.constant));
		opline->op2.num = zend_alloc_cache_slot();
	} else {
		SET_NODE(opline->op1, &class_node);
	}

	zend_compile_call_common(&ctor_result, args_ast, NULL);
	zend_do_free(&ctor_result);
}