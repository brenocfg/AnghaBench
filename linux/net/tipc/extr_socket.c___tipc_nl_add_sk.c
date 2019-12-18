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
struct tipc_sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK ; 
 int /*<<< orphan*/  TIPC_NL_SOCK_GET ; 
 scalar_t__ __tipc_nl_add_sk_info (struct sk_buff*,struct tipc_sock*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_genl_family ; 

__attribute__((used)) static int __tipc_nl_add_sk(struct sk_buff *skb, struct netlink_callback *cb,
			    struct tipc_sock *tsk)
{
	struct nlattr *attrs;
	void *hdr;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &tipc_genl_family, NLM_F_MULTI, TIPC_NL_SOCK_GET);
	if (!hdr)
		goto msg_cancel;

	attrs = nla_nest_start_noflag(skb, TIPC_NLA_SOCK);
	if (!attrs)
		goto genlmsg_cancel;

	if (__tipc_nl_add_sk_info(skb, tsk))
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