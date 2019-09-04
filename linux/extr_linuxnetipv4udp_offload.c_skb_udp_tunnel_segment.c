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
struct sk_buff {int inner_protocol_type; size_t inner_ipproto; int /*<<< orphan*/  inner_protocol; int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {struct sk_buff* (* gso_segment ) (struct sk_buff*,int /*<<< orphan*/ ) ;} ;
struct net_offload {TYPE_1__ callbacks; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  ENCAP_TYPE_ETHER 129 
#define  ENCAP_TYPE_IPPROTO 128 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_udp_tunnel_segment (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff* (*) (struct sk_buff*,int /*<<< orphan*/ ),int /*<<< orphan*/ ,int) ; 
 struct net_offload** inet6_offloads ; 
 struct net_offload** inet_offloads ; 
 struct net_offload* rcu_dereference (struct net_offload const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sk_buff* skb_mac_gso_segment (struct sk_buff*,int /*<<< orphan*/ ) ; 

struct sk_buff *skb_udp_tunnel_segment(struct sk_buff *skb,
				       netdev_features_t features,
				       bool is_ipv6)
{
	__be16 protocol = skb->protocol;
	const struct net_offload **offloads;
	const struct net_offload *ops;
	struct sk_buff *segs = ERR_PTR(-EINVAL);
	struct sk_buff *(*gso_inner_segment)(struct sk_buff *skb,
					     netdev_features_t features);

	rcu_read_lock();

	switch (skb->inner_protocol_type) {
	case ENCAP_TYPE_ETHER:
		protocol = skb->inner_protocol;
		gso_inner_segment = skb_mac_gso_segment;
		break;
	case ENCAP_TYPE_IPPROTO:
		offloads = is_ipv6 ? inet6_offloads : inet_offloads;
		ops = rcu_dereference(offloads[skb->inner_ipproto]);
		if (!ops || !ops->callbacks.gso_segment)
			goto out_unlock;
		gso_inner_segment = ops->callbacks.gso_segment;
		break;
	default:
		goto out_unlock;
	}

	segs = __skb_udp_tunnel_segment(skb, features, gso_inner_segment,
					protocol, is_ipv6);

out_unlock:
	rcu_read_unlock();

	return segs;
}