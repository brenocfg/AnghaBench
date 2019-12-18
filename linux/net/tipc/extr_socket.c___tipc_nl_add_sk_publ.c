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
struct sk_buff {int dummy; } ;
struct publication {int /*<<< orphan*/  upper; int /*<<< orphan*/  lower; int /*<<< orphan*/  type; int /*<<< orphan*/  key; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  TIPC_NLA_PUBL ; 
 int /*<<< orphan*/  TIPC_NLA_PUBL_KEY ; 
 int /*<<< orphan*/  TIPC_NLA_PUBL_LOWER ; 
 int /*<<< orphan*/  TIPC_NLA_PUBL_TYPE ; 
 int /*<<< orphan*/  TIPC_NLA_PUBL_UPPER ; 
 int /*<<< orphan*/  TIPC_NL_PUBL_GET ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_genl_family ; 

__attribute__((used)) static int __tipc_nl_add_sk_publ(struct sk_buff *skb,
				 struct netlink_callback *cb,
				 struct publication *publ)
{
	void *hdr;
	struct nlattr *attrs;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &tipc_genl_family, NLM_F_MULTI, TIPC_NL_PUBL_GET);
	if (!hdr)
		goto msg_cancel;

	attrs = nla_nest_start_noflag(skb, TIPC_NLA_PUBL);
	if (!attrs)
		goto genlmsg_cancel;

	if (nla_put_u32(skb, TIPC_NLA_PUBL_KEY, publ->key))
		goto attr_msg_cancel;
	if (nla_put_u32(skb, TIPC_NLA_PUBL_TYPE, publ->type))
		goto attr_msg_cancel;
	if (nla_put_u32(skb, TIPC_NLA_PUBL_LOWER, publ->lower))
		goto attr_msg_cancel;
	if (nla_put_u32(skb, TIPC_NLA_PUBL_UPPER, publ->upper))
		goto attr_msg_cancel;

	nla_nest_end(skb, attrs);
	genlmsg_end(skb, hdr);

	return 0;

attr_msg_cancel:
	nla_nest_cancel(skb, attrs);
genlmsg_cancel:
	genlmsg_cancel(skb, hdr);
msg_cancel:
	return -EMSGSIZE;
}