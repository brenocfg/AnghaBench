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
struct rtable {int /*<<< orphan*/  dst; scalar_t__ rt_iif; } ;
struct net {int /*<<< orphan*/  loopback_dev; } ;

/* Variables and functions */
 int BPF_CGROUP_RUN_PROG_INET_EGRESS (struct sock*,struct sk_buff*) ; 
#define  NET_XMIT_CN 129 
#define  NET_XMIT_SUCCESS 128 
 int dev_loopback_xmit (struct net*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rtable* rt_dst_clone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_rtable (struct sk_buff*) ; 

__attribute__((used)) static int ip_mc_finish_output(struct net *net, struct sock *sk,
			       struct sk_buff *skb)
{
	struct rtable *new_rt;
	bool do_cn = false;
	int ret, err;

	ret = BPF_CGROUP_RUN_PROG_INET_EGRESS(sk, skb);
	switch (ret) {
	case NET_XMIT_CN:
		do_cn = true;
		/* fall through */
	case NET_XMIT_SUCCESS:
		break;
	default:
		kfree_skb(skb);
		return ret;
	}

	/* Reset rt_iif so that inet_iif() will return skb->skb_iif. Setting
	 * this to non-zero causes ipi_ifindex in in_pktinfo to be overwritten,
	 * see ipv4_pktinfo_prepare().
	 */
	new_rt = rt_dst_clone(net->loopback_dev, skb_rtable(skb));
	if (new_rt) {
		new_rt->rt_iif = 0;
		skb_dst_drop(skb);
		skb_dst_set(skb, &new_rt->dst);
	}

	err = dev_loopback_xmit(net, sk, skb);
	return (do_cn && err) ? ret : err;
}