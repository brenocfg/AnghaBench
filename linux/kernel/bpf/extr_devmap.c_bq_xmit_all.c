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
typedef  int /*<<< orphan*/  u32 ;
struct xdp_frame {int dummy; } ;
struct xdp_bulk_queue {int count; struct xdp_frame** q; int /*<<< orphan*/  flush_node; int /*<<< orphan*/ * dev_rx; struct bpf_dtab_netdev* obj; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct bpf_dtab_netdev {int /*<<< orphan*/  idx; TYPE_2__* dtab; struct net_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;
struct TYPE_3__ {int (* ndo_xdp_xmit ) (struct net_device*,int,struct xdp_frame**,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __list_del_clearprev (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  prefetch (struct xdp_frame*) ; 
 int stub1 (struct net_device*,int,struct xdp_frame**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xdp_devmap_xmit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,struct net_device*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame (struct xdp_frame*) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

__attribute__((used)) static int bq_xmit_all(struct xdp_bulk_queue *bq, u32 flags,
		       bool in_napi_ctx)
{
	struct bpf_dtab_netdev *obj = bq->obj;
	struct net_device *dev = obj->dev;
	int sent = 0, drops = 0, err = 0;
	int i;

	if (unlikely(!bq->count))
		return 0;

	for (i = 0; i < bq->count; i++) {
		struct xdp_frame *xdpf = bq->q[i];

		prefetch(xdpf);
	}

	sent = dev->netdev_ops->ndo_xdp_xmit(dev, bq->count, bq->q, flags);
	if (sent < 0) {
		err = sent;
		sent = 0;
		goto error;
	}
	drops = bq->count - sent;
out:
	bq->count = 0;

	trace_xdp_devmap_xmit(&obj->dtab->map, obj->idx,
			      sent, drops, bq->dev_rx, dev, err);
	bq->dev_rx = NULL;
	__list_del_clearprev(&bq->flush_node);
	return 0;
error:
	/* If ndo_xdp_xmit fails with an errno, no frames have been
	 * xmit'ed and it's our responsibility to them free all.
	 */
	for (i = 0; i < bq->count; i++) {
		struct xdp_frame *xdpf = bq->q[i];

		/* RX path under NAPI protection, can return frames faster */
		if (likely(in_napi_ctx))
			xdp_return_frame_rx_napi(xdpf);
		else
			xdp_return_frame(xdpf);
		drops++;
	}
	goto out;
}