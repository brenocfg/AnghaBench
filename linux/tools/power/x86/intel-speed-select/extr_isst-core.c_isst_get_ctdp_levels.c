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
struct isst_pkg_ctdp {unsigned int version; unsigned int levels; unsigned int current_level; int locked; int enabled; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  CONFIG_TDP ; 
 int /*<<< orphan*/  CONFIG_TDP_GET_LEVELS_INFO ; 
 int /*<<< orphan*/  debug_printf (char*,int,unsigned int) ; 
 int isst_send_mbox_command (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

int isst_get_ctdp_levels(int cpu, struct isst_pkg_ctdp *pkg_dev)
{
	unsigned int resp;
	int ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_GET_LEVELS_INFO, 0, 0, &resp);
	if (ret)
		return ret;

	debug_printf("cpu:%d CONFIG_TDP_GET_LEVELS_INFO resp:%x\n", cpu, resp);

	pkg_dev->version = resp & 0xff;
	pkg_dev->levels = (resp >> 8) & 0xff;
	pkg_dev->current_level = (resp >> 16) & 0xff;
	pkg_dev->locked = !!(resp & BIT(24));
	pkg_dev->enabled = !!(resp & BIT(31));

	return 0;
}