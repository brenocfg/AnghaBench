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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_peer {scalar_t__ is_head; scalar_t__ is_local; scalar_t__ is_up; int /*<<< orphan*/  applied; int /*<<< orphan*/  addr; struct tipc_mon_domain* domain; } ;
struct tipc_nl_msg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct tipc_mon_domain {int member_cnt; int /*<<< orphan*/  members; int /*<<< orphan*/  up_map; int /*<<< orphan*/  gen; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_ADDR ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_APPLIED ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_DOMGEN ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_HEAD ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_LOCAL ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_MEMBERS ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_PAD ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_UP ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEER_UPMAP ; 
 int /*<<< orphan*/  TIPC_NL_MON_PEER_GET ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_genl_family ; 

__attribute__((used)) static int __tipc_nl_add_monitor_peer(struct tipc_peer *peer,
				      struct tipc_nl_msg *msg)
{
	struct tipc_mon_domain *dom = peer->domain;
	struct nlattr *attrs;
	void *hdr;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  NLM_F_MULTI, TIPC_NL_MON_PEER_GET);
	if (!hdr)
		return -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_MON_PEER);
	if (!attrs)
		goto msg_full;

	if (nla_put_u32(msg->skb, TIPC_NLA_MON_PEER_ADDR, peer->addr))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_MON_PEER_APPLIED, peer->applied))
		goto attr_msg_full;

	if (peer->is_up)
		if (nla_put_flag(msg->skb, TIPC_NLA_MON_PEER_UP))
			goto attr_msg_full;
	if (peer->is_local)
		if (nla_put_flag(msg->skb, TIPC_NLA_MON_PEER_LOCAL))
			goto attr_msg_full;
	if (peer->is_head)
		if (nla_put_flag(msg->skb, TIPC_NLA_MON_PEER_HEAD))
			goto attr_msg_full;

	if (dom) {
		if (nla_put_u32(msg->skb, TIPC_NLA_MON_PEER_DOMGEN, dom->gen))
			goto attr_msg_full;
		if (nla_put_u64_64bit(msg->skb, TIPC_NLA_MON_PEER_UPMAP,
				      dom->up_map, TIPC_NLA_MON_PEER_PAD))
			goto attr_msg_full;
		if (nla_put(msg->skb, TIPC_NLA_MON_PEER_MEMBERS,
			    dom->member_cnt * sizeof(u32), &dom->members))
			goto attr_msg_full;
	}

	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);
	return 0;

attr_msg_full:
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	return -EMSGSIZE;
}