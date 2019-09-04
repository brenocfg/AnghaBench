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
struct tegra_xusb_lane {unsigned int index; TYPE_1__* pad; } ;
struct tegra_xusb_hsic_pad {int /*<<< orphan*/  supply; int /*<<< orphan*/  clk; } ;
struct tegra_xusb_hsic_lane {int strobe_trim; int tx_rtune_p; int rx_strobe_trim; int rx_data_trim; } ;
struct tegra210_xusb_padctl {int dummy; } ;
struct phy {int dummy; } ;
struct TYPE_2__ {struct tegra_xusb_padctl* padctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  XUSB_PADCTL_HSIC_PADX_CTL0 (unsigned int) ; 
 int /*<<< orphan*/  XUSB_PADCTL_HSIC_PADX_CTL1 (unsigned int) ; 
 int /*<<< orphan*/  XUSB_PADCTL_HSIC_PADX_CTL2 (unsigned int) ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA0 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA1 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_STROBE ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA0 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA1 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_STROBE ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA0 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA1 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_STROBE ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPD_STROBE ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA0 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA1 ; 
 int XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE ; 
 int XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_MASK ; 
 int XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_SHIFT ; 
 int XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_MASK ; 
 int XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_SHIFT ; 
 int XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_MASK ; 
 int XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_SHIFT ; 
 int /*<<< orphan*/  XUSB_PADCTL_HSIC_PAD_TRK_CTL ; 
 int XUSB_PADCTL_HSIC_PAD_TRK_CTL_PD_TRK ; 
 int XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_MASK ; 
 int XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_SHIFT ; 
 int XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_VAL ; 
 int XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_MASK ; 
 int XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_SHIFT ; 
 int XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_VAL ; 
 int /*<<< orphan*/  XUSB_PADCTL_HSIC_STRB_TRIM_CONTROL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padctl_writel (struct tegra_xusb_padctl*,int,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_lane* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct tegra_xusb_hsic_lane* to_hsic_lane (struct tegra_xusb_lane*) ; 
 struct tegra_xusb_hsic_pad* to_hsic_pad (TYPE_1__*) ; 
 struct tegra210_xusb_padctl* to_tegra210_xusb_padctl (struct tegra_xusb_padctl*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tegra210_hsic_phy_power_on(struct phy *phy)
{
	struct tegra_xusb_lane *lane = phy_get_drvdata(phy);
	struct tegra_xusb_hsic_lane *hsic = to_hsic_lane(lane);
	struct tegra_xusb_hsic_pad *pad = to_hsic_pad(lane->pad);
	struct tegra_xusb_padctl *padctl = lane->pad->padctl;
	struct tegra210_xusb_padctl *priv;
	unsigned int index = lane->index;
	u32 value;
	int err;

	priv = to_tegra210_xusb_padctl(padctl);

	err = regulator_enable(pad->supply);
	if (err)
		return err;

	padctl_writel(padctl, hsic->strobe_trim,
		      XUSB_PADCTL_HSIC_STRB_TRIM_CONTROL);

	value = padctl_readl(padctl, XUSB_PADCTL_HSIC_PADX_CTL1(index));
	value &= ~(XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_MASK <<
		   XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_SHIFT);
	value |= (hsic->tx_rtune_p <<
		  XUSB_PADCTL_HSIC_PAD_CTL1_TX_RTUNEP_SHIFT);
	padctl_writel(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL1(index));

	value = padctl_readl(padctl, XUSB_PADCTL_HSIC_PADX_CTL2(index));
	value &= ~((XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_MASK <<
		    XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_SHIFT) |
		   (XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_MASK <<
		    XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_SHIFT));
	value |= (hsic->rx_strobe_trim <<
		  XUSB_PADCTL_HSIC_PAD_CTL2_RX_STROBE_TRIM_SHIFT) |
		 (hsic->rx_data_trim <<
		  XUSB_PADCTL_HSIC_PAD_CTL2_RX_DATA_TRIM_SHIFT);
	padctl_writel(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL2(index));

	value = padctl_readl(padctl, XUSB_PADCTL_HSIC_PADX_CTL0(index));
	value &= ~(XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_RPU_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_RPU_STROBE |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_RX_STROBE |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_ZI_STROBE |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA0 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_DATA1 |
		   XUSB_PADCTL_HSIC_PAD_CTL0_PD_TX_STROBE);
	value |= XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA0 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_RPD_DATA1 |
		 XUSB_PADCTL_HSIC_PAD_CTL0_RPD_STROBE;
	padctl_writel(padctl, value, XUSB_PADCTL_HSIC_PADX_CTL0(index));

	err = clk_prepare_enable(pad->clk);
	if (err)
		goto disable;

	value = padctl_readl(padctl, XUSB_PADCTL_HSIC_PAD_TRK_CTL);
	value &= ~((XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_MASK <<
		    XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_SHIFT) |
		   (XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_MASK <<
		    XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_SHIFT));
	value |= (XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_VAL <<
		  XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_START_TIMER_SHIFT) |
		 (XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_VAL <<
		  XUSB_PADCTL_HSIC_PAD_TRK_CTL_TRK_DONE_RESET_TIMER_SHIFT);
	padctl_writel(padctl, value, XUSB_PADCTL_HSIC_PAD_TRK_CTL);

	udelay(1);

	value = padctl_readl(padctl, XUSB_PADCTL_HSIC_PAD_TRK_CTL);
	value &= ~XUSB_PADCTL_HSIC_PAD_TRK_CTL_PD_TRK;
	padctl_writel(padctl, value, XUSB_PADCTL_HSIC_PAD_TRK_CTL);

	udelay(50);

	clk_disable_unprepare(pad->clk);

	return 0;

disable:
	regulator_disable(pad->supply);
	return err;
}