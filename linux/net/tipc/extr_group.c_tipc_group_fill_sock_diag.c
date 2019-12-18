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
struct tipc_group {scalar_t__ scope; scalar_t__* open; int /*<<< orphan*/  bc_snd_nxt; int /*<<< orphan*/  instance; int /*<<< orphan*/  type; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ TIPC_CLUSTER_SCOPE ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_GROUP ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_GROUP_BC_SEND_NEXT ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_GROUP_CLUSTER_SCOPE ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_GROUP_ID ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_GROUP_INSTANCE ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_GROUP_NODE_SCOPE ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_GROUP_OPEN ; 
 scalar_t__ TIPC_NODE_SCOPE ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tipc_group_fill_sock_diag(struct tipc_group *grp, struct sk_buff *skb)
{
	struct nlattr *group = nla_nest_start_noflag(skb, TIPC_NLA_SOCK_GROUP);

	if (!group)
		return -EMSGSIZE;

	if (nla_put_u32(skb, TIPC_NLA_SOCK_GROUP_ID,
			grp->type) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_GROUP_INSTANCE,
			grp->instance) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_GROUP_BC_SEND_NEXT,
			grp->bc_snd_nxt))
		goto group_msg_cancel;

	if (grp->scope == TIPC_NODE_SCOPE)
		if (nla_put_flag(skb, TIPC_NLA_SOCK_GROUP_NODE_SCOPE))
			goto group_msg_cancel;

	if (grp->scope == TIPC_CLUSTER_SCOPE)
		if (nla_put_flag(skb, TIPC_NLA_SOCK_GROUP_CLUSTER_SCOPE))
			goto group_msg_cancel;

	if (*grp->open)
		if (nla_put_flag(skb, TIPC_NLA_SOCK_GROUP_OPEN))
			goto group_msg_cancel;

	nla_nest_end(skb, group);
	return 0;

group_msg_cancel:
	nla_nest_cancel(skb, group);
	return -1;
}