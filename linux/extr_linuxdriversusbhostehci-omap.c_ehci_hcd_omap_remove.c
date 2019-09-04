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
struct usb_hcd {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct omap_hcd {int nports; scalar_t__* phy; } ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 struct usb_hcd* dev_get_drvdata (struct device*) ; 
 TYPE_1__* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  usb_phy_shutdown (scalar_t__) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_hcd_omap_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct omap_hcd *omap = (struct omap_hcd *)hcd_to_ehci(hcd)->priv;
	int i;

	usb_remove_hcd(hcd);

	for (i = 0; i < omap->nports; i++) {
		if (omap->phy[i])
			usb_phy_shutdown(omap->phy[i]);
	}

	usb_put_hcd(hcd);
	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);

	return 0;
}