#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int is_instanceof; scalar_t__ has_range; TYPE_2__ range; scalar_t__ ce; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_ssa_var_info ;
typedef  TYPE_2__ zend_ssa_range ;
typedef  int /*<<< orphan*/  zend_script ;
struct TYPE_8__ {int fn_flags; int /*<<< orphan*/ * arg_info; } ;
typedef  TYPE_3__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_arg_info ;

/* Variables and functions */
 int /*<<< orphan*/  MAY_BE_REF ; 
 int ZEND_ACC_HAS_RETURN_TYPE ; 
 int ZEND_ACC_RETURN_REFERENCE ; 
 int /*<<< orphan*/  zend_fetch_arg_info_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__*) ; 

void zend_init_func_return_info(const zend_op_array   *op_array,
                                const zend_script     *script,
                                zend_ssa_var_info     *ret)
{
	if (op_array->fn_flags & ZEND_ACC_HAS_RETURN_TYPE) {
		zend_arg_info *ret_info = op_array->arg_info - 1;
		zend_ssa_range tmp_range = {0, 0, 0, 0};

		ret->type = zend_fetch_arg_info_type(script, ret_info, &ret->ce);
		if (op_array->fn_flags & ZEND_ACC_RETURN_REFERENCE) {
			ret->type |= MAY_BE_REF;
		}
		ret->is_instanceof = (ret->ce) ? 1 : 0;
		ret->range = tmp_range;
		ret->has_range = 0;
	}
}