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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_flags; } ;
struct nlattr {int dummy; } ;
struct nft_set {int dummy; } ;
struct nft_ctx {int /*<<< orphan*/  table; } ;
struct nfgenmsg {scalar_t__ nfgen_family; } ;
struct netlink_ext_ack {int dummy; } ;
struct netlink_dump_control {int /*<<< orphan*/  module; struct nft_ctx* data; int /*<<< orphan*/  done; int /*<<< orphan*/  dump; int /*<<< orphan*/  start; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct nft_set const*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 scalar_t__ NFPROTO_UNSPEC ; 
 size_t NFTA_SET_NAME ; 
 size_t NFTA_SET_TABLE ; 
 int /*<<< orphan*/  NFT_MSG_NEWSET ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int NLM_F_DUMP ; 
 int PTR_ERR (struct nft_set const*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_tables_dump_sets ; 
 int /*<<< orphan*/  nf_tables_dump_sets_done ; 
 int /*<<< orphan*/  nf_tables_dump_sets_start ; 
 int nf_tables_fill_set (struct sk_buff*,struct nft_ctx*,struct nft_set const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nft_ctx_init_from_setattr (struct nft_ctx*,struct net*,struct sk_buff*,struct nlmsghdr const*,struct nlattr const* const*,struct netlink_ext_ack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nft_genmask_cur (struct net*) ; 
 int nft_netlink_dump_start_rcu (struct sock*,struct sk_buff*,struct nlmsghdr const*,struct netlink_dump_control*) ; 
 struct nft_set* nft_set_lookup (int /*<<< orphan*/ ,struct nlattr const* const,int /*<<< orphan*/ ) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int nlmsg_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_tables_getset(struct net *net, struct sock *nlsk,
			    struct sk_buff *skb, const struct nlmsghdr *nlh,
			    const struct nlattr * const nla[],
			    struct netlink_ext_ack *extack)
{
	u8 genmask = nft_genmask_cur(net);
	const struct nft_set *set;
	struct nft_ctx ctx;
	struct sk_buff *skb2;
	const struct nfgenmsg *nfmsg = nlmsg_data(nlh);
	int err;

	/* Verify existence before starting dump */
	err = nft_ctx_init_from_setattr(&ctx, net, skb, nlh, nla, extack,
					genmask);
	if (err < 0)
		return err;

	if (nlh->nlmsg_flags & NLM_F_DUMP) {
		struct netlink_dump_control c = {
			.start = nf_tables_dump_sets_start,
			.dump = nf_tables_dump_sets,
			.done = nf_tables_dump_sets_done,
			.data = &ctx,
			.module = THIS_MODULE,
		};

		return nft_netlink_dump_start_rcu(nlsk, skb, nlh, &c);
	}

	/* Only accept unspec with dump */
	if (nfmsg->nfgen_family == NFPROTO_UNSPEC)
		return -EAFNOSUPPORT;
	if (!nla[NFTA_SET_TABLE])
		return -EINVAL;

	set = nft_set_lookup(ctx.table, nla[NFTA_SET_NAME], genmask);
	if (IS_ERR(set))
		return PTR_ERR(set);

	skb2 = alloc_skb(NLMSG_GOODSIZE, GFP_ATOMIC);
	if (skb2 == NULL)
		return -ENOMEM;

	err = nf_tables_fill_set(skb2, &ctx, set, NFT_MSG_NEWSET, 0);
	if (err < 0)
		goto err;

	return nlmsg_unicast(nlsk, skb2, NETLINK_CB(skb).portid);

err:
	kfree_skb(skb2);
	return err;
}