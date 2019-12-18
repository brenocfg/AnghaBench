#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nft_table {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct nft_object {int /*<<< orphan*/  handle; int /*<<< orphan*/  use; TYPE_4__* ops; TYPE_2__ key; } ;
struct nfgenmsg {int nfgen_family; int /*<<< orphan*/  res_id; int /*<<< orphan*/  version; } ;
struct TYPE_5__ {int base_seq; } ;
struct net {TYPE_1__ nft; } ;
struct TYPE_8__ {TYPE_3__* type; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFNETLINK_V0 ; 
 int /*<<< orphan*/  NFNL_SUBSYS_NFTABLES ; 
 int /*<<< orphan*/  NFTA_OBJ_DATA ; 
 int /*<<< orphan*/  NFTA_OBJ_HANDLE ; 
 int /*<<< orphan*/  NFTA_OBJ_NAME ; 
 int /*<<< orphan*/  NFTA_OBJ_PAD ; 
 int /*<<< orphan*/  NFTA_OBJ_TABLE ; 
 int /*<<< orphan*/  NFTA_OBJ_TYPE ; 
 int /*<<< orphan*/  NFTA_OBJ_USE ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int nfnl_msg_type (int /*<<< orphan*/ ,int) ; 
 scalar_t__ nft_object_dump (struct sk_buff*,int /*<<< orphan*/ ,struct nft_object*,int) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfgenmsg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,struct nlmsghdr*) ; 

__attribute__((used)) static int nf_tables_fill_obj_info(struct sk_buff *skb, struct net *net,
				   u32 portid, u32 seq, int event, u32 flags,
				   int family, const struct nft_table *table,
				   struct nft_object *obj, bool reset)
{
	struct nfgenmsg *nfmsg;
	struct nlmsghdr *nlh;

	event = nfnl_msg_type(NFNL_SUBSYS_NFTABLES, event);
	nlh = nlmsg_put(skb, portid, seq, event, sizeof(struct nfgenmsg), flags);
	if (nlh == NULL)
		goto nla_put_failure;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family	= family;
	nfmsg->version		= NFNETLINK_V0;
	nfmsg->res_id		= htons(net->nft.base_seq & 0xffff);

	if (nla_put_string(skb, NFTA_OBJ_TABLE, table->name) ||
	    nla_put_string(skb, NFTA_OBJ_NAME, obj->key.name) ||
	    nla_put_be32(skb, NFTA_OBJ_TYPE, htonl(obj->ops->type->type)) ||
	    nla_put_be32(skb, NFTA_OBJ_USE, htonl(obj->use)) ||
	    nft_object_dump(skb, NFTA_OBJ_DATA, obj, reset) ||
	    nla_put_be64(skb, NFTA_OBJ_HANDLE, cpu_to_be64(obj->handle),
			 NFTA_OBJ_PAD))
		goto nla_put_failure;

	nlmsg_end(skb, nlh);
	return 0;

nla_put_failure:
	nlmsg_trim(skb, nlh);
	return -1;
}