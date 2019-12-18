#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct net {int dummy; } ;
struct TYPE_7__ {scalar_t__ frag_max_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {scalar_t__ xfrm; } ;

/* Variables and functions */
 TYPE_4__* IP6CB (struct sk_buff*) ; 
 TYPE_3__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSKB_REROUTED ; 
 scalar_t__ dst_allfrag (TYPE_1__*) ; 
 int dst_output (struct net*,struct sock*,struct sk_buff*) ; 
 int ip6_finish_output2 (struct net*,struct sock*,struct sk_buff*) ; 
 int ip6_fragment (struct net*,struct sock*,struct sk_buff*,int (*) (struct net*,struct sock*,struct sk_buff*)) ; 
 scalar_t__ ip6_skb_dst_mtu (struct sk_buff*) ; 
 TYPE_1__* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 

__attribute__((used)) static int __ip6_finish_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
#if defined(CONFIG_NETFILTER) && defined(CONFIG_XFRM)
	/* Policy lookup after SNAT yielded a new policy */
	if (skb_dst(skb)->xfrm) {
		IPCB(skb)->flags |= IPSKB_REROUTED;
		return dst_output(net, sk, skb);
	}
#endif

	if ((skb->len > ip6_skb_dst_mtu(skb) && !skb_is_gso(skb)) ||
	    dst_allfrag(skb_dst(skb)) ||
	    (IP6CB(skb)->frag_max_size && skb->len > IP6CB(skb)->frag_max_size))
		return ip6_fragment(net, sk, skb, ip6_finish_output2);
	else
		return ip6_finish_output2(net, sk, skb);
}