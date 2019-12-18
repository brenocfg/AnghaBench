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
struct sock {int sk_state; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_err; int /*<<< orphan*/  sk_timer; int /*<<< orphan*/  sk_write_queue; } ;
struct tipc_sock {int conn_timeout; int /*<<< orphan*/  portid; int /*<<< orphan*/  phdr; struct sock sk; } ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNREFUSED ; 
#define  TIPC_CONNECTING 132 
#define  TIPC_DISCONNECTING 131 
 int TIPC_ERR_OVERLOAD ; 
#define  TIPC_ESTABLISHED 130 
#define  TIPC_LISTEN 129 
#define  TIPC_OPEN 128 
 int TIPC_SYN_BIT ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  get_random_bytes (unsigned long*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  likely (int) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int msg_connected (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_data_sz (struct tipc_msg*) ; 
 int msg_errcode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_importance (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_is_syn (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_mcast (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_origport (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_dest_droppable (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_importance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  stub3 (struct sock*) ; 
 int tipc_node_get_capabilities (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_remove_conn (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_set_sk_state (struct sock*,int const) ; 
 int /*<<< orphan*/  tipc_sk_finish_conn (struct tipc_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsk_peer_msg (struct tipc_sock*,struct tipc_msg*) ; 
 int /*<<< orphan*/  tsk_peer_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_port (struct tipc_sock*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tipc_sk_filter_connect(struct tipc_sock *tsk, struct sk_buff *skb)
{
	struct sock *sk = &tsk->sk;
	struct net *net = sock_net(sk);
	struct tipc_msg *hdr = buf_msg(skb);
	bool con_msg = msg_connected(hdr);
	u32 pport = tsk_peer_port(tsk);
	u32 pnode = tsk_peer_node(tsk);
	u32 oport = msg_origport(hdr);
	u32 onode = msg_orignode(hdr);
	int err = msg_errcode(hdr);
	unsigned long delay;

	if (unlikely(msg_mcast(hdr)))
		return false;

	switch (sk->sk_state) {
	case TIPC_CONNECTING:
		/* Setup ACK */
		if (likely(con_msg)) {
			if (err)
				break;
			tipc_sk_finish_conn(tsk, oport, onode);
			msg_set_importance(&tsk->phdr, msg_importance(hdr));
			/* ACK+ message with data is added to receive queue */
			if (msg_data_sz(hdr))
				return true;
			/* Empty ACK-, - wake up sleeping connect() and drop */
			sk->sk_state_change(sk);
			msg_set_dest_droppable(hdr, 1);
			return false;
		}
		/* Ignore connectionless message if not from listening socket */
		if (oport != pport || onode != pnode)
			return false;

		/* Rejected SYN */
		if (err != TIPC_ERR_OVERLOAD)
			break;

		/* Prepare for new setup attempt if we have a SYN clone */
		if (skb_queue_empty(&sk->sk_write_queue))
			break;
		get_random_bytes(&delay, 2);
		delay %= (tsk->conn_timeout / 4);
		delay = msecs_to_jiffies(delay + 100);
		sk_reset_timer(sk, &sk->sk_timer, jiffies + delay);
		return false;
	case TIPC_OPEN:
	case TIPC_DISCONNECTING:
		return false;
	case TIPC_LISTEN:
		/* Accept only SYN message */
		if (!msg_is_syn(hdr) &&
		    tipc_node_get_capabilities(net, onode) & TIPC_SYN_BIT)
			return false;
		if (!con_msg && !err)
			return true;
		return false;
	case TIPC_ESTABLISHED:
		/* Accept only connection-based messages sent by peer */
		if (likely(con_msg && !err && pport == oport && pnode == onode))
			return true;
		if (!tsk_peer_msg(tsk, hdr))
			return false;
		if (!err)
			return true;
		tipc_set_sk_state(sk, TIPC_DISCONNECTING);
		tipc_node_remove_conn(net, pnode, tsk->portid);
		sk->sk_state_change(sk);
		return true;
	default:
		pr_err("Unknown sk_state %u\n", sk->sk_state);
	}
	/* Abort connection setup attempt */
	tipc_set_sk_state(sk, TIPC_DISCONNECTING);
	sk->sk_err = ECONNREFUSED;
	sk->sk_state_change(sk);
	return true;
}