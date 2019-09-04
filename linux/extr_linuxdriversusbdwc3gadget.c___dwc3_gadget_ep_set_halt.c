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
struct dwc3_trb {unsigned int ctrl; } ;
struct dwc3_gadget_ep_cmd_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;
struct dwc3_ep {int number; size_t trb_enqueue; int flags; int /*<<< orphan*/  name; scalar_t__ direction; int /*<<< orphan*/  started_list; TYPE_1__ endpoint; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  dev; struct dwc3_trb* ep0_trb; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DEPCMD_SETSTALL ; 
 int DWC3_EP_STALL ; 
 int DWC3_EP_WEDGE ; 
 unsigned int DWC3_TRB_CTRL_HWO ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct dwc3_trb* dwc3_ep_prev_trb (struct dwc3_ep*,size_t) ; 
 int dwc3_send_clear_stall_ep_cmd (struct dwc3_ep*) ; 
 int dwc3_send_gadget_ep_cmd (struct dwc3_ep*,int /*<<< orphan*/ ,struct dwc3_gadget_ep_cmd_params*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dwc3_gadget_ep_cmd_params*,int,int) ; 
 scalar_t__ usb_endpoint_xfer_isoc (int /*<<< orphan*/ ) ; 

int __dwc3_gadget_ep_set_halt(struct dwc3_ep *dep, int value, int protocol)
{
	struct dwc3_gadget_ep_cmd_params	params;
	struct dwc3				*dwc = dep->dwc;
	int					ret;

	if (usb_endpoint_xfer_isoc(dep->endpoint.desc)) {
		dev_err(dwc->dev, "%s is of Isochronous type\n", dep->name);
		return -EINVAL;
	}

	memset(&params, 0x00, sizeof(params));

	if (value) {
		struct dwc3_trb *trb;

		unsigned transfer_in_flight;
		unsigned started;

		if (dep->number > 1)
			trb = dwc3_ep_prev_trb(dep, dep->trb_enqueue);
		else
			trb = &dwc->ep0_trb[dep->trb_enqueue];

		transfer_in_flight = trb->ctrl & DWC3_TRB_CTRL_HWO;
		started = !list_empty(&dep->started_list);

		if (!protocol && ((dep->direction && transfer_in_flight) ||
				(!dep->direction && started))) {
			return -EAGAIN;
		}

		ret = dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_SETSTALL,
				&params);
		if (ret)
			dev_err(dwc->dev, "failed to set STALL on %s\n",
					dep->name);
		else
			dep->flags |= DWC3_EP_STALL;
	} else {

		ret = dwc3_send_clear_stall_ep_cmd(dep);
		if (ret)
			dev_err(dwc->dev, "failed to clear STALL on %s\n",
					dep->name);
		else
			dep->flags &= ~(DWC3_EP_STALL | DWC3_EP_WEDGE);
	}

	return ret;
}