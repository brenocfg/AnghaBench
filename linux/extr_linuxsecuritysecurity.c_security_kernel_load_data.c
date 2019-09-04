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
typedef  enum kernel_load_data_id { ____Placeholder_kernel_load_data_id } kernel_load_data_id ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ima_load_data (int) ; 
 int /*<<< orphan*/  kernel_load_data ; 

int security_kernel_load_data(enum kernel_load_data_id id)
{
	int ret;

	ret = call_int_hook(kernel_load_data, 0, id);
	if (ret)
		return ret;
	return ima_load_data(id);
}