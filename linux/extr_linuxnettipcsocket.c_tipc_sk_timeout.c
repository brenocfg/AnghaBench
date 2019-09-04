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
struct timer_list {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_timer; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;} ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_MANAGER ; 
 int /*<<< orphan*/  CONN_PROBE ; 
 scalar_t__ CONN_PROBING_INTV ; 
 int HZ ; 
 int /*<<< orphan*/  INT_H_SIZE ; 
 int /*<<< orphan*/  TIPC_DISCONNECTING ; 
 int /*<<< orphan*/  TIPC_OK ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct sock* sk ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sk_timer ; 
 struct net* sock_net (struct sock*) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct sk_buff* tipc_msg_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_remove_conn (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_xmit_skb (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_set_sk_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_connected (struct sock*) ; 
 int /*<<< orphan*/  tsk_own_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_port (struct tipc_sock*) ; 

__attribute__((used)) static void tipc_sk_timeout(struct timer_list *t)
{
	struct sock *sk = from_timer(sk, t, sk_timer);
	struct tipc_sock *tsk = tipc_sk(sk);
	u32 peer_port = tsk_peer_port(tsk);
	u32 peer_node = tsk_peer_node(tsk);
	u32 own_node = tsk_own_node(tsk);
	u32 own_port = tsk->portid;
	struct net *net = sock_net(sk);
	struct sk_buff *skb = NULL;

	bh_lock_sock(sk);
	if (!tipc_sk_connected(sk))
		goto exit;

	/* Try again later if socket is busy */
	if (sock_owned_by_user(sk)) {
		sk_reset_timer(sk, &sk->sk_timer, jiffies + HZ / 20);
		goto exit;
	}

	if (tsk->probe_unacked) {
		tipc_set_sk_state(sk, TIPC_DISCONNECTING);
		tipc_node_remove_conn(net, peer_node, peer_port);
		sk->sk_state_change(sk);
		goto exit;
	}
	/* Send new probe */
	skb = tipc_msg_create(CONN_MANAGER, CONN_PROBE, INT_H_SIZE, 0,
			      peer_node, own_node, peer_port, own_port,
			      TIPC_OK);
	tsk->probe_unacked = true;
	sk_reset_timer(sk, &sk->sk_timer, jiffies + CONN_PROBING_INTV);
exit:
	bh_unlock_sock(sk);
	if (skb)
		tipc_node_xmit_skb(net, skb, peer_node, own_port);
	sock_put(sk);
}