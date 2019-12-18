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
struct isst_pkg_ctdp_level_info {unsigned int fact_support; int pbf_support; int fact_enabled; int pbf_enabled; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  CONFIG_TDP ; 
 int /*<<< orphan*/  CONFIG_TDP_GET_TDP_CONTROL ; 
 int /*<<< orphan*/  debug_printf (char*,int,unsigned int,unsigned int,int,int,int) ; 
 int isst_send_mbox_command (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 

int isst_get_ctdp_control(int cpu, int config_index,
			  struct isst_pkg_ctdp_level_info *ctdp_level)
{
	unsigned int resp;
	int ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_GET_TDP_CONTROL, 0,
				     config_index, &resp);
	if (ret)
		return ret;

	ctdp_level->fact_support = resp & BIT(0);
	ctdp_level->pbf_support = !!(resp & BIT(1));
	ctdp_level->fact_enabled = !!(resp & BIT(16));
	ctdp_level->pbf_enabled = !!(resp & BIT(17));

	debug_printf(
		"cpu:%d CONFIG_TDP_GET_TDP_CONTROL resp:%x fact_support:%d pbf_support: %d fact_enabled:%d pbf_enabled:%d\n",
		cpu, resp, ctdp_level->fact_support, ctdp_level->pbf_support,
		ctdp_level->fact_enabled, ctdp_level->pbf_enabled);

	return 0;
}