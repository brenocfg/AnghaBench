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
typedef  scalar_t__ u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int TIPC_ERR_NO_NAME ; 
 int TIPC_OK ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 scalar_t__ msg_errcode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_incr_reroute_cnt (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_isdata (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_lookup_scope (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_named (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nameinst (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_nametype (struct tipc_msg*) ; 
 scalar_t__ msg_reroute_cnt (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_prevnode (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 scalar_t__ tipc_nametbl_translate (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ tipc_own_addr (struct net*) ; 
 scalar_t__ tipc_scope2node (struct net*,int /*<<< orphan*/ ) ; 

bool tipc_msg_lookup_dest(struct net *net, struct sk_buff *skb, int *err)
{
	struct tipc_msg *msg = buf_msg(skb);
	u32 dport, dnode;
	u32 onode = tipc_own_addr(net);

	if (!msg_isdata(msg))
		return false;
	if (!msg_named(msg))
		return false;
	if (msg_errcode(msg))
		return false;
	*err = TIPC_ERR_NO_NAME;
	if (skb_linearize(skb))
		return false;
	msg = buf_msg(skb);
	if (msg_reroute_cnt(msg))
		return false;
	dnode = tipc_scope2node(net, msg_lookup_scope(msg));
	dport = tipc_nametbl_translate(net, msg_nametype(msg),
				       msg_nameinst(msg), &dnode);
	if (!dport)
		return false;
	msg_incr_reroute_cnt(msg);
	if (dnode != onode)
		msg_set_prevnode(msg, onode);
	msg_set_destnode(msg, dnode);
	msg_set_destport(msg, dport);
	*err = TIPC_OK;

	if (!skb_cloned(skb))
		return true;

	return true;
}