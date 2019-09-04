#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fn_flags; int num_args; TYPE_2__* arg_info; } ;
typedef  TYPE_1__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ zend_arg_info ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_HAS_TYPE_HINTS ; 
 int ZEND_ACC_VARIADIC ; 
 int /*<<< orphan*/  ZEND_TYPE_IS_CLASS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_bool class_name_type_hint(const zend_op_array *op_array, uint32_t arg_num)
{
	zend_arg_info *arg_info;

	if (arg_num > 0) {
		if (op_array->fn_flags & ZEND_ACC_HAS_TYPE_HINTS) {
			if (EXPECTED(arg_num <= op_array->num_args)) {
				arg_info = &op_array->arg_info[arg_num-1];
			} else if (UNEXPECTED(op_array->fn_flags & ZEND_ACC_VARIADIC)) {
				arg_info = &op_array->arg_info[op_array->num_args];
			} else {
				return 0;
			}
			return ZEND_TYPE_IS_CLASS(arg_info->type);
		}
	} else {
		arg_info = op_array->arg_info - 1;
		return ZEND_TYPE_IS_CLASS(arg_info->type);
	}
	return 0;
}