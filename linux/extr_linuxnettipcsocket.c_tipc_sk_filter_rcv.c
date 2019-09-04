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
struct tipc_sock {struct tipc_group* group; } ;
struct tipc_msg {int dummy; } ;
struct tipc_group {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;struct sk_buff_head sk_receive_queue; int /*<<< orphan*/  sk_drops; } ;
struct sk_buff {int truesize; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ bytes_read; } ;

/* Variables and functions */
 int TIPC_ERR_NO_PORT ; 
 int TIPC_ERR_OVERLOAD ; 
 int TIPC_OK ; 
 TYPE_1__* TIPC_SKB_CB (struct sk_buff*) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 scalar_t__ msg_connected (struct tipc_msg*) ; 
 scalar_t__ msg_in_group (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_isdata (struct tipc_msg*) ; 
 int rcvbuf_limit (struct sock*,struct sk_buff*) ; 
 int sk_rmem_alloc_get (struct sock*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tipc_group_filter_msg (struct tipc_group*,struct sk_buff_head*,struct sk_buff_head*) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_filter_connect (struct tipc_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tipc_sk_proto_rcv (struct sock*,struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_sk_type_connectionless (struct sock*) ; 
 int /*<<< orphan*/  tipc_skb_reject (struct net*,int,struct sk_buff*,struct sk_buff_head*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tipc_sk_filter_rcv(struct sock *sk, struct sk_buff *skb,
			       struct sk_buff_head *xmitq)
{
	bool sk_conn = !tipc_sk_type_connectionless(sk);
	struct tipc_sock *tsk = tipc_sk(sk);
	struct tipc_group *grp = tsk->group;
	struct tipc_msg *hdr = buf_msg(skb);
	struct net *net = sock_net(sk);
	struct sk_buff_head inputq;
	int limit, err = TIPC_OK;

	TIPC_SKB_CB(skb)->bytes_read = 0;
	__skb_queue_head_init(&inputq);
	__skb_queue_tail(&inputq, skb);

	if (unlikely(!msg_isdata(hdr)))
		tipc_sk_proto_rcv(sk, &inputq, xmitq);

	if (unlikely(grp))
		tipc_group_filter_msg(grp, &inputq, xmitq);

	/* Validate and add to receive buffer if there is space */
	while ((skb = __skb_dequeue(&inputq))) {
		hdr = buf_msg(skb);
		limit = rcvbuf_limit(sk, skb);
		if ((sk_conn && !tipc_sk_filter_connect(tsk, skb)) ||
		    (!sk_conn && msg_connected(hdr)) ||
		    (!grp && msg_in_group(hdr)))
			err = TIPC_ERR_NO_PORT;
		else if (sk_rmem_alloc_get(sk) + skb->truesize >= limit) {
			atomic_inc(&sk->sk_drops);
			err = TIPC_ERR_OVERLOAD;
		}

		if (unlikely(err)) {
			tipc_skb_reject(net, err, skb, xmitq);
			err = TIPC_OK;
			continue;
		}
		__skb_queue_tail(&sk->sk_receive_queue, skb);
		skb_set_owner_r(skb, sk);
		sk->sk_data_ready(sk);
	}
}