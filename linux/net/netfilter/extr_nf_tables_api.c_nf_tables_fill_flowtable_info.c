#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nft_flowtable {int ops_len; TYPE_3__* ops; int /*<<< orphan*/  priority; int /*<<< orphan*/  hooknum; int /*<<< orphan*/  handle; int /*<<< orphan*/  use; int /*<<< orphan*/  name; TYPE_2__* table; } ;
struct nfgenmsg {int nfgen_family; int /*<<< orphan*/  res_id; int /*<<< orphan*/  version; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int base_seq; } ;
struct net {TYPE_1__ nft; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int /*<<< orphan*/  NFNL_SUBSYS_NFTABLES ; 
 int /*<<< orphan*/  NFTA_DEVICE_NAME ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_HANDLE ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_HOOK ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_HOOK_DEVS ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_HOOK_NUM ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_HOOK_PRIORITY ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_NAME ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_PAD ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_TABLE ; 
 int /*<<< orphan*/  NFTA_FLOWTABLE_USE ; 
 struct net_device* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int nfnl_msg_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,struct nlmsghdr*) ; 

__attribute__((used)) static int nf_tables_fill_flowtable_info(struct sk_buff *skb, struct net *net,
					 u32 portid, u32 seq, int event,
					 u32 flags, int family,
					 struct nft_flowtable *flowtable)
{
	struct nlattr *nest, *nest_devs;
	struct nfgenmsg *nfmsg;
	struct nlmsghdr *nlh;
	int i;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nlmsg_put(skb, portid, seq, event, sizeof(struct nfgenmsg), flags);
	if (nlh == NULL)
		goto nla_put_failure;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family	= family;
	nfmsg->version		= NFNETLINK_V0;
	nfmsg->res_id		= htons(net->nft.base_seq & 0xffff);

	if (nla_put_string(skb, NFTA_FLOWTABLE_TABLE, flowtable->table->name) ||
	    nla_put_string(skb, NFTA_FLOWTABLE_NAME, flowtable->name) ||
	    nla_put_be32(skb, NFTA_FLOWTABLE_USE, htonl(flowtable->use)) ||
	    nla_put_be64(skb, NFTA_FLOWTABLE_HANDLE, cpu_to_be64(flowtable->handle),
			 NFTA_FLOWTABLE_PAD))
		goto nla_put_failure;

	nest = nla_nest_start_noflag(skb, NFTA_FLOWTABLE_HOOK);
	if (!nest)
		goto nla_put_failure;
	if (nla_put_be32(skb, NFTA_FLOWTABLE_HOOK_NUM, htonl(flowtable->hooknum)) ||
	    nla_put_be32(skb, NFTA_FLOWTABLE_HOOK_PRIORITY, htonl(flowtable->priority)))
		goto nla_put_failure;

	nest_devs = nla_nest_start_noflag(skb, NFTA_FLOWTABLE_HOOK_DEVS);
	if (!nest_devs)
		goto nla_put_failure;

	for (i = 0; i < flowtable->ops_len; i++) {
		const struct net_device *dev = READ_ONCE(flowtable->ops[i].dev);

		if (dev &&
		    nla_put_string(skb, NFTA_DEVICE_NAME, dev->name))
			goto nla_put_failure;
	}
	nla_nest_end(skb, nest_devs);
	nla_nest_end(skb, nest);

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	return -1;
}