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
struct TYPE_2__ {int /*<<< orphan*/  status; scalar_t__ actual; } ;
struct dwc3_request {int /*<<< orphan*/  list; int /*<<< orphan*/  epnum; TYPE_1__ request; } ;
struct dwc3_ep {int flags; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  number; struct dwc3* dwc; } ;
struct dwc3 {scalar_t__ ep0state; int delayed_status; unsigned int ep0_expect_in; int /*<<< orphan*/ * eps; scalar_t__ three_stage_setup; int /*<<< orphan*/  gadget; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DWC3_EP0_DIR_IN ; 
 int DWC3_EP_PENDING_REQUEST ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 scalar_t__ EP0_DATA_PHASE ; 
 scalar_t__ EP0_STATUS_PHASE ; 
 int /*<<< orphan*/  USB_STATE_CONFIGURED ; 
 int /*<<< orphan*/  __dwc3_ep0_do_control_data (struct dwc3*,int /*<<< orphan*/ ,struct dwc3_request*) ; 
 int /*<<< orphan*/  __dwc3_ep0_do_control_status (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dwc3_gadget_ep0_queue(struct dwc3_ep *dep,
		struct dwc3_request *req)
{
	struct dwc3		*dwc = dep->dwc;

	req->request.actual	= 0;
	req->request.status	= -EINPROGRESS;
	req->epnum		= dep->number;

	list_add_tail(&req->list, &dep->pending_list);

	/*
	 * Gadget driver might not be quick enough to queue a request
	 * before we get a Transfer Not Ready event on this endpoint.
	 *
	 * In that case, we will set DWC3_EP_PENDING_REQUEST. When that
	 * flag is set, it's telling us that as soon as Gadget queues the
	 * required request, we should kick the transfer here because the
	 * IRQ we were waiting for is long gone.
	 */
	if (dep->flags & DWC3_EP_PENDING_REQUEST) {
		unsigned	direction;

		direction = !!(dep->flags & DWC3_EP0_DIR_IN);

		if (dwc->ep0state != EP0_DATA_PHASE) {
			dev_WARN(dwc->dev, "Unexpected pending request\n");
			return 0;
		}

		__dwc3_ep0_do_control_data(dwc, dwc->eps[direction], req);

		dep->flags &= ~(DWC3_EP_PENDING_REQUEST |
				DWC3_EP0_DIR_IN);

		return 0;
	}

	/*
	 * In case gadget driver asked us to delay the STATUS phase,
	 * handle it here.
	 */
	if (dwc->delayed_status) {
		unsigned	direction;

		direction = !dwc->ep0_expect_in;
		dwc->delayed_status = false;
		usb_gadget_set_state(&dwc->gadget, USB_STATE_CONFIGURED);

		if (dwc->ep0state == EP0_STATUS_PHASE)
			__dwc3_ep0_do_control_status(dwc, dwc->eps[direction]);

		return 0;
	}

	/*
	 * Unfortunately we have uncovered a limitation wrt the Data Phase.
	 *
	 * Section 9.4 says we can wait for the XferNotReady(DATA) event to
	 * come before issueing Start Transfer command, but if we do, we will
	 * miss situations where the host starts another SETUP phase instead of
	 * the DATA phase.  Such cases happen at least on TD.7.6 of the Link
	 * Layer Compliance Suite.
	 *
	 * The problem surfaces due to the fact that in case of back-to-back
	 * SETUP packets there will be no XferNotReady(DATA) generated and we
	 * will be stuck waiting for XferNotReady(DATA) forever.
	 *
	 * By looking at tables 9-13 and 9-14 of the Databook, we can see that
	 * it tells us to start Data Phase right away. It also mentions that if
	 * we receive a SETUP phase instead of the DATA phase, core will issue
	 * XferComplete for the DATA phase, before actually initiating it in
	 * the wire, with the TRB's status set to "SETUP_PENDING". Such status
	 * can only be used to print some debugging logs, as the core expects
	 * us to go through to the STATUS phase and start a CONTROL_STATUS TRB,
	 * just so it completes right away, without transferring anything and,
	 * only then, we can go back to the SETUP phase.
	 *
	 * Because of this scenario, SNPS decided to change the programming
	 * model of control transfers and support on-demand transfers only for
	 * the STATUS phase. To fix the issue we have now, we will always wait
	 * for gadget driver to queue the DATA phase's struct usb_request, then
	 * start it right away.
	 *
	 * If we're actually in a 2-stage transfer, we will wait for
	 * XferNotReady(STATUS).
	 */
	if (dwc->three_stage_setup) {
		unsigned        direction;

		direction = dwc->ep0_expect_in;
		dwc->ep0state = EP0_DATA_PHASE;

		__dwc3_ep0_do_control_data(dwc, dwc->eps[direction], req);

		dep->flags &= ~DWC3_EP0_DIR_IN;
	}

	return 0;
}