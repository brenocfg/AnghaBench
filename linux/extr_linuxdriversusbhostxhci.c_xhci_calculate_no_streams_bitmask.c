#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xhci_hcd {TYPE_2__** devs; } ;
struct TYPE_7__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_3__ desc; } ;
struct usb_device {unsigned int slot_id; } ;
struct TYPE_6__ {TYPE_1__* eps; } ;
struct TYPE_5__ {unsigned int ep_state; } ;

/* Variables and functions */
 unsigned int EP_GETTING_NO_STREAMS ; 
 unsigned int EP_GETTING_STREAMS ; 
 unsigned int EP_HAS_STREAMS ; 
 int /*<<< orphan*/  xhci_get_endpoint_flag (TYPE_3__*) ; 
 unsigned int xhci_get_endpoint_index (TYPE_3__*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,...) ; 

__attribute__((used)) static u32 xhci_calculate_no_streams_bitmask(struct xhci_hcd *xhci,
		struct usb_device *udev,
		struct usb_host_endpoint **eps, unsigned int num_eps)
{
	u32 changed_ep_bitmask = 0;
	unsigned int slot_id;
	unsigned int ep_index;
	unsigned int ep_state;
	int i;

	slot_id = udev->slot_id;
	if (!xhci->devs[slot_id])
		return 0;

	for (i = 0; i < num_eps; i++) {
		ep_index = xhci_get_endpoint_index(&eps[i]->desc);
		ep_state = xhci->devs[slot_id]->eps[ep_index].ep_state;
		/* Are streams already being freed for the endpoint? */
		if (ep_state & EP_GETTING_NO_STREAMS) {
			xhci_warn(xhci, "WARN Can't disable streams for "
					"endpoint 0x%x, "
					"streams are being disabled already\n",
					eps[i]->desc.bEndpointAddress);
			return 0;
		}
		/* Are there actually any streams to free? */
		if (!(ep_state & EP_HAS_STREAMS) &&
				!(ep_state & EP_GETTING_STREAMS)) {
			xhci_warn(xhci, "WARN Can't disable streams for "
					"endpoint 0x%x, "
					"streams are already disabled!\n",
					eps[i]->desc.bEndpointAddress);
			xhci_warn(xhci, "WARN xhci_free_streams() called "
					"with non-streams endpoint\n");
			return 0;
		}
		changed_ep_bitmask |= xhci_get_endpoint_flag(&eps[i]->desc);
	}
	return changed_ep_bitmask;
}