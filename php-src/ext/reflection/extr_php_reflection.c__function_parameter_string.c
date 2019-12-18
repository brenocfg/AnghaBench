#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ required_num_args; scalar_t__ num_args; int fn_flags; struct _zend_arg_info* arg_info; } ;
struct TYPE_6__ {TYPE_1__ common; } ;
typedef  TYPE_2__ zend_function ;
typedef  scalar_t__ uint32_t ;
struct _zend_arg_info {int dummy; } ;
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int ZEND_ACC_VARIADIC ; 
 int /*<<< orphan*/  _parameter_string (int /*<<< orphan*/ *,TYPE_2__*,struct _zend_arg_info*,scalar_t__,int,char*) ; 
 int /*<<< orphan*/  smart_str_append_printf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  smart_str_appendc (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void _function_parameter_string(smart_str *str, zend_function *fptr, char* indent)
{
	struct _zend_arg_info *arg_info = fptr->common.arg_info;
	uint32_t i, num_args, num_required = fptr->common.required_num_args;

	if (!arg_info) {
		return;
	}

	num_args = fptr->common.num_args;
	if (fptr->common.fn_flags & ZEND_ACC_VARIADIC) {
		num_args++;
	}
	smart_str_appendc(str, '\n');
	smart_str_append_printf(str, "%s- Parameters [%d] {\n", indent, num_args);
	for (i = 0; i < num_args; i++) {
		smart_str_append_printf(str, "%s  ", indent);
		_parameter_string(str, fptr, arg_info, i, i < num_required, indent);
		smart_str_appendc(str, '\n');
		arg_info++;
	}
	smart_str_append_printf(str, "%s}\n", indent);
}