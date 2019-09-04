#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_ssa ;
struct TYPE_3__ {int num_args; } ;
typedef  TYPE_1__ zend_call_info ;
typedef  int uint32_t ;

/* Variables and functions */
 int FUNC_MAY_WARN ; 
 int MAY_BE_FALSE ; 
 int MAY_BE_TRUE ; 

__attribute__((used)) static uint32_t zend_is_type_info(const zend_call_info *call_info, const zend_ssa *ssa)
{
	if (call_info->num_args == 1) {
		return MAY_BE_FALSE | MAY_BE_TRUE;
	} else {
		return MAY_BE_FALSE | MAY_BE_TRUE | FUNC_MAY_WARN;
	}
}