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
struct tipc_sock {int probe_unacked; int /*<<< orphan*/  portid; } ;
struct sock {int /*<<< orphan*/  sk_timer; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_err; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_MANAGER ; 
 int /*<<< orphan*/  CONN_PROBE ; 
 scalar_t__ CONN_PROBING_INTV ; 
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  INT_H_SIZE ; 
 int /*<<< orphan*/  TIPC_DISCONNECTING ; 
 int /*<<< orphan*/  TIPC_OK ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct sk_buff* tipc_msg_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_remove_conn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_set_sk_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tsk_own_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_port (struct tipc_sock*) ; 

__attribute__((used)) static void tipc_sk_check_probing_state(struct sock *sk,
					struct sk_buff_head *list)
{
	struct tipc_sock *tsk = tipc_sk(sk);
	u32 pnode = tsk_peer_node(tsk);
	u32 pport = tsk_peer_port(tsk);
	u32 self = tsk_own_node(tsk);
	u32 oport = tsk->portid;
	struct sk_buff *skb;

	if (tsk->probe_unacked) {
		tipc_set_sk_state(sk, TIPC_DISCONNECTING);
		sk->sk_err = ECONNABORTED;
		tipc_node_remove_conn(sock_net(sk), pnode, pport);
		sk->sk_state_change(sk);
		return;
	}
	/* Prepare new probe */
	skb = tipc_msg_create(CONN_MANAGER, CONN_PROBE, INT_H_SIZE, 0,
			      pnode, self, pport, oport, TIPC_OK);
	if (skb)
		__skb_queue_tail(list, skb);
	tsk->probe_unacked = true;
	sk_reset_timer(sk, &sk->sk_timer, jiffies + CONN_PROBING_INTV);
}