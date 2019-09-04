#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_uchar ;
struct TYPE_6__ {size_t children; TYPE_2__** child; } ;
typedef  TYPE_1__ zend_ast_list ;
struct TYPE_7__ {scalar_t__ kind; struct TYPE_7__** child; } ;
typedef  TYPE_2__ zend_ast ;
typedef  size_t uint32_t ;

/* Variables and functions */
 scalar_t__ IS_LONG ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ IS_UNDEF ; 
 scalar_t__ ZEND_AST_ZVAL ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ is_numeric_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_ast_get_zval (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_eval_const_expr (TYPE_2__**) ; 

__attribute__((used)) static zend_uchar determine_switch_jumptable_type(zend_ast_list *cases) {
	uint32_t i;
	zend_uchar common_type = IS_UNDEF;
	for (i = 0; i < cases->children; i++) {
		zend_ast *case_ast = cases->child[i];
		zend_ast **cond_ast = &case_ast->child[0];
		zval *cond_zv;
		if (!case_ast->child[0]) {
			/* Skip default clause */
			continue;
		}

		zend_eval_const_expr(cond_ast);
		if ((*cond_ast)->kind != ZEND_AST_ZVAL) {
			/* Non-constant case */
			return IS_UNDEF;
		}

		cond_zv = zend_ast_get_zval(case_ast->child[0]);
		if (Z_TYPE_P(cond_zv) != IS_LONG && Z_TYPE_P(cond_zv) != IS_STRING) {
			/* We only optimize switched on integers and strings */
			return IS_UNDEF;
		}

		if (common_type == IS_UNDEF) {
			common_type = Z_TYPE_P(cond_zv);
		} else if (common_type != Z_TYPE_P(cond_zv)) {
			/* Non-uniform case types */
			return IS_UNDEF;
		}

		if (Z_TYPE_P(cond_zv) == IS_STRING
				&& is_numeric_string(Z_STRVAL_P(cond_zv), Z_STRLEN_P(cond_zv), NULL, NULL, 0)) {
			/* Numeric strings cannot be compared with a simple hash lookup */
			return IS_UNDEF;
		}
	}

	return common_type;
}