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
struct vhci {int /*<<< orphan*/ * vhci_hcd_ss; int /*<<< orphan*/ * vhci_hcd_hs; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_remove_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhci_hcd_to_hcd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vhci_hcd_remove(struct platform_device *pdev)
{
	struct vhci *vhci = *((void **)dev_get_platdata(&pdev->dev));

	/*
	 * Disconnects the root hub,
	 * then reverses the effects of usb_add_hcd(),
	 * invoking the HCD's stop() methods.
	 */
	usb_remove_hcd(vhci_hcd_to_hcd(vhci->vhci_hcd_ss));
	usb_put_hcd(vhci_hcd_to_hcd(vhci->vhci_hcd_ss));

	usb_remove_hcd(vhci_hcd_to_hcd(vhci->vhci_hcd_hs));
	usb_put_hcd(vhci_hcd_to_hcd(vhci->vhci_hcd_hs));

	vhci->vhci_hcd_hs = NULL;
	vhci->vhci_hcd_ss = NULL;

	return 0;
}