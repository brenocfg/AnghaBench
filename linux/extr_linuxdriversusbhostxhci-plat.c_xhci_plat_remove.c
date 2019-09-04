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
struct xhci_hcd {struct usb_hcd* shared_hcd; int /*<<< orphan*/  xhc_state; struct clk* reg_clk; struct clk* clk; } ;
struct usb_hcd {int /*<<< orphan*/  usb_phy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XHCI_STATE_REMOVING ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_phy_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int xhci_plat_remove(struct platform_device *dev)
{
	struct usb_hcd	*hcd = platform_get_drvdata(dev);
	struct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	struct clk *clk = xhci->clk;
	struct clk *reg_clk = xhci->reg_clk;
	struct usb_hcd *shared_hcd = xhci->shared_hcd;

	xhci->xhc_state |= XHCI_STATE_REMOVING;

	usb_remove_hcd(shared_hcd);
	xhci->shared_hcd = NULL;
	usb_phy_shutdown(hcd->usb_phy);

	usb_remove_hcd(hcd);
	usb_put_hcd(shared_hcd);

	clk_disable_unprepare(clk);
	clk_disable_unprepare(reg_clk);
	usb_put_hcd(hcd);

	pm_runtime_set_suspended(&dev->dev);
	pm_runtime_disable(&dev->dev);

	return 0;
}