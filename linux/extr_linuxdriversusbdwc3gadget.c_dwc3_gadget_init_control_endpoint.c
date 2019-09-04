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
struct TYPE_5__ {int type_control; } ;
struct TYPE_6__ {int maxburst; TYPE_2__ caps; int /*<<< orphan*/ * ops; } ;
struct dwc3_ep {TYPE_3__ endpoint; int /*<<< orphan*/  direction; struct dwc3* dwc; } ;
struct TYPE_4__ {TYPE_3__* ep0; } ;
struct dwc3 {TYPE_1__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc3_gadget_ep0_ops ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_3__*,int) ; 

__attribute__((used)) static int dwc3_gadget_init_control_endpoint(struct dwc3_ep *dep)
{
	struct dwc3 *dwc = dep->dwc;

	usb_ep_set_maxpacket_limit(&dep->endpoint, 512);
	dep->endpoint.maxburst = 1;
	dep->endpoint.ops = &dwc3_gadget_ep0_ops;
	if (!dep->direction)
		dwc->gadget.ep0 = &dep->endpoint;

	dep->endpoint.caps.type_control = true;

	return 0;
}