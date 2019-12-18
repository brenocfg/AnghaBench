#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; } ;
struct rtgenmsg {int /*<<< orphan*/  rtgen_family; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct mr_table {int /*<<< orphan*/  net; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct igmpmsg {TYPE_2__ im_dst; TYPE_1__ im_src; int /*<<< orphan*/  im_vif; int /*<<< orphan*/  im_msgtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IPMRA_CREPORT_DST_ADDR ; 
 int /*<<< orphan*/  IPMRA_CREPORT_MSGTYPE ; 
 int /*<<< orphan*/  IPMRA_CREPORT_PKT ; 
 int /*<<< orphan*/  IPMRA_CREPORT_SRC_ADDR ; 
 int /*<<< orphan*/  IPMRA_CREPORT_VIF_ID ; 
 int /*<<< orphan*/  RTM_NEWCACHEREPORT ; 
 int /*<<< orphan*/  RTNLGRP_IPV4_MROUTE_R ; 
 int /*<<< orphan*/  RTNL_FAMILY_IPMR ; 
 int /*<<< orphan*/  igmpmsg_netlink_msgsize (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 scalar_t__ skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static void igmpmsg_netlink_event(struct mr_table *mrt, struct sk_buff *pkt)
{
	struct net *net = read_pnet(&mrt->net);
	struct nlmsghdr *nlh;
	struct rtgenmsg *rtgenm;
	struct igmpmsg *msg;
	struct sk_buff *skb;
	struct nlattr *nla;
	int payloadlen;

	payloadlen = pkt->len - sizeof(struct igmpmsg);
	msg = (struct igmpmsg *)skb_network_header(pkt);

	skb = nlmsg_new(igmpmsg_netlink_msgsize(payloadlen), GFP_ATOMIC);
	if (!skb)
		goto errout;

	nlh = nlmsg_put(skb, 0, 0, RTM_NEWCACHEREPORT,
			sizeof(struct rtgenmsg), 0);
	if (!nlh)
		goto errout;
	rtgenm = nlmsg_data(nlh);
	rtgenm->rtgen_family = RTNL_FAMILY_IPMR;
	if (nla_put_u8(skb, IPMRA_CREPORT_MSGTYPE, msg->im_msgtype) ||
	    nla_put_u32(skb, IPMRA_CREPORT_VIF_ID, msg->im_vif) ||
	    nla_put_in_addr(skb, IPMRA_CREPORT_SRC_ADDR,
			    msg->im_src.s_addr) ||
	    nla_put_in_addr(skb, IPMRA_CREPORT_DST_ADDR,
			    msg->im_dst.s_addr))
		goto nla_put_failure;

	nla = nla_reserve(skb, IPMRA_CREPORT_PKT, payloadlen);
	if (!nla || skb_copy_bits(pkt, sizeof(struct igmpmsg),
				  nla_data(nla), payloadlen))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);

	rtnl_notify(skb, net, 0, RTNLGRP_IPV4_MROUTE_R, NULL, GFP_ATOMIC);
	return;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
errout:
	kfree_skb(skb);
	rtnl_set_sk_err(net, RTNLGRP_IPV4_MROUTE_R, -ENOBUFS);
}