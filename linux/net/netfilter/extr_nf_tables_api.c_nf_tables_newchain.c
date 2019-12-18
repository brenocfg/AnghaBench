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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct nft_table {int flags; } ;
struct nft_ctx {int dummy; } ;
struct nft_chain {int flags; } ;
struct nfgenmsg {int nfgen_family; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit_mutex; } ;
struct net {TYPE_1__ nft; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct nft_table*) ; 
 size_t NFTA_CHAIN_FLAGS ; 
 size_t NFTA_CHAIN_HANDLE ; 
 size_t NFTA_CHAIN_HOOK ; 
 size_t NFTA_CHAIN_NAME ; 
 size_t NFTA_CHAIN_POLICY ; 
 size_t NFTA_CHAIN_TABLE ; 
 int NFT_BASE_CHAIN ; 
#define  NF_ACCEPT 129 
#define  NF_DROP 128 
 int NLM_F_EXCL ; 
 int NLM_F_REPLACE ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (struct netlink_ext_ack*,struct nlattr const*) ; 
 int PTR_ERR (struct nft_table*) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int nf_tables_addchain (struct nft_ctx*,int,int,int,int) ; 
 int nf_tables_updchain (struct nft_ctx*,int,int,int) ; 
 struct nft_table* nft_chain_lookup (struct net*,struct nft_table*,struct nlattr const*,int) ; 
 struct nft_table* nft_chain_lookup_byhandle (struct nft_table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nft_ctx_init (struct nft_ctx*,struct net*,struct sk_buff*,struct nlmsghdr const*,int,struct nft_table*,struct nft_table*,struct nlattr const* const*) ; 
 int nft_genmask_next (struct net*) ; 
 int /*<<< orphan*/  nft_is_base_chain (struct nft_table*) ; 
 struct nft_table* nft_table_lookup (struct net*,struct nlattr const* const,int,int) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be64 (struct nlattr const* const) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_tables_newchain(struct net *net, struct sock *nlsk,
			      struct sk_buff *skb, const struct nlmsghdr *nlh,
			      const struct nlattr * const nla[],
			      struct netlink_ext_ack *extack)
{
	const struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u8 genmask = nft_genmask_next(net);
	int family = nfmsg->nfgen_family;
	const struct nlattr *attr;
	struct nft_table *table;
	struct nft_chain *chain;
	u8 policy = NF_ACCEPT;
	struct nft_ctx ctx;
	u64 handle = 0;
	u32 flags = 0;

	lockdep_assert_held(&net->nft.commit_mutex);

	table = nft_table_lookup(net, nla[NFTA_CHAIN_TABLE], family, genmask);
	if (IS_ERR(table)) {
		NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_TABLE]);
		return PTR_ERR(table);
	}

	chain = NULL;
	attr = nla[NFTA_CHAIN_NAME];

	if (nla[NFTA_CHAIN_HANDLE]) {
		handle = be64_to_cpu(nla_get_be64(nla[NFTA_CHAIN_HANDLE]));
		chain = nft_chain_lookup_byhandle(table, handle, genmask);
		if (IS_ERR(chain)) {
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_HANDLE]);
			return PTR_ERR(chain);
		}
		attr = nla[NFTA_CHAIN_HANDLE];
	} else {
		chain = nft_chain_lookup(net, table, attr, genmask);
		if (IS_ERR(chain)) {
			if (PTR_ERR(chain) != -ENOENT) {
				NL_SET_BAD_ATTR(extack, attr);
				return PTR_ERR(chain);
			}
			chain = NULL;
		}
	}

	if (nla[NFTA_CHAIN_POLICY]) {
		if (chain != NULL &&
		    !nft_is_base_chain(chain)) {
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_POLICY]);
			return -EOPNOTSUPP;
		}

		if (chain == NULL &&
		    nla[NFTA_CHAIN_HOOK] == NULL) {
			NL_SET_BAD_ATTR(extack, nla[NFTA_CHAIN_POLICY]);
			return -EOPNOTSUPP;
		}

		policy = ntohl(nla_get_be32(nla[NFTA_CHAIN_POLICY]));
		switch (policy) {
		case NF_DROP:
		case NF_ACCEPT:
			break;
		default:
			return -EINVAL;
		}
	}

	if (nla[NFTA_CHAIN_FLAGS])
		flags = ntohl(nla_get_be32(nla[NFTA_CHAIN_FLAGS]));
	else if (chain)
		flags = chain->flags;

	nft_ctx_init(&ctx, net, skb, nlh, family, table, chain, nla);

	if (chain != NULL) {
		if (nlh->nlmsg_flags & NLM_F_EXCL) {
			NL_SET_BAD_ATTR(extack, attr);
			return -EEXIST;
		}
		if (nlh->nlmsg_flags & NLM_F_REPLACE)
			return -EOPNOTSUPP;

		flags |= chain->flags & NFT_BASE_CHAIN;
		return nf_tables_updchain(&ctx, genmask, policy, flags);
	}

	return nf_tables_addchain(&ctx, family, genmask, policy, flags);
}