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
struct nft_set {int /*<<< orphan*/  nelems; scalar_t__ use; } ;
struct nft_ctx {int /*<<< orphan*/  table; } ;
struct nfgenmsg {scalar_t__ nfgen_family; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct nft_set*) ; 
 scalar_t__ NFPROTO_UNSPEC ; 
 size_t NFTA_SET_HANDLE ; 
 size_t NFTA_SET_NAME ; 
 size_t NFTA_SET_TABLE ; 
 int NLM_F_NONREC ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (struct netlink_ext_ack*,struct nlattr const*) ; 
 int PTR_ERR (struct nft_set*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int nft_ctx_init_from_setattr (struct nft_ctx*,struct net*,struct sk_buff*,struct nlmsghdr const*,struct nlattr const* const*,struct netlink_ext_ack*,int /*<<< orphan*/ ) ; 
 int nft_delset (struct nft_ctx*,struct nft_set*) ; 
 int /*<<< orphan*/  nft_genmask_next (struct net*) ; 
 struct nft_set* nft_set_lookup (int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ) ; 
 struct nft_set* nft_set_lookup_byhandle (int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 

__attribute__((used)) static int nf_tables_delset(struct net *net, struct sock *nlsk,
			    struct sk_buff *skb, const struct nlmsghdr *nlh,
			    const struct nlattr * const nla[],
			    struct netlink_ext_ack *extack)
{
	const struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	u8 genmask = nft_genmask_next(net);
	const struct nlattr *attr;
	struct nft_set *set;
	struct nft_ctx ctx;
	int err;

	if (nfmsg->nfgen_family == NFPROTO_UNSPEC)
		return -EAFNOSUPPORT;
	if (nla[NFTA_SET_TABLE] == NULL)
		return -EINVAL;

	err = nft_ctx_init_from_setattr(&ctx, net, skb, nlh, nla, extack,
					genmask);
	if (err < 0)
		return err;

	if (nla[NFTA_SET_HANDLE]) {
		attr = nla[NFTA_SET_HANDLE];
		set = nft_set_lookup_byhandle(ctx.table, attr, genmask);
	} else {
		attr = nla[NFTA_SET_NAME];
		set = nft_set_lookup(ctx.table, attr, genmask);
	}

	if (IS_ERR(set)) {
		NL_SET_BAD_ATTR(extack, attr);
		return PTR_ERR(set);
	}
	if (set->use ||
	    (nlh->nlmsg_flags & NLM_F_NONREC && atomic_read(&set->nelems) > 0)) {
		NL_SET_BAD_ATTR(extack, attr);
		return -EBUSY;
	}

	return nft_delset(&ctx, set);
}