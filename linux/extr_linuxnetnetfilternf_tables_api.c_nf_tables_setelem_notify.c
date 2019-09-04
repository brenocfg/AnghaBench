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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nft_set_elem {int dummy; } ;
struct nft_set {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  report; int /*<<< orphan*/  portid; struct net* net; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFNLGRP_NFTABLES ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nf_tables_fill_setelem_info (struct sk_buff*,struct nft_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nft_set const*,struct nft_set_elem const*) ; 
 int /*<<< orphan*/  nfnetlink_has_listeners (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_set_err (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_tables_setelem_notify(const struct nft_ctx *ctx,
				     const struct nft_set *set,
				     const struct nft_set_elem *elem,
				     int event, u16 flags)
{
	struct net *net = ctx->net;
	u32 portid = ctx->portid;
	struct sk_buff *skb;
	int err;

	if (!ctx->report && !nfnetlink_has_listeners(net, NFNLGRP_NFTABLES))
		return;

	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (skb == NULL)
		goto err;

	err = nf_tables_fill_setelem_info(skb, ctx, 0, portid, event, flags,
					  set, elem);
	if (err < 0) {
		kfree_skb(skb);
		goto err;
	}

	nfnetlink_send(skb, net, portid, NFNLGRP_NFTABLES, ctx->report,
		       GFP_KERNEL);
	return;
err:
	nfnetlink_set_err(net, portid, NFNLGRP_NFTABLES, -ENOBUFS);
}