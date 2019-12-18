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
struct tipc_msg {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_timer; } ;
struct tipc_sock {int peer_caps; void* snd_win; void* rcv_win; int /*<<< orphan*/  portid; int /*<<< orphan*/  max_pkt; struct tipc_msg phdr; struct sock sk; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ CONN_PROBING_INTV ; 
 void* FLOWCTL_MSG_WIN ; 
 int /*<<< orphan*/  SHORT_H_SIZE ; 
 int TIPC_BLOCK_FLOWCTL ; 
 int /*<<< orphan*/  TIPC_CONN_MSG ; 
 int /*<<< orphan*/  TIPC_ESTABLISHED ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_hdr_sz (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_lookup_scope (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_syn (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tipc_node_add_conn (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tipc_node_get_capabilities (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_get_mtu (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_set_sk_state (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_sk_finish_conn(struct tipc_sock *tsk, u32 peer_port,
				u32 peer_node)
{
	struct sock *sk = &tsk->sk;
	struct net *net = sock_net(sk);
	struct tipc_msg *msg = &tsk->phdr;

	msg_set_syn(msg, 0);
	msg_set_destnode(msg, peer_node);
	msg_set_destport(msg, peer_port);
	msg_set_type(msg, TIPC_CONN_MSG);
	msg_set_lookup_scope(msg, 0);
	msg_set_hdr_sz(msg, SHORT_H_SIZE);

	sk_reset_timer(sk, &sk->sk_timer, jiffies + CONN_PROBING_INTV);
	tipc_set_sk_state(sk, TIPC_ESTABLISHED);
	tipc_node_add_conn(net, peer_node, tsk->portid, peer_port);
	tsk->max_pkt = tipc_node_get_mtu(net, peer_node, tsk->portid);
	tsk->peer_caps = tipc_node_get_capabilities(net, peer_node);
	__skb_queue_purge(&sk->sk_write_queue);
	if (tsk->peer_caps & TIPC_BLOCK_FLOWCTL)
		return;

	/* Fall back to message based flow control */
	tsk->rcv_win = FLOWCTL_MSG_WIN;
	tsk->snd_win = FLOWCTL_MSG_WIN;
}