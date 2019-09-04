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
struct dwc2_hsotg {unsigned int num_of_eps; int /*<<< orphan*/  gadget; int /*<<< orphan*/  lx_state; scalar_t__* eps_out; scalar_t__* eps_in; scalar_t__ test_mode; scalar_t__ connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_L3 ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  call_gadget (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disconnect ; 
 int /*<<< orphan*/  kill_all_requests (struct dwc2_hsotg*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_gadget_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dwc2_hsotg_disconnect(struct dwc2_hsotg *hsotg)
{
	unsigned int ep;

	if (!hsotg->connected)
		return;

	hsotg->connected = 0;
	hsotg->test_mode = 0;

	/* all endpoints should be shutdown */
	for (ep = 0; ep < hsotg->num_of_eps; ep++) {
		if (hsotg->eps_in[ep])
			kill_all_requests(hsotg, hsotg->eps_in[ep],
					  -ESHUTDOWN);
		if (hsotg->eps_out[ep])
			kill_all_requests(hsotg, hsotg->eps_out[ep],
					  -ESHUTDOWN);
	}

	call_gadget(hsotg, disconnect);
	hsotg->lx_state = DWC2_L3;

	usb_gadget_set_state(&hsotg->gadget, USB_STATE_NOTATTACHED);
}