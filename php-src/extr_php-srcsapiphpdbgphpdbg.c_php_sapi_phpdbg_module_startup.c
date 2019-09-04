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
typedef  int /*<<< orphan*/  sapi_module_struct ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int SUCCESS ; 
 scalar_t__ php_module_startup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int phpdbg_booted ; 
 int /*<<< orphan*/  sapi_phpdbg_module_entry ; 

__attribute__((used)) static inline int php_sapi_phpdbg_module_startup(sapi_module_struct *module) /* {{{ */
{
	if (php_module_startup(module, &sapi_phpdbg_module_entry, 1) == FAILURE) {
		return FAILURE;
	}

	phpdbg_booted = 1;

	return SUCCESS;
}