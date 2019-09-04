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
typedef  int /*<<< orphan*/  zend_ssa ;
struct TYPE_5__ {int num_args; TYPE_1__* arg_info; int /*<<< orphan*/  caller_op_array; } ;
typedef  TYPE_2__ zend_call_info ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ opline; } ;

/* Variables and functions */
 int FUNC_MAY_WARN ; 
 int MAY_BE_ARRAY ; 
 int MAY_BE_DOUBLE ; 
 int MAY_BE_FALSE ; 
 int MAY_BE_LONG ; 
 int MAY_BE_NULL ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_RESOURCE ; 
 int MAY_BE_STRING ; 
 int MAY_BE_TRUE ; 
 int _ssa_op1_info (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static uint32_t zend_strlen_info(const zend_call_info *call_info, const zend_ssa *ssa)
{
	if (call_info->num_args == 1) {
		uint32_t tmp = 0;
		if (call_info->arg_info[0].opline) {
			uint32_t arg_info = _ssa_op1_info(call_info->caller_op_array, ssa, call_info->arg_info[0].opline);

			if (arg_info & (MAY_BE_NULL|MAY_BE_FALSE|MAY_BE_TRUE|MAY_BE_LONG|MAY_BE_DOUBLE|MAY_BE_STRING|MAY_BE_OBJECT)) {
				tmp |= MAY_BE_LONG;
			}
			if (arg_info & (MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
				/* warning, and returns NULL */
				tmp |= FUNC_MAY_WARN | MAY_BE_NULL;
			}
		} else {
			tmp |= MAY_BE_LONG | FUNC_MAY_WARN | MAY_BE_NULL;
		}
		return tmp;
	} else if (call_info->num_args != -1) {
		/* warning, and returns NULL */
		return FUNC_MAY_WARN | MAY_BE_NULL;
	} else {
		return MAY_BE_LONG | FUNC_MAY_WARN | MAY_BE_NULL;
	}
}