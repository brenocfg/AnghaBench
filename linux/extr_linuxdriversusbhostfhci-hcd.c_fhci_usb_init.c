#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct fhci_usb {int saved_msk; TYPE_3__* fhci; TYPE_4__* actual_frame; int /*<<< orphan*/  sw_transaction_time; int /*<<< orphan*/  max_frame_usage; int /*<<< orphan*/  port_status; } ;
struct fhci_hcd {TYPE_1__* pram; struct fhci_usb* usb_lld; } ;
struct TYPE_8__ {int /*<<< orphan*/  tds_list; } ;
struct TYPE_7__ {TYPE_2__* regs; int /*<<< orphan*/  pram; } ;
struct TYPE_6__ {int /*<<< orphan*/  usb_usber; int /*<<< orphan*/  usb_usbmr; int /*<<< orphan*/  usb_usmod; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_state; int /*<<< orphan*/  frame_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DATA_MEM ; 
 int /*<<< orphan*/  DEFAULT_RING_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FHCI_PORT_DISABLED ; 
 int /*<<< orphan*/  FHCI_PRAM_SIZE ; 
 int /*<<< orphan*/  FRAME_TIME_USAGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SW_FIX_TIME_BETWEEN_TRANSACTION ; 
 int USB_E_IDLE_MASK ; 
 int USB_E_MSF_MASK ; 
 int USB_E_RESET_MASK ; 
 int USB_E_SFT_MASK ; 
 int USB_E_TXB_MASK ; 
 int USB_E_TXE1_MASK ; 
 int USB_MODE_EN ; 
 int USB_MODE_HOST ; 
 scalar_t__ endpoint_zero_init (struct fhci_usb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fhci_usb_free (struct fhci_usb*) ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fhci_usb_init(struct fhci_hcd *fhci)
{
	struct fhci_usb *usb = fhci->usb_lld;

	memset_io(usb->fhci->pram, 0, FHCI_PRAM_SIZE);

	usb->port_status = FHCI_PORT_DISABLED;
	usb->max_frame_usage = FRAME_TIME_USAGE;
	usb->sw_transaction_time = SW_FIX_TIME_BETWEEN_TRANSACTION;

	usb->actual_frame = kzalloc(sizeof(*usb->actual_frame), GFP_KERNEL);
	if (!usb->actual_frame) {
		fhci_usb_free(usb);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&usb->actual_frame->tds_list);

	/* initializing registers on chip, clear frame number */
	out_be16(&fhci->pram->frame_num, 0);

	/* clear rx state */
	out_be32(&fhci->pram->rx_state, 0);

	/* set mask register */
	usb->saved_msk = (USB_E_TXB_MASK |
			  USB_E_TXE1_MASK |
			  USB_E_IDLE_MASK |
			  USB_E_RESET_MASK | USB_E_SFT_MASK | USB_E_MSF_MASK);

	out_8(&usb->fhci->regs->usb_usmod, USB_MODE_HOST | USB_MODE_EN);

	/* clearing the mask register */
	out_be16(&usb->fhci->regs->usb_usbmr, 0);

	/* initialing the event register */
	out_be16(&usb->fhci->regs->usb_usber, 0xffff);

	if (endpoint_zero_init(usb, DEFAULT_DATA_MEM, DEFAULT_RING_LEN) != 0) {
		fhci_usb_free(usb);
		return -EINVAL;
	}

	return 0;
}