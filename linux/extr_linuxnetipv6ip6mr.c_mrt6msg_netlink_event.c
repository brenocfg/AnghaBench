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
struct sk_buff {int len; } ;
struct rtgenmsg {int /*<<< orphan*/  rtgen_family; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct mrt6msg {int /*<<< orphan*/  im6_dst; int /*<<< orphan*/  im6_src; int /*<<< orphan*/  im6_mif; int /*<<< orphan*/  im6_msgtype; } ;
struct mr_table {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IP6MRA_CREPORT_DST_ADDR ; 
 int /*<<< orphan*/  IP6MRA_CREPORT_MIF_ID ; 
 int /*<<< orphan*/  IP6MRA_CREPORT_MSGTYPE ; 
 int /*<<< orphan*/  IP6MRA_CREPORT_PKT ; 
 int /*<<< orphan*/  IP6MRA_CREPORT_SRC_ADDR ; 
 int /*<<< orphan*/  RTM_NEWCACHEREPORT ; 
 int /*<<< orphan*/  RTNLGRP_IPV6_MROUTE_R ; 
 int /*<<< orphan*/  RTNL_FAMILY_IP6MR ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mrt6msg_netlink_msgsize (int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct rtgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct net* read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_notify (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_set_sk_err (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static void mrt6msg_netlink_event(struct mr_table *mrt, struct sk_buff *pkt)
{
	struct net *net = read_pnet(&mrt->net);
	struct nlmsghdr *nlh;
	struct rtgenmsg *rtgenm;
	struct mrt6msg *msg;
	struct sk_buff *skb;
	struct nlattr *nla;
	int payloadlen;

	payloadlen = pkt->len - sizeof(struct mrt6msg);
	msg = (struct mrt6msg *)skb_transport_header(pkt);

	skb = nlmsg_new(mrt6msg_netlink_msgsize(payloadlen), GFP_ATOMIC);
	if (!skb)
		goto errout;

	nlh = nlmsg_put(skb, 0, 0, RTM_NEWCACHEREPORT,
			sizeof(struct rtgenmsg), 0);
	if (!nlh)
		goto errout;
	rtgenm = nlmsg_data(nlh);
	rtgenm->rtgen_family = RTNL_FAMILY_IP6MR;
	if (nla_put_u8(skb, IP6MRA_CREPORT_MSGTYPE, msg->im6_msgtype) ||
	    nla_put_u32(skb, IP6MRA_CREPORT_MIF_ID, msg->im6_mif) ||
	    nla_put_in6_addr(skb, IP6MRA_CREPORT_SRC_ADDR,
			     &msg->im6_src) ||
	    nla_put_in6_addr(skb, IP6MRA_CREPORT_DST_ADDR,
			     &msg->im6_dst))
		goto nla_put_failure;

	nla = nla_reserve(skb, IP6MRA_CREPORT_PKT, payloadlen);
	if (!nla || skb_copy_bits(pkt, sizeof(struct mrt6msg),
				  nla_data(nla), payloadlen))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);

	rtnl_notify(skb, net, 0, RTNLGRP_IPV6_MROUTE_R, NULL, GFP_ATOMIC);
	return;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
errout:
	kfree_skb(skb);
	rtnl_set_sk_err(net, RTNLGRP_IPV6_MROUTE_R, -ENOBUFS);
}