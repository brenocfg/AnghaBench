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
struct usb_hcd {TYPE_1__* driver; int /*<<< orphan*/  rh_registered; } ;
struct platform_device {int dummy; } ;
struct ehci_hcd_mv {struct usb_hcd* hcd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* shutdown ) (struct usb_hcd*) ;} ;

/* Variables and functions */
 struct ehci_hcd_mv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct usb_hcd*) ; 

__attribute__((used)) static void mv_ehci_shutdown(struct platform_device *pdev)
{
	struct ehci_hcd_mv *ehci_mv = platform_get_drvdata(pdev);
	struct usb_hcd *hcd = ehci_mv->hcd;

	if (!hcd->rh_registered)
		return;

	if (hcd->driver->shutdown)
		hcd->driver->shutdown(hcd);
}