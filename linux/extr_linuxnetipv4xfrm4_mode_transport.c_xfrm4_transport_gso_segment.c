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
struct TYPE_4__ {scalar_t__ header_len; } ;
struct xfrm_state {TYPE_2__ props; } ;
struct xfrm_offload {size_t proto; } ;
struct sk_buff {int /*<<< orphan*/  transport_header; } ;
struct TYPE_3__ {struct sk_buff* (* gso_segment ) (struct sk_buff*,int /*<<< orphan*/ ) ;} ;
struct net_offload {TYPE_1__ callbacks; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_offloads ; 
 scalar_t__ likely (int) ; 
 struct net_offload* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *xfrm4_transport_gso_segment(struct xfrm_state *x,
						   struct sk_buff *skb,
						   netdev_features_t features)
{
	const struct net_offload *ops;
	struct sk_buff *segs = ERR_PTR(-EINVAL);
	struct xfrm_offload *xo = xfrm_offload(skb);

	skb->transport_header += x->props.header_len;
	ops = rcu_dereference(inet_offloads[xo->proto]);
	if (likely(ops && ops->callbacks.gso_segment))
		segs = ops->callbacks.gso_segment(skb, features);

	return segs;
}