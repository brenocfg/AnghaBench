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
struct exynos_ohci_hcd {int /*<<< orphan*/ * phy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PHY_NUMBER ; 
 struct usb_hcd* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct exynos_ohci_hcd* to_exynos_ohci (struct usb_hcd*) ; 

__attribute__((used)) static void exynos_ohci_phy_disable(struct device *dev)
{
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);
	int i;

	for (i = 0; i < PHY_NUMBER; i++)
		if (!IS_ERR(exynos_ohci->phy[i]))
			phy_power_off(exynos_ohci->phy[i]);
}