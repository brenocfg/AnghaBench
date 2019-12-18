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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int BPF_CGROUP_RUN_PROG_INET_EGRESS (struct sock*,struct sk_buff*) ; 
#define  NET_XMIT_CN 129 
#define  NET_XMIT_SUCCESS 128 
 int __ip6_finish_output (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static int ip6_finish_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	int ret;

	ret = BPF_CGROUP_RUN_PROG_INET_EGRESS(sk, skb);
	switch (ret) {
	case NET_XMIT_SUCCESS:
		return __ip6_finish_output(net, sk, skb);
	case NET_XMIT_CN:
		return __ip6_finish_output(net, sk, skb) ? : ret;
	default:
		kfree_skb(skb);
		return ret;
	}
}