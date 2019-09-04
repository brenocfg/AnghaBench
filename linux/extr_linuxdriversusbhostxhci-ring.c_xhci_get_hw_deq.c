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
typedef  int /*<<< orphan*/  u64 ;
struct xhci_virt_ep {int ep_state; TYPE_1__* stream_info; } ;
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; struct xhci_virt_ep* eps; } ;
struct xhci_stream_ctx {int /*<<< orphan*/  stream_ring; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_ep_ctx {int /*<<< orphan*/  deq; } ;
struct TYPE_2__ {struct xhci_stream_ctx* stream_ctx_array; } ;

/* Variables and functions */
 int EP_HAS_STREAMS ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static u64 xhci_get_hw_deq(struct xhci_hcd *xhci, struct xhci_virt_device *vdev,
			   unsigned int ep_index, unsigned int stream_id)
{
	struct xhci_ep_ctx *ep_ctx;
	struct xhci_stream_ctx *st_ctx;
	struct xhci_virt_ep *ep;

	ep = &vdev->eps[ep_index];

	if (ep->ep_state & EP_HAS_STREAMS) {
		st_ctx = &ep->stream_info->stream_ctx_array[stream_id];
		return le64_to_cpu(st_ctx->stream_ring);
	}
	ep_ctx = xhci_get_ep_ctx(xhci, vdev->out_ctx, ep_index);
	return le64_to_cpu(ep_ctx->deq);
}