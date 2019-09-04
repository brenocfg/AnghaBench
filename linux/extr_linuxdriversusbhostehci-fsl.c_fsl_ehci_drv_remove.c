#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {TYPE_1__* usb_phy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_usb2_platform_data {int /*<<< orphan*/  (* exit ) (struct platform_device*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_1__*) ; 
 struct fsl_usb2_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otg_set_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_phy (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int fsl_ehci_drv_remove(struct platform_device *pdev)
{
	struct fsl_usb2_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	if (!IS_ERR_OR_NULL(hcd->usb_phy)) {
		otg_set_host(hcd->usb_phy->otg, NULL);
		usb_put_phy(hcd->usb_phy);
	}

	usb_remove_hcd(hcd);

	/*
	 * do platform specific un-initialization:
	 * release iomux pins, disable clock, etc.
	 */
	if (pdata->exit)
		pdata->exit(pdev);
	usb_put_hcd(hcd);

	return 0;
}