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
struct sock {int dummy; } ;
struct sk_buff {unsigned int len; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int BPF_CGROUP_RUN_PROG_INET_EGRESS (struct sock*,struct sk_buff*) ; 
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int IPSKB_FRAG_PMTU ; 
 int ip_finish_output2 (struct net*,struct sock*,struct sk_buff*) ; 
 int ip_finish_output_gso (struct net*,struct sock*,struct sk_buff*,unsigned int) ; 
 int ip_fragment (struct net*,struct sock*,struct sk_buff*,unsigned int,int (*) (struct net*,struct sock*,struct sk_buff*)) ; 
 unsigned int ip_skb_dst_mtu (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 

__attribute__((used)) static int ip_finish_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	unsigned int mtu;
	int ret;

	ret = BPF_CGROUP_RUN_PROG_INET_EGRESS(sk, skb);
	if (ret) {
		kfree_skb(skb);
		return ret;
	}

#if defined(CONFIG_NETFILTER) && defined(CONFIG_XFRM)
	/* Policy lookup after SNAT yielded a new policy */
	if (skb_dst(skb)->xfrm) {
		IPCB(skb)->flags |= IPSKB_REROUTED;
		return dst_output(net, sk, skb);
	}
#endif
	mtu = ip_skb_dst_mtu(sk, skb);
	if (skb_is_gso(skb))
		return ip_finish_output_gso(net, sk, skb, mtu);

	if (skb->len > mtu || (IPCB(skb)->flags & IPSKB_FRAG_PMTU))
		return ip_fragment(net, sk, skb, mtu, ip_finish_output2);

	return ip_finish_output2(net, sk, skb);
}