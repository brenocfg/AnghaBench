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
 unsigned long long BIT (int) ; 
 int isst_send_msr_command (int,int,int /*<<< orphan*/ ,unsigned long long*) ; 

int isst_get_config_tdp_lock_status(int cpu)
{
	unsigned long long tdp_control = 0;
	int ret;

	ret = isst_send_msr_command(cpu, 0x64b, 0, &tdp_control);
	if (ret)
		return ret;

	ret = !!(tdp_control & BIT(31));

	return ret;
}