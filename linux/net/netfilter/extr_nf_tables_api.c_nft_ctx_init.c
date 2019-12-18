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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_seq; int /*<<< orphan*/  nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct nft_table {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  seq; int /*<<< orphan*/  flags; int /*<<< orphan*/  report; int /*<<< orphan*/  portid; struct nlattr const* const* nla; struct nft_chain* chain; struct nft_table* table; scalar_t__ level; int /*<<< orphan*/  family; struct net* net; } ;
struct nft_chain {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 TYPE_1__ NETLINK_CB (struct sk_buff const*) ; 
 int /*<<< orphan*/  nlmsg_report (struct nlmsghdr const*) ; 

__attribute__((used)) static void nft_ctx_init(struct nft_ctx *ctx,
			 struct net *net,
			 const struct sk_buff *skb,
			 const struct nlmsghdr *nlh,
			 u8 family,
			 struct nft_table *table,
			 struct nft_chain *chain,
			 const struct nlattr * const *nla)
{
	ctx->net	= net;
	ctx->family	= family;
	ctx->level	= 0;
	ctx->table	= table;
	ctx->chain	= chain;
	ctx->nla   	= nla;
	ctx->portid	= NETLINK_CB(skb).portid;
	ctx->report	= nlmsg_report(nlh);
	ctx->flags	= nlh->nlmsg_flags;
	ctx->seq	= nlh->nlmsg_seq;
}