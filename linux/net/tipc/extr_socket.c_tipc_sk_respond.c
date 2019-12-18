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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_DUMP_NONE ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_destnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_origport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tipc_msg_reverse (int /*<<< orphan*/ ,struct sk_buff**,int) ; 
 int /*<<< orphan*/  tipc_node_xmit_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tipc_sk_rej_msg (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void tipc_sk_respond(struct sock *sk, struct sk_buff *skb, int err)
{
	u32 selector;
	u32 dnode;
	u32 onode = tipc_own_addr(sock_net(sk));

	if (!tipc_msg_reverse(onode, &skb, err))
		return;

	trace_tipc_sk_rej_msg(sk, skb, TIPC_DUMP_NONE, "@sk_respond!");
	dnode = msg_destnode(buf_msg(skb));
	selector = msg_origport(buf_msg(skb));
	tipc_node_xmit_skb(sock_net(sk), skb, dnode, selector);
}