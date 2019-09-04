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
struct xhci_hcd {int /*<<< orphan*/  quirks; } ;
struct TYPE_2__ {int /*<<< orphan*/  controller; } ;
struct usb_hcd {TYPE_1__ self; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  XHCI_NO_64BIT_SUPPORT ; 
 int /*<<< orphan*/  XHCI_TRUST_TX_LENGTH ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int xhci_rcar_download_firmware (struct usb_hcd*) ; 
 scalar_t__ xhci_rcar_is_gen2 (int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_rcar_is_gen3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_rcar_wait_for_pll_active (struct usb_hcd*) ; 

int xhci_rcar_init_quirk(struct usb_hcd *hcd)
{
	struct xhci_hcd *xhci = hcd_to_xhci(hcd);

	/* If hcd->regs is NULL, we don't just call the following function */
	if (!hcd->regs)
		return 0;

	/*
	 * On R-Car Gen2 and Gen3, the AC64 bit (bit 0) of HCCPARAMS1 is set
	 * to 1. However, these SoCs don't support 64-bit address memory
	 * pointers. So, this driver clears the AC64 bit of xhci->hcc_params
	 * to call dma_set_coherent_mask(dev, DMA_BIT_MASK(32)) in
	 * xhci_gen_setup().
	 */
	if (xhci_rcar_is_gen2(hcd->self.controller) ||
			xhci_rcar_is_gen3(hcd->self.controller))
		xhci->quirks |= XHCI_NO_64BIT_SUPPORT;

	if (!xhci_rcar_wait_for_pll_active(hcd))
		return -ETIMEDOUT;

	xhci->quirks |= XHCI_TRUST_TX_LENGTH;
	return xhci_rcar_download_firmware(hcd);
}