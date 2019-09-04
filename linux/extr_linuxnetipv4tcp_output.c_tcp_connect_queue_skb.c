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
struct tcp_sock {int /*<<< orphan*/  packets_out; int /*<<< orphan*/  write_seq; } ;
struct tcp_skb_cb {int /*<<< orphan*/  end_seq; } ;
struct sock {int /*<<< orphan*/  sk_wmem_queued; } ;
struct sk_buff {scalar_t__ truesize; scalar_t__ len; } ;

/* Variables and functions */
 struct tcp_skb_cb* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_header_release (struct sk_buff*) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,scalar_t__) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_skb_pcount (struct sk_buff*) ; 

__attribute__((used)) static void tcp_connect_queue_skb(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct tcp_skb_cb *tcb = TCP_SKB_CB(skb);

	tcb->end_seq += skb->len;
	__skb_header_release(skb);
	sk->sk_wmem_queued += skb->truesize;
	sk_mem_charge(sk, skb->truesize);
	tp->write_seq = tcb->end_seq;
	tp->packets_out += tcp_skb_pcount(skb);
}