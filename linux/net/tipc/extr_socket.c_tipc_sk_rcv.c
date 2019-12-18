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
struct TYPE_2__ {int /*<<< orphan*/  slock; } ;
struct sock {TYPE_1__ sk_lock; } ;
struct tipc_sock {struct sock sk; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_DUMP_NONE ; 
 int TIPC_ERR_NO_PORT ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  buf_msg (struct sk_buff*) ; 
 scalar_t__ likely (struct tipc_sock*) ; 
 int /*<<< orphan*/  msg_destnode (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct tipc_sock* spin_trylock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ tipc_msg_lookup_dest (struct net*,struct sk_buff*,int*) ; 
 int /*<<< orphan*/  tipc_msg_reverse (int /*<<< orphan*/ ,struct sk_buff**,int) ; 
 int /*<<< orphan*/  tipc_node_distr_xmit (int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_node_xmit_skb (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 
 int /*<<< orphan*/  tipc_sk_enqueue (struct sk_buff_head*,struct sock*,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 struct tipc_sock* tipc_sk_lookup (struct net*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_skb_dequeue (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_skb_peek_port (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tipc_sk_rej_msg (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 

void tipc_sk_rcv(struct net *net, struct sk_buff_head *inputq)
{
	struct sk_buff_head xmitq;
	u32 dnode, dport = 0;
	int err;
	struct tipc_sock *tsk;
	struct sock *sk;
	struct sk_buff *skb;

	__skb_queue_head_init(&xmitq);
	while (skb_queue_len(inputq)) {
		dport = tipc_skb_peek_port(inputq, dport);
		tsk = tipc_sk_lookup(net, dport);

		if (likely(tsk)) {
			sk = &tsk->sk;
			if (likely(spin_trylock_bh(&sk->sk_lock.slock))) {
				tipc_sk_enqueue(inputq, sk, dport, &xmitq);
				spin_unlock_bh(&sk->sk_lock.slock);
			}
			/* Send pending response/rejected messages, if any */
			tipc_node_distr_xmit(sock_net(sk), &xmitq);
			sock_put(sk);
			continue;
		}
		/* No destination socket => dequeue skb if still there */
		skb = tipc_skb_dequeue(inputq, dport);
		if (!skb)
			return;

		/* Try secondary lookup if unresolved named message */
		err = TIPC_ERR_NO_PORT;
		if (tipc_msg_lookup_dest(net, skb, &err))
			goto xmit;

		/* Prepare for message rejection */
		if (!tipc_msg_reverse(tipc_own_addr(net), &skb, err))
			continue;

		trace_tipc_sk_rej_msg(NULL, skb, TIPC_DUMP_NONE, "@sk_rcv!");
xmit:
		dnode = msg_destnode(buf_msg(skb));
		tipc_node_xmit_skb(net, skb, dnode, dport);
	}
}