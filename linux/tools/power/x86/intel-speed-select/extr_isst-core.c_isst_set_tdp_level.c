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
 int /*<<< orphan*/  CONFIG_TDP ; 
 int /*<<< orphan*/  CONFIG_TDP_SET_LEVEL ; 
 int isst_send_mbox_command (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 
 int isst_set_tdp_level_msr (int,int) ; 

int isst_set_tdp_level(int cpu, int tdp_level)
{
	unsigned int resp;
	int ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP, CONFIG_TDP_SET_LEVEL, 0,
				     tdp_level, &resp);
	if (ret)
		return isst_set_tdp_level_msr(cpu, tdp_level);

	return 0;
}