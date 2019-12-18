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
struct nft_table {int dummy; } ;
struct nft_object {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  NFNLGRP_NFTABLES ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nf_tables_fill_obj_info (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,struct nft_table const*,struct nft_object*,int) ; 
 int /*<<< orphan*/  nfnetlink_has_listeners (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_send (struct sk_buff*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnetlink_set_err (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nft_obj_notify(struct net *net, const struct nft_table *table,
		    struct nft_object *obj, u32 portid, u32 seq, int event,
		    int family, int report, gfp_t gfp)
{
	struct sk_buff *skb;
	int err;

	if (!report &&
	    !nfnetlink_has_listeners(net, NFNLGRP_NFTABLES))
		return;

	skb = nlmsg_new(NLMSG_GOODSIZE, gfp);
	if (skb == NULL)
		goto err;

	err = nf_tables_fill_obj_info(skb, net, portid, seq, event, 0, family,
				      table, obj, false);
	if (err < 0) {
		kfree_skb(skb);
		goto err;
	}

	nfnetlink_send(skb, net, portid, NFNLGRP_NFTABLES, report, gfp);
	return;
err:
	nfnetlink_set_err(net, portid, NFNLGRP_NFTABLES, -ENOBUFS);
}