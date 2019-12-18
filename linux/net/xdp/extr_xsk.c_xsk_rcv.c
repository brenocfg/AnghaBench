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
typedef  scalar_t__ u32 ;
struct xdp_sock {scalar_t__ dev; scalar_t__ queue_id; } ;
struct xdp_buff {TYPE_2__* rxq; scalar_t__ data; scalar_t__ data_end; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ dev; scalar_t__ queue_index; TYPE_1__ mem; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEM_TYPE_ZERO_COPY ; 
 int __xsk_rcv (struct xdp_sock*,struct xdp_buff*,scalar_t__) ; 
 int __xsk_rcv_zc (struct xdp_sock*,struct xdp_buff*,scalar_t__) ; 
 int /*<<< orphan*/  xsk_is_bound (struct xdp_sock*) ; 

int xsk_rcv(struct xdp_sock *xs, struct xdp_buff *xdp)
{
	u32 len;

	if (!xsk_is_bound(xs))
		return -EINVAL;

	if (xs->dev != xdp->rxq->dev || xs->queue_id != xdp->rxq->queue_index)
		return -EINVAL;

	len = xdp->data_end - xdp->data;

	return (xdp->rxq->mem.type == MEM_TYPE_ZERO_COPY) ?
		__xsk_rcv_zc(xs, xdp, len) : __xsk_rcv(xs, xdp, len);
}