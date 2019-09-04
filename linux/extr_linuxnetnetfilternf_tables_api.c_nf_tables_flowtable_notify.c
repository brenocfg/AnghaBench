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
struct nft_flowtable {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  portid; int /*<<< orphan*/  net; scalar_t__ report; int /*<<< orphan*/  family; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFNLGRP_NFTABLES ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nf_tables_fill_flowtable_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nft_flowtable*) ; 
 int /*<<< orphan*/  nfnetlink_has_listeners (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_set_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_tables_flowtable_notify(struct nft_ctx *ctx,
				       struct nft_flowtable *flowtable,
				       int event)
{
	struct sk_buff *skb;
	int err;

	if (ctx->report &&
	    !nfnetlink_has_listeners(ctx->net, NFNLGRP_NFTABLES))
		return;

	skb = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (skb == NULL)
		goto err;

	err = nf_tables_fill_flowtable_info(skb, ctx->net, ctx->portid,
					    ctx->seq, event, 0,
					    ctx->family, flowtable);
	if (err < 0) {
		kfree_skb(skb);
		goto err;
	}

	nfnetlink_send(skb, ctx->net, ctx->portid, NFNLGRP_NFTABLES,
		       ctx->report, GFP_KERNEL);
	return;
err:
	nfnetlink_set_err(ctx->net, ctx->portid, NFNLGRP_NFTABLES, -ENOBUFS);
}