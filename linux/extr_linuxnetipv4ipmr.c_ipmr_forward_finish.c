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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net {int dummy; } ;
struct ip_options {int /*<<< orphan*/  optlen; } ;
struct TYPE_2__ {struct ip_options opt; } ;

/* Variables and functions */
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTFORWDATAGRAMS ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTOCTETS ; 
 int /*<<< orphan*/  IP_ADD_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int dst_output (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ip_forward_options (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ipmr_forward_finish(struct net *net, struct sock *sk,
				      struct sk_buff *skb)
{
	struct ip_options *opt = &(IPCB(skb)->opt);

	IP_INC_STATS(net, IPSTATS_MIB_OUTFORWDATAGRAMS);
	IP_ADD_STATS(net, IPSTATS_MIB_OUTOCTETS, skb->len);

	if (unlikely(opt->optlen))
		ip_forward_options(skb);

	return dst_output(net, sk, skb);
}