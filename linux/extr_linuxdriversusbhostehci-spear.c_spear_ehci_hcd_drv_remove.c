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
struct spear_ehci {scalar_t__ clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 struct spear_ehci* to_spear_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int spear_ehci_hcd_drv_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);
	struct spear_ehci *sehci = to_spear_ehci(hcd);

	usb_remove_hcd(hcd);

	if (sehci->clk)
		clk_disable_unprepare(sehci->clk);
	usb_put_hcd(hcd);

	return 0;
}