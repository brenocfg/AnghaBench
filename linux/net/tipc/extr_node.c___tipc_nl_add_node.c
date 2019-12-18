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
struct tipc_node {int /*<<< orphan*/  addr; } ;
struct tipc_nl_msg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  TIPC_NLA_NODE ; 
 int /*<<< orphan*/  TIPC_NLA_NODE_ADDR ; 
 int /*<<< orphan*/  TIPC_NLA_NODE_UP ; 
 int /*<<< orphan*/  TIPC_NL_NODE_GET ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ node_is_up (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_genl_family ; 

__attribute__((used)) static int __tipc_nl_add_node(struct tipc_nl_msg *msg, struct tipc_node *node)
{
	void *hdr;
	struct nlattr *attrs;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  NLM_F_MULTI, TIPC_NL_NODE_GET);
	if (!hdr)
		return -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_NODE);
	if (!attrs)
		goto msg_full;

	if (nla_put_u32(msg->skb, TIPC_NLA_NODE_ADDR, node->addr))
		goto attr_msg_full;
	if (node_is_up(node))
		if (nla_put_flag(msg->skb, TIPC_NLA_NODE_UP))
			goto attr_msg_full;

	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	return 0;

attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	return -EMSGSIZE;
}