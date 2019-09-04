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
struct sdw_cdns {int /*<<< orphan*/  dev; } ;
struct sdw_bus_params {int curr_dr_freq; int max_dr_freq; scalar_t__ next_bank; } ;
struct sdw_bus {int dummy; } ;

/* Variables and functions */
 int CDNS_MCP_CLK_CTRL0 ; 
 int CDNS_MCP_CLK_CTRL1 ; 
 int EINVAL ; 
 struct sdw_cdns* bus_to_cdns (struct sdw_bus*) ; 
 int cdns_readl (struct sdw_cdns*,int) ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

int cdns_bus_conf(struct sdw_bus *bus, struct sdw_bus_params *params)
{
	struct sdw_cdns *cdns = bus_to_cdns(bus);
	int mcp_clkctrl_off, mcp_clkctrl;
	int divider;

	if (!params->curr_dr_freq) {
		dev_err(cdns->dev, "NULL curr_dr_freq");
		return -EINVAL;
	}

	divider	= (params->max_dr_freq / params->curr_dr_freq) - 1;

	if (params->next_bank)
		mcp_clkctrl_off = CDNS_MCP_CLK_CTRL1;
	else
		mcp_clkctrl_off = CDNS_MCP_CLK_CTRL0;

	mcp_clkctrl = cdns_readl(cdns, mcp_clkctrl_off);
	mcp_clkctrl |= divider;
	cdns_writel(cdns, mcp_clkctrl_off, mcp_clkctrl);

	return 0;
}