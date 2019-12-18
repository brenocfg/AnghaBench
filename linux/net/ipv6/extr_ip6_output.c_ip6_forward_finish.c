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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ tstamp; scalar_t__ offload_l3_fwd_mark; int /*<<< orphan*/  len; } ;
struct net {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSTATS_MIB_OUTFORWDATAGRAMS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTOCTETS ; 
 int /*<<< orphan*/  __IP6_ADD_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int dst_output (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_dst_idev (struct dst_entry*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static inline int ip6_forward_finish(struct net *net, struct sock *sk,
				     struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);

	__IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTFORWDATAGRAMS);
	__IP6_ADD_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTOCTETS, skb->len);

#ifdef CONFIG_NET_SWITCHDEV
	if (skb->offload_l3_fwd_mark) {
		consume_skb(skb);
		return 0;
	}
#endif

	skb->tstamp = 0;
	return dst_output(net, sk, skb);
}