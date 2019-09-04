#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nft_table {scalar_t__* name; } ;
struct nft_chain {int /*<<< orphan*/  use; scalar_t__* name; int /*<<< orphan*/  handle; } ;
struct nf_hook_ops {int /*<<< orphan*/  priority; int /*<<< orphan*/  hooknum; } ;
struct nft_base_chain {int /*<<< orphan*/  stats; TYPE_2__* type; int /*<<< orphan*/  policy; scalar_t__* dev_name; struct nf_hook_ops ops; } ;
struct nfgenmsg {int nfgen_family; int /*<<< orphan*/  res_id; int /*<<< orphan*/  version; } ;
struct TYPE_3__ {int base_seq; } ;
struct net {TYPE_1__ nft; } ;
struct TYPE_4__ {scalar_t__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int /*<<< orphan*/  NFNL_SUBSYS_NFTABLES ; 
 int /*<<< orphan*/  NFTA_CHAIN_HANDLE ; 
 int /*<<< orphan*/  NFTA_CHAIN_HOOK ; 
 int /*<<< orphan*/  NFTA_CHAIN_NAME ; 
 int /*<<< orphan*/  NFTA_CHAIN_PAD ; 
 int /*<<< orphan*/  NFTA_CHAIN_POLICY ; 
 int /*<<< orphan*/  NFTA_CHAIN_TABLE ; 
 int /*<<< orphan*/  NFTA_CHAIN_TYPE ; 
 int /*<<< orphan*/  NFTA_CHAIN_USE ; 
 int /*<<< orphan*/  NFTA_HOOK_DEV ; 
 int /*<<< orphan*/  NFTA_HOOK_HOOKNUM ; 
 int /*<<< orphan*/  NFTA_HOOK_PRIORITY ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int nfnl_msg_type (int /*<<< orphan*/ ,int) ; 
 struct nft_base_chain* nft_base_chain (struct nft_chain const*) ; 
 scalar_t__ nft_dump_stats (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nft_is_base_chain (struct nft_chain const*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,struct nlmsghdr*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nf_tables_fill_chain_info(struct sk_buff *skb, struct net *net,
				     u32 portid, u32 seq, int event, u32 flags,
				     int family, const struct nft_table *table,
				     const struct nft_chain *chain)
{
	struct nlmsghdr *nlh;
	struct nfgenmsg *nfmsg;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nlmsg_put(skb, portid, seq, event, sizeof(struct nfgenmsg), flags);
	if (nlh == NULL)
		goto nla_put_failure;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family	= family;
	nfmsg->version		= NFNETLINK_V0;
	nfmsg->res_id		= htons(net->nft.base_seq & 0xffff);

	if (nla_put_string(skb, NFTA_CHAIN_TABLE, table->name))
		goto nla_put_failure;
	if (nla_put_be64(skb, NFTA_CHAIN_HANDLE, cpu_to_be64(chain->handle),
			 NFTA_CHAIN_PAD))
		goto nla_put_failure;
	if (nla_put_string(skb, NFTA_CHAIN_NAME, chain->name))
		goto nla_put_failure;

	if (nft_is_base_chain(chain)) {
		const struct nft_base_chain *basechain = nft_base_chain(chain);
		const struct nf_hook_ops *ops = &basechain->ops;
		struct nlattr *nest;

		nest = nla_nest_start(skb, NFTA_CHAIN_HOOK);
		if (nest == NULL)
			goto nla_put_failure;
		if (nla_put_be32(skb, NFTA_HOOK_HOOKNUM, htonl(ops->hooknum)))
			goto nla_put_failure;
		if (nla_put_be32(skb, NFTA_HOOK_PRIORITY, htonl(ops->priority)))
			goto nla_put_failure;
		if (basechain->dev_name[0] &&
		    nla_put_string(skb, NFTA_HOOK_DEV, basechain->dev_name))
			goto nla_put_failure;
		nla_nest_end(skb, nest);

		if (nla_put_be32(skb, NFTA_CHAIN_POLICY,
				 htonl(basechain->policy)))
			goto nla_put_failure;

		if (nla_put_string(skb, NFTA_CHAIN_TYPE, basechain->type->name))
			goto nla_put_failure;

		if (rcu_access_pointer(basechain->stats) &&
		    nft_dump_stats(skb, rcu_dereference(basechain->stats)))
			goto nla_put_failure;
	}

	if (nla_put_be32(skb, NFTA_CHAIN_USE, htonl(chain->use)))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	return -1;
}