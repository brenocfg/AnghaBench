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
struct sunxi_priv_data {int internal_phy_powered; int /*<<< orphan*/  ephy_clk; int /*<<< orphan*/  rst_ephy; } ;
struct stmmac_priv {int /*<<< orphan*/  device; TYPE_1__* plat; } ;
struct TYPE_2__ {struct sunxi_priv_data* bsp_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun8i_dwmac_power_internal_phy(struct stmmac_priv *priv)
{
	struct sunxi_priv_data *gmac = priv->plat->bsp_priv;
	int ret;

	if (gmac->internal_phy_powered) {
		dev_warn(priv->device, "Internal PHY already powered\n");
		return 0;
	}

	dev_info(priv->device, "Powering internal PHY\n");
	ret = clk_prepare_enable(gmac->ephy_clk);
	if (ret) {
		dev_err(priv->device, "Cannot enable internal PHY\n");
		return ret;
	}

	/* Make sure the EPHY is properly reseted, as U-Boot may leave
	 * it at deasserted state, and thus it may fail to reset EMAC.
	 */
	reset_control_assert(gmac->rst_ephy);

	ret = reset_control_deassert(gmac->rst_ephy);
	if (ret) {
		dev_err(priv->device, "Cannot deassert internal phy\n");
		clk_disable_unprepare(gmac->ephy_clk);
		return ret;
	}

	gmac->internal_phy_powered = true;

	return 0;
}