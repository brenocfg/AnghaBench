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
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; } ;
struct xhci_td {int /*<<< orphan*/  first_trb; int /*<<< orphan*/  start_seg; int /*<<< orphan*/  td_list; struct urb* urb; int /*<<< orphan*/  cancelled_td_list; } ;
struct xhci_ring {int /*<<< orphan*/  enqueue; int /*<<< orphan*/  enq_seg; int /*<<< orphan*/  td_list; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_ep_ctx {int dummy; } ;
struct urb_priv {struct xhci_td* td; } ;
struct urb {TYPE_1__* dev; struct urb_priv* hcpriv; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GET_EP_CTX_STATE (struct xhci_ep_ctx*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int prepare_ring (struct xhci_hcd*,struct xhci_ring*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int usb_hcd_link_urb_to_ep (int /*<<< orphan*/ ,struct urb*) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,unsigned int) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int) ; 
 struct xhci_ring* xhci_stream_id_to_ring (struct xhci_virt_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int prepare_transfer(struct xhci_hcd *xhci,
		struct xhci_virt_device *xdev,
		unsigned int ep_index,
		unsigned int stream_id,
		unsigned int num_trbs,
		struct urb *urb,
		unsigned int td_index,
		gfp_t mem_flags)
{
	int ret;
	struct urb_priv *urb_priv;
	struct xhci_td	*td;
	struct xhci_ring *ep_ring;
	struct xhci_ep_ctx *ep_ctx = xhci_get_ep_ctx(xhci, xdev->out_ctx, ep_index);

	ep_ring = xhci_stream_id_to_ring(xdev, ep_index, stream_id);
	if (!ep_ring) {
		xhci_dbg(xhci, "Can't prepare ring for bad stream ID %u\n",
				stream_id);
		return -EINVAL;
	}

	ret = prepare_ring(xhci, ep_ring, GET_EP_CTX_STATE(ep_ctx),
			   num_trbs, mem_flags);
	if (ret)
		return ret;

	urb_priv = urb->hcpriv;
	td = &urb_priv->td[td_index];

	INIT_LIST_HEAD(&td->td_list);
	INIT_LIST_HEAD(&td->cancelled_td_list);

	if (td_index == 0) {
		ret = usb_hcd_link_urb_to_ep(bus_to_hcd(urb->dev->bus), urb);
		if (unlikely(ret))
			return ret;
	}

	td->urb = urb;
	/* Add this TD to the tail of the endpoint ring's TD list */
	list_add_tail(&td->td_list, &ep_ring->td_list);
	td->start_seg = ep_ring->enq_seg;
	td->first_trb = ep_ring->enqueue;

	return 0;
}