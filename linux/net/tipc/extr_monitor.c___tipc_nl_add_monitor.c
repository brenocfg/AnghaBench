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
struct tipc_nl_msg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; } ;
struct tipc_monitor {int /*<<< orphan*/  lock; int /*<<< orphan*/  list_gen; int /*<<< orphan*/  peer_cnt; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int TIPC_MAX_BEARER_NAME ; 
 int /*<<< orphan*/  TIPC_NLA_MON ; 
 int /*<<< orphan*/  TIPC_NLA_MON_ACTIVE ; 
 int /*<<< orphan*/  TIPC_NLA_MON_BEARER_NAME ; 
 int /*<<< orphan*/  TIPC_NLA_MON_LISTGEN ; 
 int /*<<< orphan*/  TIPC_NLA_MON_PEERCNT ; 
 int /*<<< orphan*/  TIPC_NLA_MON_REF ; 
 int /*<<< orphan*/  TIPC_NL_MON_GET ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int tipc_bearer_get_name (struct net*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_genl_family ; 
 scalar_t__ tipc_mon_is_active (struct net*,struct tipc_monitor*) ; 
 struct tipc_monitor* tipc_monitor (struct net*,int /*<<< orphan*/ ) ; 

int __tipc_nl_add_monitor(struct net *net, struct tipc_nl_msg *msg,
			  u32 bearer_id)
{
	struct tipc_monitor *mon = tipc_monitor(net, bearer_id);
	char bearer_name[TIPC_MAX_BEARER_NAME];
	struct nlattr *attrs;
	void *hdr;
	int ret;

	ret = tipc_bearer_get_name(net, bearer_name, bearer_id);
	if (ret || !mon)
		return 0;

	hdr = genlmsg_put(msg->skb, msg->portid, msg->seq, &tipc_genl_family,
			  NLM_F_MULTI, TIPC_NL_MON_GET);
	if (!hdr)
		return -EMSGSIZE;

	attrs = nla_nest_start_noflag(msg->skb, TIPC_NLA_MON);
	if (!attrs)
		goto msg_full;

	read_lock_bh(&mon->lock);
	if (nla_put_u32(msg->skb, TIPC_NLA_MON_REF, bearer_id))
		goto attr_msg_full;
	if (tipc_mon_is_active(net, mon))
		if (nla_put_flag(msg->skb, TIPC_NLA_MON_ACTIVE))
			goto attr_msg_full;
	if (nla_put_string(msg->skb, TIPC_NLA_MON_BEARER_NAME, bearer_name))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_MON_PEERCNT, mon->peer_cnt))
		goto attr_msg_full;
	if (nla_put_u32(msg->skb, TIPC_NLA_MON_LISTGEN, mon->list_gen))
		goto attr_msg_full;

	read_unlock_bh(&mon->lock);
	nla_nest_end(msg->skb, attrs);
	genlmsg_end(msg->skb, hdr);

	return 0;

attr_msg_full:
	read_unlock_bh(&mon->lock);
	nla_nest_cancel(msg->skb, attrs);
msg_full:
	genlmsg_cancel(msg->skb, hdr);

	return -EMSGSIZE;
}