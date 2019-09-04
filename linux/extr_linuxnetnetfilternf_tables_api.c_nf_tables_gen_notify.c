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
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NFNLGRP_NFTABLES ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nf_tables_fill_gen_info (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_has_listeners (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_set_err (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nlmsg_report (struct nlmsghdr*) ; 

__attribute__((used)) static void nf_tables_gen_notify(struct net *net, struct sk_buff *skb,
				 int event)
{
	struct nlmsghdr *nlh = nlmsg_hdr(skb);
	struct sk_buff *skb2;
	int err;

	if (nlmsg_report(nlh) &&
	    !nfnetlink_has_listeners(net, NFNLGRP_NFTABLES))
		return;

	skb2 = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (skb2 == NULL)
		goto err;

	err = nf_tables_fill_gen_info(skb2, net, NETLINK_CB(skb).portid,
				      nlh->nlmsg_seq);
	if (err < 0) {
		kfree_skb(skb2);
		goto err;
	}

	nfnetlink_send(skb2, net, NETLINK_CB(skb).portid, NFNLGRP_NFTABLES,
		       nlmsg_report(nlh), GFP_KERNEL);
	return;
err:
	nfnetlink_set_err(net, NETLINK_CB(skb).portid, NFNLGRP_NFTABLES,
			  -ENOBUFS);
}