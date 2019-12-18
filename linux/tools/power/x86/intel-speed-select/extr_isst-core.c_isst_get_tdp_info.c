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
struct isst_pkg_ctdp_level_info {unsigned int pkg_tdp; unsigned int tdp_ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TDP ; 
 int /*<<< orphan*/  CONFIG_TDP_GET_TDP_INFO ; 
 unsigned int GENMASK (int,int) ; 
 int /*<<< orphan*/  debug_printf (char*,int,int,unsigned int,unsigned int,unsigned int) ; 
 int isst_send_mbox_command (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 

int isst_get_tdp_info(int cpu, int config_index,
		      struct isst_pkg_ctdp_level_info *ctdp_level)
{
	unsigned int resp;
	int ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP, CONFIG_TDP_GET_TDP_INFO,
				     0, config_index, &resp);
	if (ret)
		return ret;

	ctdp_level->pkg_tdp = resp & GENMASK(14, 0);
	ctdp_level->tdp_ratio = (resp & GENMASK(23, 16)) >> 16;

	debug_printf(
		"cpu:%d ctdp:%d CONFIG_TDP_GET_TDP_INFO resp:%x tdp_ratio:%d pkg_tdp:%d\n",
		cpu, config_index, resp, ctdp_level->tdp_ratio,
		ctdp_level->pkg_tdp);
	return 0;
}