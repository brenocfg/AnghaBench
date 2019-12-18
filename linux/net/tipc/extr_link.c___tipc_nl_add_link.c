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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_nl_msg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct TYPE_2__ {int /*<<< orphan*/  sent_pkts; int /*<<< orphan*/  recv_pkts; } ;
struct tipc_link {TYPE_1__ stats; int /*<<< orphan*/  priority; int /*<<< orphan*/  window; int /*<<< orphan*/  tolerance; scalar_t__ active; int /*<<< orphan*/  mtu; int /*<<< orphan*/  name; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TIPC_NLA_LINK ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_ACTIVE ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_DEST ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_MTU ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_NAME ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_PROP ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_RX ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_TX ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_UP ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_PRIO ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_TOL ; 
 int /*<<< orphan*/  TIPC_NLA_PROP_WIN ; 
 int /*<<< orphan*/  TIPC_NL_LINK_GET ; 
 int __tipc_nl_add_stats (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cluster_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_genl_family ; 
 scalar_t__ tipc_link_is_up (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 

int __tipc_nl_add_link(struct net *net, struct tipc_nl_msg *msg,
		       struct tipc_link *link, int nlflags)
{
	u32 self = tipc_own_addr(net);
	struct nlattr *attrs;
	struct nlattr *prop;
	void *hdr;
	int err;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  nlflags, TIPC_NL_LINK_GET);
	if (!hdr)
		return -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_LINK);
	if (!attrs)
		goto msg_full;

	if (nla_put_string(msg->skb, TIPC_NLA_LINK_NAME, link->name))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_LINK_DEST, tipc_cluster_mask(self)))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_LINK_MTU, link->mtu))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_LINK_RX, link->stats.recv_pkts))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_LINK_TX, link->stats.sent_pkts))
		goto attr_msg_full;

	if (tipc_link_is_up(link))
		if (nla_put_flag(msg->skb, TIPC_NLA_LINK_UP))
			goto attr_msg_full;
	if (link->active)
		if (nla_put_flag(msg->skb, TIPC_NLA_LINK_ACTIVE))
			goto attr_msg_full;

	prop = nla_nest_start_noflag(msg->skb, TIPC_NLA_LINK_PROP);
	if (!prop)
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_PRIO, link->priority))
		goto prop_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_TOL, link->tolerance))
		goto prop_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_WIN,
			link->window))
		goto prop_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_PROP_PRIO, link->priority))
		goto prop_msg_full;
	nla_nest_end(msg->skb, prop);

	err = __tipc_nl_add_stats(msg->skb, &link->stats);
	if (err)
		goto attr_msg_full;

	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	return 0;

prop_msg_full:
	nla_nest_cancel(msg->skb, prop);
attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	return -EMSGSIZE;
}