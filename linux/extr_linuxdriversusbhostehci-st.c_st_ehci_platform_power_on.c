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
struct usb_hcd {int dummy; } ;
struct st_ehci_platform_priv {int /*<<< orphan*/  pwr; int /*<<< orphan*/  rst; scalar_t__* clks; int /*<<< orphan*/  phy; scalar_t__ clk48; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int USB_MAX_CLKS ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int clk_set_rate (scalar_t__,int) ; 
 struct st_ehci_platform_priv* hcd_to_ehci_priv (struct usb_hcd*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_ehci_platform_power_on(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct st_ehci_platform_priv *priv = hcd_to_ehci_priv(hcd);
	int clk, ret;

	ret = reset_control_deassert(priv->pwr);
	if (ret)
		return ret;

	ret = reset_control_deassert(priv->rst);
	if (ret)
		goto err_assert_power;

	/* some SoCs don't have a dedicated 48Mhz clock, but those that do
	   need the rate to be explicitly set */
	if (priv->clk48) {
		ret = clk_set_rate(priv->clk48, 48000000);
		if (ret)
			goto err_assert_reset;
	}

	for (clk = 0; clk < USB_MAX_CLKS && priv->clks[clk]; clk++) {
		ret = clk_prepare_enable(priv->clks[clk]);
		if (ret)
			goto err_disable_clks;
	}

	ret = phy_init(priv->phy);
	if (ret)
		goto err_disable_clks;

	ret = phy_power_on(priv->phy);
	if (ret)
		goto err_exit_phy;

	return 0;

err_exit_phy:
	phy_exit(priv->phy);
err_disable_clks:
	while (--clk >= 0)
		clk_disable_unprepare(priv->clks[clk]);
err_assert_reset:
	reset_control_assert(priv->rst);
err_assert_power:
	reset_control_assert(priv->pwr);

	return ret;
}