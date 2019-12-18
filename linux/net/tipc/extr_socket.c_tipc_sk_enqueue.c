#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct sock {int /*<<< orphan*/  sk_drops; TYPE_1__ sk_backlog; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_4__ {int /*<<< orphan*/  dupl_rcvcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
 int /*<<< orphan*/  TIPC_ERR_OVERLOAD ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 scalar_t__ likely (int) ; 
 unsigned int rcvbuf_limit (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sk_add_backlog (struct sock*,struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int time_after_eq (int,unsigned long) ; 
 scalar_t__ tipc_msg_reverse (int /*<<< orphan*/ ,struct sk_buff**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (int /*<<< orphan*/ ) ; 
 TYPE_2__* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_filter_rcv (struct sock*,struct sk_buff*,struct sk_buff_head*) ; 
 struct sk_buff* tipc_skb_dequeue (struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tipc_sk_dump (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace_tipc_sk_overlimit1 (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace_tipc_sk_rej_msg (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tipc_sk_enqueue(struct sk_buff_head *inputq, struct sock *sk,
			    u32 dport, struct sk_buff_head *xmitq)
{
	unsigned long time_limit = jiffies + 2;
	struct sk_buff *skb;
	unsigned int lim;
	atomic_t *dcnt;
	u32 onode;

	while (skb_queue_len(inputq)) {
		if (unlikely(time_after_eq(jiffies, time_limit)))
			return;

		skb = tipc_skb_dequeue(inputq, dport);
		if (unlikely(!skb))
			return;

		/* Add message directly to receive queue if possible */
		if (!sock_owned_by_user(sk)) {
			tipc_sk_filter_rcv(sk, skb, xmitq);
			continue;
		}

		/* Try backlog, compensating for double-counted bytes */
		dcnt = &tipc_sk(sk)->dupl_rcvcnt;
		if (!sk->sk_backlog.len)
			atomic_set(dcnt, 0);
		lim = rcvbuf_limit(sk, skb) + atomic_read(dcnt);
		if (likely(!sk_add_backlog(sk, skb, lim))) {
			trace_tipc_sk_overlimit1(sk, skb, TIPC_DUMP_ALL,
						 "bklg & rcvq >90% allocated!");
			continue;
		}

		trace_tipc_sk_dump(sk, skb, TIPC_DUMP_ALL, "err_overload!");
		/* Overload => reject message back to sender */
		onode = tipc_own_addr(sock_net(sk));
		atomic_inc(&sk->sk_drops);
		if (tipc_msg_reverse(onode, &skb, TIPC_ERR_OVERLOAD)) {
			trace_tipc_sk_rej_msg(sk, skb, TIPC_DUMP_ALL,
					      "@sk_enqueue!");
			__skb_queue_tail(xmitq, skb);
		}
		break;
	}
}