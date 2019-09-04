#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_1__ generic; } ;
typedef  int u32 ;
struct xhci_virt_ep {int dummy; } ;
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; } ;
struct xhci_transfer_event {int /*<<< orphan*/  transfer_len; int /*<<< orphan*/  flags; } ;
struct xhci_td {int urb_length_set; TYPE_2__* urb; } ;
struct xhci_hcd {struct xhci_virt_device** devs; } ;
struct xhci_ep_ctx {int dummy; } ;
struct TYPE_4__ {int transfer_buffer_length; int actual_length; } ;

/* Variables and functions */
#define  COMP_SHORT_PACKET 137 
#define  COMP_STALL_ERROR 136 
#define  COMP_STOPPED 135 
#define  COMP_STOPPED_LENGTH_INVALID 134 
#define  COMP_STOPPED_SHORT_PACKET 133 
#define  COMP_SUCCESS 132 
 int ESHUTDOWN ; 
 int EVENT_TRB_LEN (int /*<<< orphan*/ ) ; 
 int GET_COMP_CODE (int /*<<< orphan*/ ) ; 
#define  TRB_DATA 131 
 int TRB_FIELD_TO_TYPE (int /*<<< orphan*/ ) ; 
#define  TRB_NORMAL 130 
#define  TRB_SETUP 129 
#define  TRB_STATUS 128 
 int TRB_TO_EP_ID (int /*<<< orphan*/ ) ; 
 unsigned int TRB_TO_SLOT_ID (int /*<<< orphan*/ ) ; 
 int finish_td (struct xhci_hcd*,struct xhci_td*,struct xhci_transfer_event*,struct xhci_virt_ep*,int*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,...) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhci_requires_manual_halt_cleanup (struct xhci_hcd*,struct xhci_ep_ctx*,int) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,...) ; 

__attribute__((used)) static int process_ctrl_td(struct xhci_hcd *xhci, struct xhci_td *td,
	union xhci_trb *ep_trb, struct xhci_transfer_event *event,
	struct xhci_virt_ep *ep, int *status)
{
	struct xhci_virt_device *xdev;
	unsigned int slot_id;
	int ep_index;
	struct xhci_ep_ctx *ep_ctx;
	u32 trb_comp_code;
	u32 remaining, requested;
	u32 trb_type;

	trb_type = TRB_FIELD_TO_TYPE(le32_to_cpu(ep_trb->generic.field[3]));
	slot_id = TRB_TO_SLOT_ID(le32_to_cpu(event->flags));
	xdev = xhci->devs[slot_id];
	ep_index = TRB_TO_EP_ID(le32_to_cpu(event->flags)) - 1;
	ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);
	trb_comp_code = GET_COMP_CODE(le32_to_cpu(event->transfer_len));
	requested = td->urb->transfer_buffer_length;
	remaining = EVENT_TRB_LEN(le32_to_cpu(event->transfer_len));

	switch (trb_comp_code) {
	case COMP_SUCCESS:
		if (trb_type != TRB_STATUS) {
			xhci_warn(xhci, "WARN: Success on ctrl %s TRB without IOC set?\n",
				  (trb_type == TRB_DATA) ? "data" : "setup");
			*status = -ESHUTDOWN;
			break;
		}
		*status = 0;
		break;
	case COMP_SHORT_PACKET:
		*status = 0;
		break;
	case COMP_STOPPED_SHORT_PACKET:
		if (trb_type == TRB_DATA || trb_type == TRB_NORMAL)
			td->urb->actual_length = remaining;
		else
			xhci_warn(xhci, "WARN: Stopped Short Packet on ctrl setup or status TRB\n");
		goto finish_td;
	case COMP_STOPPED:
		switch (trb_type) {
		case TRB_SETUP:
			td->urb->actual_length = 0;
			goto finish_td;
		case TRB_DATA:
		case TRB_NORMAL:
			td->urb->actual_length = requested - remaining;
			goto finish_td;
		case TRB_STATUS:
			td->urb->actual_length = requested;
			goto finish_td;
		default:
			xhci_warn(xhci, "WARN: unexpected TRB Type %d\n",
				  trb_type);
			goto finish_td;
		}
	case COMP_STOPPED_LENGTH_INVALID:
		goto finish_td;
	default:
		if (!xhci_requires_manual_halt_cleanup(xhci,
						       ep_ctx, trb_comp_code))
			break;
		xhci_dbg(xhci, "TRB error %u, halted endpoint index = %u\n",
			 trb_comp_code, ep_index);
		/* else fall through */
	case COMP_STALL_ERROR:
		/* Did we transfer part of the data (middle) phase? */
		if (trb_type == TRB_DATA || trb_type == TRB_NORMAL)
			td->urb->actual_length = requested - remaining;
		else if (!td->urb_length_set)
			td->urb->actual_length = 0;
		goto finish_td;
	}

	/* stopped at setup stage, no data transferred */
	if (trb_type == TRB_SETUP)
		goto finish_td;

	/*
	 * if on data stage then update the actual_length of the URB and flag it
	 * as set, so it won't be overwritten in the event for the last TRB.
	 */
	if (trb_type == TRB_DATA ||
		trb_type == TRB_NORMAL) {
		td->urb_length_set = true;
		td->urb->actual_length = requested - remaining;
		xhci_dbg(xhci, "Waiting for status stage event\n");
		return 0;
	}

	/* at status stage */
	if (!td->urb_length_set)
		td->urb->actual_length = requested;

finish_td:
	return finish_td(xhci, td, event, ep, status);
}