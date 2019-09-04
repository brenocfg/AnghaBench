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
struct sunxi_priv_data {scalar_t__ regulator; int /*<<< orphan*/  tx_clk; int /*<<< orphan*/  rst_ephy; scalar_t__ internal_phy_powered; scalar_t__ mux_handle; TYPE_1__* variant; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ soc_has_internal_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_mux_uninit (scalar_t__) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun8i_dwmac_unpower_internal_phy (struct sunxi_priv_data*) ; 
 int /*<<< orphan*/  sun8i_dwmac_unset_syscon (struct sunxi_priv_data*) ; 

__attribute__((used)) static void sun8i_dwmac_exit(struct platform_device *pdev, void *priv)
{
	struct sunxi_priv_data *gmac = priv;

	if (gmac->variant->soc_has_internal_phy) {
		/* sun8i_dwmac_exit could be called with mdiomux uninit */
		if (gmac->mux_handle)
			mdio_mux_uninit(gmac->mux_handle);
		if (gmac->internal_phy_powered)
			sun8i_dwmac_unpower_internal_phy(gmac);
	}

	sun8i_dwmac_unset_syscon(gmac);

	reset_control_put(gmac->rst_ephy);

	clk_disable_unprepare(gmac->tx_clk);

	if (gmac->regulator)
		regulator_disable(gmac->regulator);
}