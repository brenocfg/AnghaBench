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
struct sk_buff {int dummy; } ;
struct nf_acct {int dummy; } ;
struct net {int /*<<< orphan*/  nfnl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NFNLGRP_ACCT_QUOTA ; 
 int /*<<< orphan*/  NFNL_MSG_ACCT_OVERQUOTA ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netlink_broadcast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfnl_acct_fill_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nf_acct*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfnl_overquota_report(struct net *net, struct nf_acct *nfacct)
{
	int ret;
	struct sk_buff *skb;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (skb == NULL)
		return;

	ret = nfnl_acct_fill_info(skb, 0, 0, NFNL_MSG_ACCT_OVERQUOTA, 0,
				  nfacct);
	if (ret <= 0) {
		kfree_skb(skb);
		return;
	}
	netlink_broadcast(net->nfnl, skb, 0, NFNLGRP_ACCT_QUOTA,
			  GFP_ATOMIC);
}