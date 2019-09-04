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
struct platform_device {int dummy; } ;
struct ehci_platform_priv {scalar_t__* clks; } ;

/* Variables and functions */
 int EHCI_MAX_CLKS ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 struct ehci_platform_priv* hcd_to_ehci_priv (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ehci_platform_power_on(struct platform_device *dev)
{
	struct usb_hcd *hcd = platform_get_drvdata(dev);
	struct ehci_platform_priv *priv = hcd_to_ehci_priv(hcd);
	int clk, ret;

	for (clk = 0; clk < EHCI_MAX_CLKS && priv->clks[clk]; clk++) {
		ret = clk_prepare_enable(priv->clks[clk]);
		if (ret)
			goto err_disable_clks;
	}

	return 0;

err_disable_clks:
	while (--clk >= 0)
		clk_disable_unprepare(priv->clks[clk]);

	return ret;
}