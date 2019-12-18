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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_ADD_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTFORWDATAGRAMS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTOCTETS ; 
 int dst_output (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_dst_idev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 

__attribute__((used)) static inline int ip6mr_forward2_finish(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
		      IPSTATS_MIB_OUTFORWDATAGRAMS);
	IP6_ADD_STATS(net, ip6_dst_idev(skb_dst(skb)),
		      IPSTATS_MIB_OUTOCTETS, skb->len);
	return dst_output(net, sk, skb);
}