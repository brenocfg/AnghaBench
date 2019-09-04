#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_19__ {scalar_t__ num_args; int /*<<< orphan*/  filename; scalar_t__ T; scalar_t__ last_var; int /*<<< orphan*/  function_name; TYPE_1__* scope; } ;
typedef  TYPE_3__ zend_op_array ;
struct TYPE_20__ {TYPE_2__* opline; TYPE_12__* func; } ;
typedef  TYPE_4__ zend_execute_data ;
typedef  scalar_t__ uint32_t ;
struct TYPE_21__ {int /*<<< orphan*/ * s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ smart_str ;
struct TYPE_18__ {int /*<<< orphan*/  lineno; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_3__ op_array; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ZEND_CALL_ARG (TYPE_4__*,int) ; 
 scalar_t__ ZEND_CALL_NUM_ARGS (TYPE_4__*) ; 
 int /*<<< orphan*/ * ZEND_CALL_VAR_NUM (TYPE_4__*,scalar_t__) ; 
 scalar_t__ ZEND_USER_FUNCTION ; 
 int /*<<< orphan*/  phpdbg_append_individual_arg (TYPE_5__*,scalar_t__,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_append (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_append_unsigned (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_5__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_5__*,char*) ; 

zend_string *phpdbg_compile_stackframe(zend_execute_data *ex) {
	smart_str s = {0};
	zend_op_array *op_array = &ex->func->op_array;
	uint32_t i = 0, first_extra_arg = op_array->num_args, num_args = ZEND_CALL_NUM_ARGS(ex);
	zval *p = ZEND_CALL_ARG(ex, 1);

	if (op_array->scope) {
		smart_str_append(&s, op_array->scope->name);
		smart_str_appends(&s, "::");
	}
	smart_str_append(&s, op_array->function_name);
	smart_str_appendc(&s, '(');
	if (ZEND_CALL_NUM_ARGS(ex) > first_extra_arg) {
		while (i < first_extra_arg) {
			phpdbg_append_individual_arg(&s, i, ex->func, p);
			p++;
			i++;
		}
		p = ZEND_CALL_VAR_NUM(ex, op_array->last_var + op_array->T);
	}
	while (i < num_args) {
		phpdbg_append_individual_arg(&s, i, ex->func, p);
		p++;
		i++;
	}
	smart_str_appendc(&s, ')');

	if (ex->func->type == ZEND_USER_FUNCTION) {
		smart_str_appends(&s, " at ");
		smart_str_append(&s, op_array->filename);
		smart_str_appendc(&s, ':');
		smart_str_append_unsigned(&s, ex->opline->lineno);
	} else {
		smart_str_appends(&s, " [internal function]");
	}

	return s.s;
}