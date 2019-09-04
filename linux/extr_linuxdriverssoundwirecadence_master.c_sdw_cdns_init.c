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
typedef  int u32 ;
struct sdw_cdns {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CDNS_DEFAULT_CLK_DIVIDER ; 
 int CDNS_DEFAULT_FRAME_SHAPE ; 
 int CDNS_DEFAULT_SSP_INTERVAL ; 
 int /*<<< orphan*/  CDNS_MCP_CLK_CTRL0 ; 
 int /*<<< orphan*/  CDNS_MCP_CONFIG ; 
 int CDNS_MCP_CONFIG_BUS_REL ; 
 int CDNS_MCP_CONFIG_CMD ; 
 int CDNS_MCP_CONFIG_MCMD_RETRY ; 
 int /*<<< orphan*/  CDNS_MCP_CONFIG_MPREQ_DELAY ; 
 int CDNS_MCP_CONFIG_OP ; 
 int CDNS_MCP_CONFIG_OP_NORMAL ; 
 int CDNS_MCP_CONFIG_SNIFFER ; 
 int /*<<< orphan*/  CDNS_MCP_CONTROL ; 
 int /*<<< orphan*/  CDNS_MCP_CONTROL_CLK_STOP_CLR ; 
 int /*<<< orphan*/  CDNS_MCP_CONTROL_CMD_ACCEPT ; 
 int /*<<< orphan*/  CDNS_MCP_FRAME_SHAPE_INIT ; 
 int /*<<< orphan*/  CDNS_MCP_SSP_CTRL0 ; 
 int /*<<< orphan*/  CDNS_MCP_SSP_CTRL1 ; 
 int SDW_REG_SHIFT (int /*<<< orphan*/ ) ; 
 int cdns_clear_bit (struct sdw_cdns*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cdns_readl (struct sdw_cdns*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_updatel (struct sdw_cdns*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

int sdw_cdns_init(struct sdw_cdns *cdns)
{
	u32 val;
	int ret;

	/* Exit clock stop */
	ret = cdns_clear_bit(cdns, CDNS_MCP_CONTROL,
			CDNS_MCP_CONTROL_CLK_STOP_CLR);
	if (ret < 0) {
		dev_err(cdns->dev, "Couldn't exit from clock stop\n");
		return ret;
	}

	/* Set clock divider */
	val = cdns_readl(cdns, CDNS_MCP_CLK_CTRL0);
	val |= CDNS_DEFAULT_CLK_DIVIDER;
	cdns_writel(cdns, CDNS_MCP_CLK_CTRL0, val);

	/* Set the default frame shape */
	cdns_writel(cdns, CDNS_MCP_FRAME_SHAPE_INIT, CDNS_DEFAULT_FRAME_SHAPE);

	/* Set SSP interval to default value */
	cdns_writel(cdns, CDNS_MCP_SSP_CTRL0, CDNS_DEFAULT_SSP_INTERVAL);
	cdns_writel(cdns, CDNS_MCP_SSP_CTRL1, CDNS_DEFAULT_SSP_INTERVAL);

	/* Set cmd accept mode */
	cdns_updatel(cdns, CDNS_MCP_CONTROL, CDNS_MCP_CONTROL_CMD_ACCEPT,
					CDNS_MCP_CONTROL_CMD_ACCEPT);

	/* Configure mcp config */
	val = cdns_readl(cdns, CDNS_MCP_CONFIG);

	/* Set Max cmd retry to 15 */
	val |= CDNS_MCP_CONFIG_MCMD_RETRY;

	/* Set frame delay between PREQ and ping frame to 15 frames */
	val |= 0xF << SDW_REG_SHIFT(CDNS_MCP_CONFIG_MPREQ_DELAY);

	/* Disable auto bus release */
	val &= ~CDNS_MCP_CONFIG_BUS_REL;

	/* Disable sniffer mode */
	val &= ~CDNS_MCP_CONFIG_SNIFFER;

	/* Set cmd mode for Tx and Rx cmds */
	val &= ~CDNS_MCP_CONFIG_CMD;

	/* Set operation to normal */
	val &= ~CDNS_MCP_CONFIG_OP;
	val |= CDNS_MCP_CONFIG_OP_NORMAL;

	cdns_writel(cdns, CDNS_MCP_CONFIG, val);

	return 0;
}