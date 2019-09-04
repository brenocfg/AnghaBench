#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ AUDIT_FAIL_PANIC ; 
 scalar_t__ AUDIT_FAIL_PRINTK ; 
 scalar_t__ AUDIT_FAIL_SILENT ; 
 int EINVAL ; 
 int audit_do_config_change (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  audit_failure ; 

__attribute__((used)) static int audit_set_failure(u32 state)
{
	if (state != AUDIT_FAIL_SILENT
	    && state != AUDIT_FAIL_PRINTK
	    && state != AUDIT_FAIL_PANIC)
		return -EINVAL;

	return audit_do_config_change("audit_failure", &audit_failure, state);
}