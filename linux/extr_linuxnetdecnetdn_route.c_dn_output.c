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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct dst_entry {struct net_device* dev; } ;
struct dn_skb_cb {scalar_t__ hops; int /*<<< orphan*/  rt_flags; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct dn_route {int /*<<< orphan*/  rt_daddr; int /*<<< orphan*/  rt_saddr; int /*<<< orphan*/ * n; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_RT_F_IE ; 
 int /*<<< orphan*/  DN_RT_F_RQR ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NFPROTO_DECNET ; 
 int /*<<< orphan*/  NF_DN_LOCAL_OUT ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sock*,struct sk_buff*,int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_to_neigh_output ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static int dn_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);
	struct dn_route *rt = (struct dn_route *)dst;
	struct net_device *dev = dst->dev;
	struct dn_skb_cb *cb = DN_SKB_CB(skb);

	int err = -EINVAL;

	if (rt->n == NULL)
		goto error;

	skb->dev = dev;

	cb->src = rt->rt_saddr;
	cb->dst = rt->rt_daddr;

	/*
	 * Always set the Intra-Ethernet bit on all outgoing packets
	 * originated on this node. Only valid flag from upper layers
	 * is return-to-sender-requested. Set hop count to 0 too.
	 */
	cb->rt_flags &= ~DN_RT_F_RQR;
	cb->rt_flags |= DN_RT_F_IE;
	cb->hops = 0;

	return NF_HOOK(NFPROTO_DECNET, NF_DN_LOCAL_OUT,
		       &init_net, sk, skb, NULL, dev,
		       dn_to_neigh_output);

error:
	net_dbg_ratelimited("dn_output: This should not happen\n");

	kfree_skb(skb);

	return err;
}