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
struct tipc_sock {int /*<<< orphan*/  portid; int /*<<< orphan*/  cong_link_cnt; } ;
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ bytes_read; } ;

/* Variables and functions */
 long CONN_TIMEOUT_DEFAULT ; 
 int /*<<< orphan*/  SHORT_H_SIZE ; 
 int /*<<< orphan*/  TIPC_CONN_MSG ; 
 int /*<<< orphan*/  TIPC_CRITICAL_IMPORTANCE ; 
 scalar_t__ TIPC_DISCONNECTING ; 
 TYPE_1__* TIPC_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct net* sock_net (struct sock*) ; 
 struct sk_buff* tipc_msg_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tipc_node_remove_conn (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_xmit_skb (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_set_sk_state (struct sock*,scalar_t__) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_respond (struct sock*,struct sk_buff*,int) ; 
 scalar_t__ tipc_sk_type_connectionless (struct sock*) ; 
 int /*<<< orphan*/  tipc_wait_for_cond (struct socket*,long*,int) ; 
 int /*<<< orphan*/  tsk_conn_cong (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_own_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_port (struct tipc_sock*) ; 

__attribute__((used)) static void __tipc_shutdown(struct socket *sock, int error)
{
	struct sock *sk = sock->sk;
	struct tipc_sock *tsk = tipc_sk(sk);
	struct net *net = sock_net(sk);
	long timeout = CONN_TIMEOUT_DEFAULT;
	u32 dnode = tsk_peer_node(tsk);
	struct sk_buff *skb;

	/* Avoid that hi-prio shutdown msgs bypass msgs in link wakeup queue */
	tipc_wait_for_cond(sock, &timeout, (!tsk->cong_link_cnt &&
					    !tsk_conn_cong(tsk)));

	/* Remove any pending SYN message */
	__skb_queue_purge(&sk->sk_write_queue);

	/* Reject all unreceived messages, except on an active connection
	 * (which disconnects locally & sends a 'FIN+' to peer).
	 */
	while ((skb = __skb_dequeue(&sk->sk_receive_queue)) != NULL) {
		if (TIPC_SKB_CB(skb)->bytes_read) {
			kfree_skb(skb);
			continue;
		}
		if (!tipc_sk_type_connectionless(sk) &&
		    sk->sk_state != TIPC_DISCONNECTING) {
			tipc_set_sk_state(sk, TIPC_DISCONNECTING);
			tipc_node_remove_conn(net, dnode, tsk->portid);
		}
		tipc_sk_respond(sk, skb, error);
	}

	if (tipc_sk_type_connectionless(sk))
		return;

	if (sk->sk_state != TIPC_DISCONNECTING) {
		skb = tipc_msg_create(TIPC_CRITICAL_IMPORTANCE,
				      TIPC_CONN_MSG, SHORT_H_SIZE, 0, dnode,
				      tsk_own_node(tsk), tsk_peer_port(tsk),
				      tsk->portid, error);
		if (skb)
			tipc_node_xmit_skb(net, skb, dnode, tsk->portid);
		tipc_node_remove_conn(net, dnode, tsk->portid);
		tipc_set_sk_state(sk, TIPC_DISCONNECTING);
	}
}