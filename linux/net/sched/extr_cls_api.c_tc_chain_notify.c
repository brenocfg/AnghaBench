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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct tcf_chain {int /*<<< orphan*/  index; int /*<<< orphan*/  tmplt_priv; int /*<<< orphan*/  tmplt_ops; struct tcf_block* block; } ;
struct tcf_block {struct net* net; } ;
struct sk_buff {int dummy; } ;
struct net {int /*<<< orphan*/  rtnl; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int NLM_F_ECHO ; 
 int /*<<< orphan*/  RTNLGRP_TC ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tc_chain_fill_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct sk_buff*,struct tcf_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int tc_chain_notify(struct tcf_chain *chain, struct sk_buff *oskb,
			   u32 seq, u16 flags, int event, bool unicast)
{
	u32 portid = oskb ? NETLINK_CB(oskb).portid : 0;
	struct tcf_block *block = chain->block;
	struct net *net = block->net;
	struct sk_buff *skb;
	int err = 0;

	skb = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!skb)
		return -ENOBUFS;

	if (tc_chain_fill_node(chain->tmplt_ops, chain->tmplt_priv,
			       chain->index, net, skb, block, portid,
			       seq, flags, event) <= 0) {
		kfree_skb(skb);
		return -EINVAL;
	}

	if (unicast)
		err = netlink_unicast(net->rtnl, skb, portid, MSG_DONTWAIT);
	else
		err = rtnetlink_send(skb, net, portid, RTNLGRP_TC,
				     flags & NLM_F_ECHO);

	if (err > 0)
		err = 0;
	return err;
}