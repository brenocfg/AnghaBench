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
struct xhci_virt_ep {int /*<<< orphan*/  bw_endpoint_list; } ;
struct xhci_tt_bw_info {int active_eps; } ;
struct xhci_interval_bw_table {struct xhci_interval_bw* interval_bw; int /*<<< orphan*/  interval0_esit_payload; } ;
struct xhci_interval_bw {int* overhead; int /*<<< orphan*/  num_packets; } ;
struct xhci_hcd {TYPE_2__** devs; } ;
struct xhci_bw_info {int ep_interval; scalar_t__ num_packets; scalar_t__ max_esit_payload; int /*<<< orphan*/  type; } ;
struct usb_device {int speed; size_t slot_id; } ;
struct TYPE_4__ {TYPE_1__* bw_table; } ;
struct TYPE_3__ {int /*<<< orphan*/  ss_bw_out; int /*<<< orphan*/  ss_bw_in; } ;

/* Variables and functions */
 size_t FS_OVERHEAD_TYPE ; 
 size_t HS_OVERHEAD_TYPE ; 
 size_t LS_OVERHEAD_TYPE ; 
#define  USB_SPEED_FULL 134 
#define  USB_SPEED_HIGH 133 
#define  USB_SPEED_LOW 132 
#define  USB_SPEED_SUPER 131 
#define  USB_SPEED_SUPER_PLUS 130 
#define  USB_SPEED_UNKNOWN 129 
#define  USB_SPEED_WIRELESS 128 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ xhci_get_ss_bw_consumed (struct xhci_bw_info*) ; 
 scalar_t__ xhci_is_async_ep (int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_is_sync_in_ep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_drop_ep_from_interval_table(struct xhci_hcd *xhci,
		struct xhci_bw_info *ep_bw,
		struct xhci_interval_bw_table *bw_table,
		struct usb_device *udev,
		struct xhci_virt_ep *virt_ep,
		struct xhci_tt_bw_info *tt_info)
{
	struct xhci_interval_bw	*interval_bw;
	int normalized_interval;

	if (xhci_is_async_ep(ep_bw->type))
		return;

	if (udev->speed >= USB_SPEED_SUPER) {
		if (xhci_is_sync_in_ep(ep_bw->type))
			xhci->devs[udev->slot_id]->bw_table->ss_bw_in -=
				xhci_get_ss_bw_consumed(ep_bw);
		else
			xhci->devs[udev->slot_id]->bw_table->ss_bw_out -=
				xhci_get_ss_bw_consumed(ep_bw);
		return;
	}

	/* SuperSpeed endpoints never get added to intervals in the table, so
	 * this check is only valid for HS/FS/LS devices.
	 */
	if (list_empty(&virt_ep->bw_endpoint_list))
		return;
	/* For LS/FS devices, we need to translate the interval expressed in
	 * microframes to frames.
	 */
	if (udev->speed == USB_SPEED_HIGH)
		normalized_interval = ep_bw->ep_interval;
	else
		normalized_interval = ep_bw->ep_interval - 3;

	if (normalized_interval == 0)
		bw_table->interval0_esit_payload -= ep_bw->max_esit_payload;
	interval_bw = &bw_table->interval_bw[normalized_interval];
	interval_bw->num_packets -= ep_bw->num_packets;
	switch (udev->speed) {
	case USB_SPEED_LOW:
		interval_bw->overhead[LS_OVERHEAD_TYPE] -= 1;
		break;
	case USB_SPEED_FULL:
		interval_bw->overhead[FS_OVERHEAD_TYPE] -= 1;
		break;
	case USB_SPEED_HIGH:
		interval_bw->overhead[HS_OVERHEAD_TYPE] -= 1;
		break;
	case USB_SPEED_SUPER:
	case USB_SPEED_SUPER_PLUS:
	case USB_SPEED_UNKNOWN:
	case USB_SPEED_WIRELESS:
		/* Should never happen because only LS/FS/HS endpoints will get
		 * added to the endpoint list.
		 */
		return;
	}
	if (tt_info)
		tt_info->active_eps -= 1;
	list_del_init(&virt_ep->bw_endpoint_list);
}