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
struct veth_rq {int /*<<< orphan*/  xdp_napi; int /*<<< orphan*/  xdp_ring; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 void* __ptr_ring_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ veth_is_xdp_frame (void*) ; 
 int /*<<< orphan*/  veth_ptr_to_xdp (void*) ; 
 struct sk_buff* veth_xdp_rcv_one (struct veth_rq*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct sk_buff* veth_xdp_rcv_skb (struct veth_rq*,void*,unsigned int*) ; 

__attribute__((used)) static int veth_xdp_rcv(struct veth_rq *rq, int budget, unsigned int *xdp_xmit)
{
	int i, done = 0;

	for (i = 0; i < budget; i++) {
		void *ptr = __ptr_ring_consume(&rq->xdp_ring);
		struct sk_buff *skb;

		if (!ptr)
			break;

		if (veth_is_xdp_frame(ptr)) {
			skb = veth_xdp_rcv_one(rq, veth_ptr_to_xdp(ptr),
					       xdp_xmit);
		} else {
			skb = veth_xdp_rcv_skb(rq, ptr, xdp_xmit);
		}

		if (skb)
			napi_gro_receive(&rq->xdp_napi, skb);

		done++;
	}

	return done;
}