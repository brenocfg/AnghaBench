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
struct TYPE_4__ {int /*<<< orphan*/  opline; } ;

/* Variables and functions */
 int MAY_BE_ANY ; 
 int MAY_BE_ARRAY ; 
 int MAY_BE_ARRAY_KEY_LONG ; 
 int MAY_BE_ARRAY_OF_DOUBLE ; 
 int MAY_BE_ARRAY_OF_LONG ; 
 int MAY_BE_ARRAY_OF_STRING ; 
 int MAY_BE_DOUBLE ; 
 int MAY_BE_FALSE ; 
 int MAY_BE_RC1 ; 
 int MAY_BE_STRING ; 
 int _ssa_op1_info (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t zend_range_info(const zend_call_info *call_info, const zend_ssa *ssa)
{
	if (call_info->num_args == 2 || call_info->num_args == 3) {

		uint32_t t1 = _ssa_op1_info(call_info->caller_op_array, ssa, call_info->arg_info[0].opline);
		uint32_t t2 = _ssa_op1_info(call_info->caller_op_array, ssa, call_info->arg_info[1].opline);
		uint32_t t3 = 0;
		uint32_t tmp = MAY_BE_RC1 | MAY_BE_FALSE | MAY_BE_ARRAY | MAY_BE_ARRAY_KEY_LONG;

		if (call_info->num_args == 3) {
			t3 = _ssa_op1_info(call_info->caller_op_array, ssa, call_info->arg_info[2].opline);
		}
		if ((t1 & MAY_BE_STRING) && (t2 & MAY_BE_STRING)) {
			tmp |= MAY_BE_ARRAY_OF_LONG | MAY_BE_ARRAY_OF_DOUBLE | MAY_BE_ARRAY_OF_STRING;
		}
		if ((t1 & (MAY_BE_DOUBLE|MAY_BE_STRING))
				|| (t2 & (MAY_BE_DOUBLE|MAY_BE_STRING))
				|| (t3 & (MAY_BE_DOUBLE|MAY_BE_STRING))) {
			tmp |= MAY_BE_ARRAY_OF_DOUBLE;
		}
		if ((t1 & (MAY_BE_ANY-(MAY_BE_STRING|MAY_BE_DOUBLE))) && (t2 & (MAY_BE_ANY-(MAY_BE_STRING|MAY_BE_DOUBLE)))) {
			if ((t3 & MAY_BE_ANY) != MAY_BE_DOUBLE) {
				tmp |= MAY_BE_ARRAY_OF_LONG;
			}
		}
		return tmp;
	} else {
		/* may warning, and return FALSE */
		return MAY_BE_RC1 | MAY_BE_FALSE | MAY_BE_ARRAY | MAY_BE_ARRAY_KEY_LONG | MAY_BE_ARRAY_OF_LONG | MAY_BE_ARRAY_OF_DOUBLE | MAY_BE_ARRAY_OF_STRING;
	}
}