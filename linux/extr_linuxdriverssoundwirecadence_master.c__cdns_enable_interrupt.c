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
struct sdw_cdns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_MCP_INTMASK ; 
 int CDNS_MCP_INT_CTRL_CLASH ; 
 int CDNS_MCP_INT_DATA_CLASH ; 
 int CDNS_MCP_INT_DPINT ; 
 int CDNS_MCP_INT_IRQ ; 
 int CDNS_MCP_INT_RX_WL ; 
 int CDNS_MCP_INT_SLAVE_ALERT ; 
 int CDNS_MCP_INT_SLAVE_ATTACH ; 
 int CDNS_MCP_INT_SLAVE_NATTACH ; 
 int CDNS_MCP_INT_SLAVE_RSVD ; 
 int /*<<< orphan*/  CDNS_MCP_SLAVE_INTMASK0 ; 
 int CDNS_MCP_SLAVE_INTMASK0_MASK ; 
 int /*<<< orphan*/  CDNS_MCP_SLAVE_INTMASK1 ; 
 int CDNS_MCP_SLAVE_INTMASK1_MASK ; 
 int /*<<< orphan*/  cdns_writel (struct sdw_cdns*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _cdns_enable_interrupt(struct sdw_cdns *cdns)
{
	u32 mask;

	cdns_writel(cdns, CDNS_MCP_SLAVE_INTMASK0,
				CDNS_MCP_SLAVE_INTMASK0_MASK);
	cdns_writel(cdns, CDNS_MCP_SLAVE_INTMASK1,
				CDNS_MCP_SLAVE_INTMASK1_MASK);

	mask = CDNS_MCP_INT_SLAVE_RSVD | CDNS_MCP_INT_SLAVE_ALERT |
		CDNS_MCP_INT_SLAVE_ATTACH | CDNS_MCP_INT_SLAVE_NATTACH |
		CDNS_MCP_INT_CTRL_CLASH | CDNS_MCP_INT_DATA_CLASH |
		CDNS_MCP_INT_RX_WL | CDNS_MCP_INT_IRQ | CDNS_MCP_INT_DPINT;

	cdns_writel(cdns, CDNS_MCP_INTMASK, mask);

	return 0;
}