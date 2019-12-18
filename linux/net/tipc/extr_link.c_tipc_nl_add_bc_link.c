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
typedef  int u32 ;
struct tipc_nl_msg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct tipc_net {struct tipc_link* bcl; } ;
struct tipc_link {int window; int /*<<< orphan*/  stats; int /*<<< orphan*/  name; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int BCLINK_MODE_SEL ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  TIPC_NLA_LINK ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_BROADCAST ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_NAME ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_PROP ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_RX ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_TX ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_UP ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_BROADCAST ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_BROADCAST_RATIO ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_WIN ; 
 int /*<<< orphan*/  TIPC_NL_LINK_GET ; 
 int __tipc_nl_add_bc_link_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tipc_bcast_get_broadcast_mode (struct net*) ; 
 int tipc_bcast_get_broadcast_ratio (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_genl_family ; 
 int /*<<< orphan*/  tipc_net_id ; 

int tipc_nl_add_bc_link(struct net *net, struct tipc_nl_msg *msg)
{
	int err;
	void *hdr;
	struct nlattr *attrs;
	struct nlattr *prop;
	struct tipc_net *tn = net_generic(net, tipc_net_id);
	u32 bc_mode = tipc_bcast_get_broadcast_mode(net);
	u32 bc_ratio = tipc_bcast_get_broadcast_ratio(net);
	struct tipc_link *bcl = tn->bcl;

	if (!bcl)
		return 0;

	tipc_bcast_lock(net);

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  NLM_F_MULTI, TIPC_NL_LINK_GET);
	if (!hdr) {
		tipc_bcast_unlock(net);
		return -EMSGSIZE;
	}

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_LINK);
	if (!attrs)
		goto msg_full;

	/* The broadcast link is always up */
	if (nla_put_flag(msg->skb, TIPC_NLA_LINK_UP))
		goto attr_msg_full;

	if (nla_put_flag(msg->skb, TIPC_NLA_LINK_BROADCAST))
		goto attr_msg_full;
	if (nla_put_string(msg->skb, TIPC_NLA_LINK_NAME, bcl->name))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_LINK_RX, 0))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_LINK_TX, 0))
		goto attr_msg_full;

	prop = nla_nest_start_noflag(msg->skb, TIPC_NLA_LINK_PROP);
	if (!prop)
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_WIN, bcl->window))
		goto prop_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_BROADCAST, bc_mode))
		goto prop_msg_full;
	if (bc_mode & BCLINK_MODE_SEL)
		if (nla_put_u32(msg->skb, TIPC_NLA_PROP_BROADCAST_RATIO,
				bc_ratio))
			goto prop_msg_full;
	nla_nest_end(msg->skb, prop);

	err = __tipc_nl_add_bc_link_stat(msg->skb, &bcl->stats);
	if (err)
		goto attr_msg_full;

	tipc_bcast_unlock(net);
	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	return 0;

prop_msg_full:
	nla_nest_cancel(msg->skb, prop);
attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	tipc_bcast_unlock(net);
	genlmsg_cancel(msg->skb, hdr);

	return -EMSGSIZE;
}