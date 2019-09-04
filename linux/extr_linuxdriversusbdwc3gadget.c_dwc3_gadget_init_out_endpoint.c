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
struct TYPE_5__ {int type_iso; int type_bulk; int type_int; } ;
struct TYPE_6__ {int max_streams; TYPE_2__ caps; int /*<<< orphan*/  ep_list; int /*<<< orphan*/ * ops; } ;
struct dwc3_ep {TYPE_3__ endpoint; struct dwc3* dwc; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep_list; } ;
struct dwc3 {TYPE_1__ gadget; } ;

/* Variables and functions */
 int dwc3_alloc_trb_pool (struct dwc3_ep*) ; 
 int /*<<< orphan*/  dwc3_gadget_ep_ops ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_3__*,int) ; 

__attribute__((used)) static int dwc3_gadget_init_out_endpoint(struct dwc3_ep *dep)
{
	struct dwc3 *dwc = dep->dwc;

	usb_ep_set_maxpacket_limit(&dep->endpoint, 1024);
	dep->endpoint.max_streams = 15;
	dep->endpoint.ops = &dwc3_gadget_ep_ops;
	list_add_tail(&dep->endpoint.ep_list,
			&dwc->gadget.ep_list);
	dep->endpoint.caps.type_iso = true;
	dep->endpoint.caps.type_bulk = true;
	dep->endpoint.caps.type_int = true;

	return dwc3_alloc_trb_pool(dep);
}