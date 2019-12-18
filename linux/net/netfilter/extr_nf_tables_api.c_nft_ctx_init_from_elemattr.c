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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nft_table {int dummy; } ;
struct nft_ctx {int dummy; } ;
struct nfgenmsg {int nfgen_family; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nft_table*) ; 
 size_t NFTA_SET_ELEM_LIST_TABLE ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (struct netlink_ext_ack*,struct nlattr const* const) ; 
 int PTR_ERR (struct nft_table*) ; 
 int /*<<< orphan*/  nft_ctx_init (struct nft_ctx*,struct net*,struct sk_buff const*,struct nlmsghdr const*,int,struct nft_table*,int /*<<< orphan*/ *,struct nlattr const* const*) ; 
 struct nft_table* nft_table_lookup (struct net*,struct nlattr const* const,int,int /*<<< orphan*/ ) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 

__attribute__((used)) static int nft_ctx_init_from_elemattr(struct nft_ctx *ctx, struct net *net,
				      const struct sk_buff *skb,
				      const struct nlmsghdr *nlh,
				      const struct nlattr * const nla[],
				      struct netlink_ext_ack *extack,
				      u8 genmask)
{
	const struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	int family = nfmsg->nfgen_family;
	struct nft_table *table;

	table = nft_table_lookup(net, nla[NFTA_SET_ELEM_LIST_TABLE], family,
				 genmask);
	if (IS_ERR(table)) {
		NL_SET_BAD_ATTR(extack, nla[NFTA_SET_ELEM_LIST_TABLE]);
		return PTR_ERR(table);
	}

	nft_ctx_init(ctx, net, skb, nlh, family, table, NULL, nla);
	return 0;
}