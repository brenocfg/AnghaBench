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
struct xhci_hcd {int /*<<< orphan*/ * shared_hcd; } ;
struct TYPE_2__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  virt; int /*<<< orphan*/  size; } ;
struct tegra_xusb {int /*<<< orphan*/  padctl; TYPE_1__ fw; int /*<<< orphan*/ * hcd; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xhci_hcd* hcd_to_xhci (int /*<<< orphan*/ *) ; 
 struct tegra_xusb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_xusb_padctl_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_hcd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_remove_hcd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_xusb_remove(struct platform_device *pdev)
{
	struct tegra_xusb *tegra = platform_get_drvdata(pdev);
	struct xhci_hcd *xhci = hcd_to_xhci(tegra->hcd);

	usb_remove_hcd(xhci->shared_hcd);
	usb_put_hcd(xhci->shared_hcd);
	xhci->shared_hcd = NULL;
	usb_remove_hcd(tegra->hcd);
	usb_put_hcd(tegra->hcd);

	dma_free_coherent(&pdev->dev, tegra->fw.size, tegra->fw.virt,
			  tegra->fw.phys);

	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	tegra_xusb_padctl_put(tegra->padctl);

	return 0;
}