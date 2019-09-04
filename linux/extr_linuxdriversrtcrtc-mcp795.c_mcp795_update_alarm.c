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
struct device {int dummy; } ;

/* Variables and functions */
 int MCP795_ALM0IF_BIT ; 
 int MCP795_ALM0_BIT ; 
 int MCP795_ALM1_BIT ; 
 int /*<<< orphan*/  MCP795_REG_ALM0_DAY ; 
 int /*<<< orphan*/  MCP795_REG_CONTROL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int mcp795_rtcc_set_bits (struct device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mcp795_update_alarm(struct device *dev, bool enable)
{
	int ret;

	dev_dbg(dev, "%s alarm\n", enable ? "Enable" : "Disable");

	if (enable) {
		/* clear ALM0IF (Alarm 0 Interrupt Flag) bit */
		ret = mcp795_rtcc_set_bits(dev, MCP795_REG_ALM0_DAY,
					MCP795_ALM0IF_BIT, 0);
		if (ret)
			return ret;
		/* enable alarm 0 */
		ret = mcp795_rtcc_set_bits(dev, MCP795_REG_CONTROL,
					MCP795_ALM0_BIT, MCP795_ALM0_BIT);
	} else {
		/* disable alarm 0 and alarm 1 */
		ret = mcp795_rtcc_set_bits(dev, MCP795_REG_CONTROL,
					MCP795_ALM0_BIT | MCP795_ALM1_BIT, 0);
	}
	return ret;
}