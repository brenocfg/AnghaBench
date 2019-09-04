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
struct dwc3_request {int dummy; } ;
struct dwc3_ep {int /*<<< orphan*/  pending_list; void* flags; } ;
struct dwc3 {int delayed_status; int /*<<< orphan*/  ep0state; struct dwc3_ep** eps; } ;

/* Variables and functions */
 void* DWC3_EP_ENABLED ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  EP0_SETUP_PHASE ; 
 int /*<<< orphan*/  __dwc3_gadget_ep_set_halt (struct dwc3_ep*,int,int) ; 
 int /*<<< orphan*/  dwc3_ep0_out_start (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_giveback (struct dwc3_ep*,struct dwc3_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct dwc3_request* next_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc3_ep0_stall_and_restart(struct dwc3 *dwc)
{
	struct dwc3_ep		*dep;

	/* reinitialize physical ep1 */
	dep = dwc->eps[1];
	dep->flags = DWC3_EP_ENABLED;

	/* stall is always issued on EP0 */
	dep = dwc->eps[0];
	__dwc3_gadget_ep_set_halt(dep, 1, false);
	dep->flags = DWC3_EP_ENABLED;
	dwc->delayed_status = false;

	if (!list_empty(&dep->pending_list)) {
		struct dwc3_request	*req;

		req = next_request(&dep->pending_list);
		dwc3_gadget_giveback(dep, req, -ECONNRESET);
	}

	dwc->ep0state = EP0_SETUP_PHASE;
	dwc3_ep0_out_start(dwc);
}