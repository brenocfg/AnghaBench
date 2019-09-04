#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {TYPE_1__* usb_phy; } ;
struct tegra_ehci_hcd {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;
struct platform_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 TYPE_2__* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  otg_set_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usb_phy_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int tegra_ehci_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct tegra_ehci_hcd *tegra =
		(struct tegra_ehci_hcd *)hcd_to_ehci(hcd)->priv;

	otg_set_host(hcd->usb_phy->otg, NULL);

	usb_phy_shutdown(hcd->usb_phy);
	usb_remove_hcd(hcd);

	reset_control_assert(tegra->rst);
	udelay(1);

	clk_disable_unprepare(tegra->clk);

	usb_put_hcd(hcd);

	return 0;
}