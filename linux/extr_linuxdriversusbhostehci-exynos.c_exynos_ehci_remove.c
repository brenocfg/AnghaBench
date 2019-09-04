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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct exynos_ehci_hcd {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_ehci_phy_disable (int /*<<< orphan*/ *) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 struct exynos_ehci_hcd* to_exynos_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int exynos_ehci_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);

	usb_remove_hcd(hcd);

	exynos_ehci_phy_disable(&pdev->dev);

	clk_disable_unprepare(exynos_ehci->clk);

	usb_put_hcd(hcd);

	return 0;
}