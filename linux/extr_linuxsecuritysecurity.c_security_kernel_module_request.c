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

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int integrity_kernel_module_request (char*) ; 
 int /*<<< orphan*/  kernel_module_request ; 

int security_kernel_module_request(char *kmod_name)
{
	int ret;

	ret = call_int_hook(kernel_module_request, 0, kmod_name);
	if (ret)
		return ret;
	return integrity_kernel_module_request(kmod_name);
}