#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fhci_usb {int intr_nesting_cnt; int saved_msk; struct fhci_hcd* fhci; } ;
struct fhci_hcd {TYPE_1__* timer; TYPE_2__* regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  usb_usbmr; int /*<<< orphan*/  usb_usber; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fhci_info (struct fhci_hcd*,char*) ; 
 TYPE_3__* fhci_to_hcd (struct fhci_hcd*) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 

void fhci_usb_enable_interrupt(struct fhci_usb *usb)
{
	struct fhci_hcd *fhci = usb->fhci;

	if (usb->intr_nesting_cnt == 1) {
		/* initialize the USB interrupt */
		enable_irq(fhci_to_hcd(fhci)->irq);

		/* initialize the event register and mask register */
		out_be16(&usb->fhci->regs->usb_usber, 0xffff);
		out_be16(&usb->fhci->regs->usb_usbmr, usb->saved_msk);

		/* enable the timer interrupts */
		enable_irq(fhci->timer->irq);
	} else if (usb->intr_nesting_cnt > 1)
		fhci_info(fhci, "unbalanced USB interrupts nesting\n");
	usb->intr_nesting_cnt--;
}