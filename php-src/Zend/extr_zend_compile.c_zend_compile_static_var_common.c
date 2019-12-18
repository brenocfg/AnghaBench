#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_9__ {int /*<<< orphan*/  var; } ;
struct TYPE_10__ {int extended_value; TYPE_2__ op1; int /*<<< orphan*/  op1_type; } ;
typedef  TYPE_3__ zend_op ;
typedef  int uint32_t ;
struct TYPE_12__ {TYPE_4__* static_variables; TYPE_1__* scope; } ;
struct TYPE_11__ {scalar_t__ arData; } ;
struct TYPE_8__ {int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 TYPE_7__* CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_COMPILE_ERROR ; 
 int /*<<< orphan*/  IS_CV ; 
 int /*<<< orphan*/  ZEND_BIND_STATIC ; 
 int /*<<< orphan*/  ZEND_HAS_STATIC_IN_METHODS ; 
 int /*<<< orphan*/  active_op_array ; 
 int /*<<< orphan*/  lookup_cv (int /*<<< orphan*/ *) ; 
 TYPE_3__* zend_emit_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_error_noreturn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * zend_hash_update (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* zend_new_array (int) ; 
 scalar_t__ zend_string_equals_literal (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void zend_compile_static_var_common(zend_string *var_name, zval *value, uint32_t mode) /* {{{ */
{
	zend_op *opline;
	if (!CG(active_op_array)->static_variables) {
		if (CG(active_op_array)->scope) {
			CG(active_op_array)->scope->ce_flags |= ZEND_HAS_STATIC_IN_METHODS;
		}
		CG(active_op_array)->static_variables = zend_new_array(8);
	}

	value = zend_hash_update(CG(active_op_array)->static_variables, var_name, value);

	if (zend_string_equals_literal(var_name, "this")) {
		zend_error_noreturn(E_COMPILE_ERROR, "Cannot use $this as static variable");
	}

	opline = zend_emit_op(NULL, ZEND_BIND_STATIC, NULL, NULL);
	opline->op1_type = IS_CV;
	opline->op1.var = lookup_cv(var_name);
	opline->extended_value = (uint32_t)((char*)value - (char*)CG(active_op_array)->static_variables->arData) | mode;
}