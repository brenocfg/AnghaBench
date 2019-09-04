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
struct sock {int sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;void* sk_err; } ;
struct tipc_sock {int /*<<< orphan*/  portid; int /*<<< orphan*/  phdr; struct sock sk; } ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 void* ECONNREFUSED ; 
 void* EINVAL ; 
#define  TIPC_CONNECTING 132 
#define  TIPC_DISCONNECTING 131 
#define  TIPC_ESTABLISHED 130 
#define  TIPC_LISTEN 129 
#define  TIPC_OPEN 128 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_connected (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_data_sz (struct tipc_msg*) ; 
 int msg_errcode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_importance (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_isdata (struct tipc_msg*) ; 
 int msg_mcast (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_origport (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_dest_droppable (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_importance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  stub3 (struct sock*) ; 
 int /*<<< orphan*/  stub4 (struct sock*) ; 
 int /*<<< orphan*/  stub5 (struct sock*) ; 
 int /*<<< orphan*/  tipc_node_remove_conn (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_set_sk_state (struct sock*,int const) ; 
 int /*<<< orphan*/  tipc_sk_finish_conn (struct tipc_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsk_peer_msg (struct tipc_sock*,struct tipc_msg*) ; 
 int /*<<< orphan*/  tsk_peer_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_port (struct tipc_sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool tipc_sk_filter_connect(struct tipc_sock *tsk, struct sk_buff *skb)
{
	struct sock *sk = &tsk->sk;
	struct net *net = sock_net(sk);
	struct tipc_msg *hdr = buf_msg(skb);
	u32 pport = msg_origport(hdr);
	u32 pnode = msg_orignode(hdr);

	if (unlikely(msg_mcast(hdr)))
		return false;

	switch (sk->sk_state) {
	case TIPC_CONNECTING:
		/* Accept only ACK or NACK message */
		if (unlikely(!msg_connected(hdr))) {
			if (pport != tsk_peer_port(tsk) ||
			    pnode != tsk_peer_node(tsk))
				return false;

			tipc_set_sk_state(sk, TIPC_DISCONNECTING);
			sk->sk_err = ECONNREFUSED;
			sk->sk_state_change(sk);
			return true;
		}

		if (unlikely(msg_errcode(hdr))) {
			tipc_set_sk_state(sk, TIPC_DISCONNECTING);
			sk->sk_err = ECONNREFUSED;
			sk->sk_state_change(sk);
			return true;
		}

		if (unlikely(!msg_isdata(hdr))) {
			tipc_set_sk_state(sk, TIPC_DISCONNECTING);
			sk->sk_err = EINVAL;
			sk->sk_state_change(sk);
			return true;
		}

		tipc_sk_finish_conn(tsk, msg_origport(hdr), msg_orignode(hdr));
		msg_set_importance(&tsk->phdr, msg_importance(hdr));

		/* If 'ACK+' message, add to socket receive queue */
		if (msg_data_sz(hdr))
			return true;

		/* If empty 'ACK-' message, wake up sleeping connect() */
		sk->sk_data_ready(sk);

		/* 'ACK-' message is neither accepted nor rejected: */
		msg_set_dest_droppable(hdr, 1);
		return false;

	case TIPC_OPEN:
	case TIPC_DISCONNECTING:
		break;
	case TIPC_LISTEN:
		/* Accept only SYN message */
		if (!msg_connected(hdr) && !(msg_errcode(hdr)))
			return true;
		break;
	case TIPC_ESTABLISHED:
		/* Accept only connection-based messages sent by peer */
		if (unlikely(!tsk_peer_msg(tsk, hdr)))
			return false;

		if (unlikely(msg_errcode(hdr))) {
			tipc_set_sk_state(sk, TIPC_DISCONNECTING);
			/* Let timer expire on it's own */
			tipc_node_remove_conn(net, tsk_peer_node(tsk),
					      tsk->portid);
			sk->sk_state_change(sk);
		}
		return true;
	default:
		pr_err("Unknown sk_state %u\n", sk->sk_state);
	}

	return false;
}