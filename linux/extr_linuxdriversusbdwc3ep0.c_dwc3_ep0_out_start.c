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
struct dwc3_ep {int dummy; } ;
struct dwc3 {int /*<<< orphan*/  ep0_trb_addr; struct dwc3_ep** eps; int /*<<< orphan*/  ep0_in_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_TRBCTL_CONTROL_SETUP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc3_ep0_prepare_one_trb (struct dwc3_ep*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int dwc3_ep0_start_trans (struct dwc3_ep*) ; 

void dwc3_ep0_out_start(struct dwc3 *dwc)
{
	struct dwc3_ep			*dep;
	int				ret;

	complete(&dwc->ep0_in_setup);

	dep = dwc->eps[0];
	dwc3_ep0_prepare_one_trb(dep, dwc->ep0_trb_addr, 8,
			DWC3_TRBCTL_CONTROL_SETUP, false);
	ret = dwc3_ep0_start_trans(dep);
	WARN_ON(ret < 0);
}