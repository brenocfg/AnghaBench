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
typedef  size_t u8 ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_3__ {int (* gro_complete ) (struct sk_buff*,int) ;} ;
struct net_offload {TYPE_1__ callbacks; } ;
struct iphdr {int /*<<< orphan*/  version; } ;
struct guehdr {int version; size_t proto_ctype; int hlen; } ;
struct TYPE_4__ {scalar_t__ is_ipv6; } ;

/* Variables and functions */
 int ENOENT ; 
 size_t IPPROTO_IPIP ; 
 size_t IPPROTO_IPV6 ; 
 TYPE_2__* NAPI_GRO_CB (struct sk_buff*) ; 
 scalar_t__ WARN_ON (int) ; 
 struct net_offload** inet6_offloads ; 
 struct net_offload** inet_offloads ; 
 struct net_offload* rcu_dereference (struct net_offload const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_set_inner_mac_header (struct sk_buff*,int) ; 
 int stub1 (struct sk_buff*,int) ; 

__attribute__((used)) static int gue_gro_complete(struct sock *sk, struct sk_buff *skb, int nhoff)
{
	const struct net_offload **offloads;
	struct guehdr *guehdr = (struct guehdr *)(skb->data + nhoff);
	const struct net_offload *ops;
	unsigned int guehlen = 0;
	u8 proto;
	int err = -ENOENT;

	switch (guehdr->version) {
	case 0:
		proto = guehdr->proto_ctype;
		guehlen = sizeof(*guehdr) + (guehdr->hlen << 2);
		break;
	case 1:
		switch (((struct iphdr *)guehdr)->version) {
		case 4:
			proto = IPPROTO_IPIP;
			break;
		case 6:
			proto = IPPROTO_IPV6;
			break;
		default:
			return err;
		}
		break;
	default:
		return err;
	}

	rcu_read_lock();
	offloads = NAPI_GRO_CB(skb)->is_ipv6 ? inet6_offloads : inet_offloads;
	ops = rcu_dereference(offloads[proto]);
	if (WARN_ON(!ops || !ops->callbacks.gro_complete))
		goto out_unlock;

	err = ops->callbacks.gro_complete(skb, nhoff + guehlen);

	skb_set_inner_mac_header(skb, nhoff + guehlen);

out_unlock:
	rcu_read_unlock();
	return err;
}