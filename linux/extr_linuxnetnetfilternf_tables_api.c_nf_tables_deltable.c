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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct nft_table {scalar_t__ use; } ;
struct nft_ctx {int family; struct nft_table* table; } ;
struct nfgenmsg {int nfgen_family; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int AF_UNSPEC ; 
 int EBUSY ; 
 scalar_t__ IS_ERR (struct nft_table*) ; 
 size_t NFTA_TABLE_HANDLE ; 
 size_t NFTA_TABLE_NAME ; 
 int NLM_F_NONREC ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (struct netlink_ext_ack*,struct nlattr const*) ; 
 int PTR_ERR (struct nft_table*) ; 
 int /*<<< orphan*/  nft_ctx_init (struct nft_ctx*,struct net*,struct sk_buff*,struct nlmsghdr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nlattr const* const*) ; 
 int nft_flush (struct nft_ctx*,int) ; 
 int nft_flush_table (struct nft_ctx*) ; 
 int /*<<< orphan*/  nft_genmask_next (struct net*) ; 
 struct nft_table* nft_table_lookup (struct net*,struct nlattr const*,int,int /*<<< orphan*/ ) ; 
 struct nft_table* nft_table_lookup_byhandle (struct net*,struct nlattr const*,int /*<<< orphan*/ ) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 

__attribute__((used)) static int nf_tables_deltable(struct net *net, struct sock *nlsk,
			      struct sk_buff *skb, const struct nlmsghdr *nlh,
			      const struct nlattr * const nla[],
			      struct netlink_ext_ack *extack)
{
	const struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u8 genmask = nft_genmask_next(net);
	int family = nfmsg->nfgen_family;
	const struct nlattr *attr;
	struct nft_table *table;
	struct nft_ctx ctx;

	nft_ctx_init(&ctx, net, skb, nlh, 0, NULL, NULL, nla);
	if (family == AF_UNSPEC ||
	    (!nla[NFTA_TABLE_NAME] && !nla[NFTA_TABLE_HANDLE]))
		return nft_flush(&ctx, family);

	if (nla[NFTA_TABLE_HANDLE]) {
		attr = nla[NFTA_TABLE_HANDLE];
		table = nft_table_lookup_byhandle(net, attr, genmask);
	} else {
		attr = nla[NFTA_TABLE_NAME];
		table = nft_table_lookup(net, attr, family, genmask);
	}

	if (IS_ERR(table)) {
		NL_SET_BAD_ATTR(extack, attr);
		return PTR_ERR(table);
	}

	if (nlh->nlmsg_flags & NLM_F_NONREC &&
	    table->use > 0)
		return -EBUSY;

	ctx.family = family;
	ctx.table = table;

	return nft_flush_table(&ctx);
}