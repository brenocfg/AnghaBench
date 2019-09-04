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
struct udc {int /*<<< orphan*/  nb; int /*<<< orphan*/  edev; int /*<<< orphan*/  udc_phy; scalar_t__ drd_wq; int /*<<< orphan*/  driver; int /*<<< orphan*/  gadget; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  extcon_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  free_dma_pools (struct udc*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udc_remove (struct udc*) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udc_plat_remove(struct platform_device *pdev)
{
	struct udc *dev;

	dev = platform_get_drvdata(pdev);

	usb_del_gadget_udc(&dev->gadget);
	/* gadget driver must not be registered */
	if (WARN_ON(dev->driver))
		return 0;

	/* dma pool cleanup */
	free_dma_pools(dev);

	udc_remove(dev);

	platform_set_drvdata(pdev, NULL);

	if (dev->drd_wq) {
		flush_workqueue(dev->drd_wq);
		destroy_workqueue(dev->drd_wq);
	}

	phy_power_off(dev->udc_phy);
	phy_exit(dev->udc_phy);
	extcon_unregister_notifier(dev->edev, EXTCON_USB, &dev->nb);

	dev_info(&pdev->dev, "Synopsys UDC platform driver removed\n");

	return 0;
}