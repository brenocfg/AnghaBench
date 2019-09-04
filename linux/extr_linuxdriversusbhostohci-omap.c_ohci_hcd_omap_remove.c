#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; int /*<<< orphan*/  regs; TYPE_2__* usb_phy; TYPE_1__ self; } ;
struct platform_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_2__*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_omap_osk () ; 
 int /*<<< orphan*/  omap_ohci_clock_power (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_set_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dc_ck ; 
 int /*<<< orphan*/  usb_host_ck ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_phy (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ohci_hcd_omap_remove(struct platform_device *pdev)
{
	struct usb_hcd	*hcd = platform_get_drvdata(pdev);

	dev_dbg(hcd->self.controller, "stopping USB Controller\n");
	usb_remove_hcd(hcd);
	omap_ohci_clock_power(0);
	if (!IS_ERR_OR_NULL(hcd->usb_phy)) {
		(void) otg_set_host(hcd->usb_phy->otg, 0);
		usb_put_phy(hcd->usb_phy);
	}
	if (machine_is_omap_osk())
		gpio_free(9);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);
	clk_put(usb_dc_ck);
	clk_put(usb_host_ck);
	return 0;
}