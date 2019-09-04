#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct fhci_usb {scalar_t__ port_status; TYPE_5__* actual_frame; int /*<<< orphan*/  max_frame_usage; int /*<<< orphan*/  saved_msk; TYPE_4__* fhci; TYPE_2__* vroot_hub; } ;
struct fhci_hcd {int /*<<< orphan*/  timer; struct fhci_usb* usb_lld; } ;
struct TYPE_10__ {int /*<<< orphan*/  frame_status; } ;
struct TYPE_9__ {TYPE_3__* regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  usb_usbmr; } ;
struct TYPE_6__ {int wPortStatus; int wPortChange; } ;
struct TYPE_7__ {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ FHCI_PORT_DISABLED ; 
 scalar_t__ FHCI_PORT_FULL ; 
 scalar_t__ FHCI_PORT_LOW ; 
 int /*<<< orphan*/  FRAME_IS_TRANSMITTED ; 
 int /*<<< orphan*/  USB_E_IDLE_MASK ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_C_CONNECTION ; 
 int USB_PORT_STAT_LOW_SPEED ; 
 int /*<<< orphan*/  fhci_host_transmit_actual_frame (struct fhci_usb*) ; 
 int /*<<< orphan*/  fhci_schedule_transactions (struct fhci_usb*) ; 
 int /*<<< orphan*/  gtm_set_exact_timer16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sof_interrupt(struct fhci_hcd *fhci)
{
	struct fhci_usb *usb = fhci->usb_lld;

	if ((usb->port_status == FHCI_PORT_DISABLED) &&
	    (usb->vroot_hub->port.wPortStatus & USB_PORT_STAT_CONNECTION) &&
	    !(usb->vroot_hub->port.wPortChange & USB_PORT_STAT_C_CONNECTION)) {
		if (usb->vroot_hub->port.wPortStatus & USB_PORT_STAT_LOW_SPEED)
			usb->port_status = FHCI_PORT_LOW;
		else
			usb->port_status = FHCI_PORT_FULL;
		/* Disable IDLE */
		usb->saved_msk &= ~USB_E_IDLE_MASK;
		out_be16(&usb->fhci->regs->usb_usbmr, usb->saved_msk);
	}

	gtm_set_exact_timer16(fhci->timer, usb->max_frame_usage, false);

	fhci_host_transmit_actual_frame(usb);
	usb->actual_frame->frame_status = FRAME_IS_TRANSMITTED;

	fhci_schedule_transactions(usb);
}