#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int op_type; } ;
typedef  TYPE_3__ znode ;
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_24__ {size_t var; } ;
struct TYPE_23__ {size_t num; size_t opline_num; } ;
struct TYPE_26__ {TYPE_2__ result; TYPE_1__ op2; } ;
typedef  TYPE_4__ zend_op ;
typedef  scalar_t__ zend_intptr_t ;
typedef  int /*<<< orphan*/  zend_function ;
typedef  int zend_bool ;
struct TYPE_27__ {size_t children; TYPE_6__** child; } ;
typedef  TYPE_5__ zend_ast_list ;
struct TYPE_28__ {scalar_t__ kind; struct TYPE_28__** child; } ;
typedef  TYPE_6__ zend_ast ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  CG ;

/* Variables and functions */
 scalar_t__ ARG_MAY_BE_SENT_BY_REF (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ARG_MUST_BE_SENT_BY_REF (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ARG_SHOULD_BE_SENT_BY_REF (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  BP_VAR_FUNC_ARG ; 
 int /*<<< orphan*/  BP_VAR_R ; 
 int /*<<< orphan*/  BP_VAR_W ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int IS_CONST ; 
 int IS_CV ; 
 int IS_TMP_VAR ; 
 int IS_VAR ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ ZEND_AST_UNPACK ; 
 scalar_t__ ZEND_AST_VAR ; 
 scalar_t__ ZEND_CALL_ARG (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ZEND_CHECK_FUNC_ARG ; 
 int /*<<< orphan*/  ZEND_FETCH_THIS ; 
 int /*<<< orphan*/  ZEND_SEND_FUNC_ARG ; 
 int /*<<< orphan*/  ZEND_SEND_REF ; 
 int /*<<< orphan*/  ZEND_SEND_UNPACK ; 
 int /*<<< orphan*/  ZEND_SEND_VAL ; 
 int /*<<< orphan*/  ZEND_SEND_VAL_EX ; 
 int /*<<< orphan*/  ZEND_SEND_VAR ; 
 int /*<<< orphan*/  ZEND_SEND_VAR_EX ; 
 int /*<<< orphan*/  ZEND_SEND_VAR_NO_REF ; 
 int /*<<< orphan*/  ZEND_SEND_VAR_NO_REF_EX ; 
 scalar_t__ is_this_fetch (TYPE_6__*) ; 
 int /*<<< orphan*/  zend_ast_get_lineno (TYPE_6__*) ; 
 TYPE_5__* zend_ast_get_list (TYPE_6__*) ; 
 int /*<<< orphan*/  zend_compile_expr (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  zend_compile_var (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* zend_emit_op (TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zend_is_call (TYPE_6__*) ; 
 scalar_t__ zend_is_variable (TYPE_6__*) ; 
 scalar_t__ zend_try_compile_cv (TYPE_3__*,TYPE_6__*) ; 

uint32_t zend_compile_args(zend_ast *ast, zend_function *fbc) /* {{{ */
{
	zend_ast_list *args = zend_ast_get_list(ast);
	uint32_t i;
	zend_bool uses_arg_unpack = 0;
	uint32_t arg_count = 0; /* number of arguments not including unpacks */

	for (i = 0; i < args->children; ++i) {
		zend_ast *arg = args->child[i];
		uint32_t arg_num = i + 1;

		znode arg_node;
		zend_op *opline;
		zend_uchar opcode;

		if (arg->kind == ZEND_AST_UNPACK) {
			uses_arg_unpack = 1;
			fbc = NULL;

			zend_compile_expr(&arg_node, arg->child[0]);
			opline = zend_emit_op(NULL, ZEND_SEND_UNPACK, &arg_node, NULL);
			opline->op2.num = arg_count;
			opline->result.var = (uint32_t)(zend_intptr_t)ZEND_CALL_ARG(NULL, arg_count);
			continue;
		}

		if (uses_arg_unpack) {
			zend_error_noreturn(E_COMPILE_ERROR,
				"Cannot use positional argument after argument unpacking");
		}

		arg_count++;
		if (zend_is_call(arg)) {
			zend_compile_var(&arg_node, arg, BP_VAR_R, 0);
			if (arg_node.op_type & (IS_CONST|IS_TMP_VAR)) {
				/* Function call was converted into builtin instruction */
				opcode = ZEND_SEND_VAL;
			} else {
				if (fbc) {
					if (ARG_MUST_BE_SENT_BY_REF(fbc, arg_num)) {
						opcode = ZEND_SEND_VAR_NO_REF;
					} else if (ARG_MAY_BE_SENT_BY_REF(fbc, arg_num)) {
						opcode = ZEND_SEND_VAL;
					} else {
						opcode = ZEND_SEND_VAR;
					}
				} else {
					opcode = ZEND_SEND_VAR_NO_REF_EX;
				}
			}
		} else if (zend_is_variable(arg)) {
			if (fbc) {
				if (ARG_SHOULD_BE_SENT_BY_REF(fbc, arg_num)) {
					zend_compile_var(&arg_node, arg, BP_VAR_W, 1);
					opcode = ZEND_SEND_REF;
				} else {
					zend_compile_var(&arg_node, arg, BP_VAR_R, 0);
					opcode = (arg_node.op_type == IS_TMP_VAR) ? ZEND_SEND_VAL : ZEND_SEND_VAR;
				}
			} else {
				do {
					if (arg->kind == ZEND_AST_VAR) {
						CG(zend_lineno) = zend_ast_get_lineno(ast);
						if (is_this_fetch(arg)) {
							zend_emit_op(&arg_node, ZEND_FETCH_THIS, NULL, NULL);
							opcode = ZEND_SEND_VAR_EX;
							break;
						} else if (zend_try_compile_cv(&arg_node, arg) == SUCCESS) {
							opcode = ZEND_SEND_VAR_EX;
							break;
						}
					}
					opline = zend_emit_op(NULL, ZEND_CHECK_FUNC_ARG, NULL, NULL);
					opline->op2.num = arg_num;
					zend_compile_var(&arg_node, arg, BP_VAR_FUNC_ARG, 1);
					opcode = ZEND_SEND_FUNC_ARG;
				} while (0);
			}
		} else {
			zend_compile_expr(&arg_node, arg);
			if (arg_node.op_type == IS_VAR) {
				/* pass ++$a or something similar */
				if (fbc) {
					if (ARG_MUST_BE_SENT_BY_REF(fbc, arg_num)) {
						opcode = ZEND_SEND_VAR_NO_REF;
					} else if (ARG_MAY_BE_SENT_BY_REF(fbc, arg_num)) {
						opcode = ZEND_SEND_VAL;
					} else {
						opcode = ZEND_SEND_VAR;
					}
				} else {
					opcode = ZEND_SEND_VAR_NO_REF_EX;
				}
			} else if (arg_node.op_type == IS_CV) {
				if (fbc) {
					if (ARG_SHOULD_BE_SENT_BY_REF(fbc, arg_num)) {
						opcode = ZEND_SEND_REF;
					} else {
						opcode = ZEND_SEND_VAR;
					}
				} else {
					opcode = ZEND_SEND_VAR_EX;
				}
			} else {
				if (fbc) {
					opcode = ZEND_SEND_VAL;
					if (ARG_MUST_BE_SENT_BY_REF(fbc, arg_num)) {
						zend_error_noreturn(E_COMPILE_ERROR, "Only variables can be passed by reference");
					}
				} else {
					opcode = ZEND_SEND_VAL_EX;
				}
			}
		}

		opline = zend_emit_op(NULL, opcode, &arg_node, NULL);
		opline->op2.opline_num = arg_num;
		opline->result.var = (uint32_t)(zend_intptr_t)ZEND_CALL_ARG(NULL, arg_num);
	}

	return arg_count;
}