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
struct sk_buff {int dummy; } ;
struct nft_set {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  net; int /*<<< orphan*/  report; int /*<<< orphan*/  portid; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  NFNLGRP_NFTABLES ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nf_tables_fill_set (struct sk_buff*,struct nft_ctx const*,struct nft_set const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_has_listeners (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_set_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_tables_set_notify(const struct nft_ctx *ctx,
				 const struct nft_set *set, int event,
			         gfp_t gfp_flags)
{
	struct sk_buff *skb;
	u32 portid = ctx->portid;
	int err;

	if (!ctx->report &&
	    !nfnetlink_has_listeners(ctx->net, NFNLGRP_NFTABLES))
		return;

	skb = nlmsg_new(NLMSG_GOODSIZE, gfp_flags);
	if (skb == NULL)
		goto err;

	err = nf_tables_fill_set(skb, ctx, set, event, 0);
	if (err < 0) {
		kfree_skb(skb);
		goto err;
	}

	nfnetlink_send(skb, ctx->net, portid, NFNLGRP_NFTABLES, ctx->report,
		       gfp_flags);
	return;
err:
	nfnetlink_set_err(ctx->net, portid, NFNLGRP_NFTABLES, -ENOBUFS);
}