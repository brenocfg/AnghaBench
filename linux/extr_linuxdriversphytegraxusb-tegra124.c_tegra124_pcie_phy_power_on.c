#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_xusb_padctl {int dummy; } ;
struct tegra_xusb_lane {int /*<<< orphan*/  index; TYPE_1__* pad; } ;
struct phy {int dummy; } ;
struct TYPE_2__ {struct tegra_xusb_padctl* padctl; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_P0_CTL1 ; 
 int XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL0_LOCKDET ; 
 int XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL_RST ; 
 int XUSB_PADCTL_IOPHY_PLL_P0_CTL1_REFCLK_SEL_MASK ; 
 int /*<<< orphan*/  XUSB_PADCTL_IOPHY_PLL_P0_CTL2 ; 
 int XUSB_PADCTL_IOPHY_PLL_P0_CTL2_REFCLKBUF_EN ; 
 int XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_EN ; 
 int XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_SEL ; 
 int /*<<< orphan*/  XUSB_PADCTL_USB3_PAD_MUX ; 
 int XUSB_PADCTL_USB3_PAD_MUX_PCIE_IDDQ_DISABLE (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* phy_get_drvdata (struct phy*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra124_pcie_phy_power_on(struct phy *phy)
{
	struct tegra_xusb_lane *lane = phy_get_drvdata(phy);
	struct tegra_xusb_padctl *padctl = lane->pad->padctl;
	unsigned long timeout;
	int err = -ETIMEDOUT;
	u32 value;

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
	value &= ~XUSB_PADCTL_IOPHY_PLL_P0_CTL1_REFCLK_SEL_MASK;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL2);
	value |= XUSB_PADCTL_IOPHY_PLL_P0_CTL2_REFCLKBUF_EN |
		 XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_EN |
		 XUSB_PADCTL_IOPHY_PLL_P0_CTL2_TXCLKREF_SEL;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL2);

	value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
	value |= XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL_RST;
	padctl_writel(padctl, value, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);

	timeout = jiffies + msecs_to_jiffies(50);

	while (time_before(jiffies, timeout)) {
		value = padctl_readl(padctl, XUSB_PADCTL_IOPHY_PLL_P0_CTL1);
		if (value & XUSB_PADCTL_IOPHY_PLL_P0_CTL1_PLL0_LOCKDET) {
			err = 0;
			break;
		}

		usleep_range(100, 200);
	}

	value = padctl_readl(padctl, XUSB_PADCTL_USB3_PAD_MUX);
	value |= XUSB_PADCTL_USB3_PAD_MUX_PCIE_IDDQ_DISABLE(lane->index);
	padctl_writel(padctl, value, XUSB_PADCTL_USB3_PAD_MUX);

	return err;
}