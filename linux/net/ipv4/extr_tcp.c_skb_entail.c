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
struct tcp_sock {int nonagle; int /*<<< orphan*/  write_seq; } ;
struct tcp_skb_cb {scalar_t__ sacked; int /*<<< orphan*/  tcp_flags; int /*<<< orphan*/  end_seq; int /*<<< orphan*/  seq; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  truesize; scalar_t__ csum; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPHDR_ACK ; 
 int TCP_NAGLE_PUSH ; 
 struct tcp_skb_cb* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_header_release (struct sk_buff*) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_wmem_queued_add (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_add_write_queue_tail (struct sock*,struct sk_buff*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_slow_start_after_idle_check (struct sock*) ; 

__attribute__((used)) static void skb_entail(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct tcp_skb_cb *tcb = TCP_SKB_CB(skb);

	skb->csum    = 0;
	tcb->seq     = tcb->end_seq = tp->write_seq;
	tcb->tcp_flags = TCPHDR_ACK;
	tcb->sacked  = 0;
	__skb_header_release(skb);
	tcp_add_write_queue_tail(sk, skb);
	sk_wmem_queued_add(sk, skb->truesize);
	sk_mem_charge(sk, skb->truesize);
	if (tp->nonagle & TCP_NAGLE_PUSH)
		tp->nonagle &= ~TCP_NAGLE_PUSH;

	tcp_slow_start_after_idle_check(sk);
}