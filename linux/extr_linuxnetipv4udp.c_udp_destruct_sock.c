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
struct udp_sock {int /*<<< orphan*/  reader_queue; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {scalar_t__ truesize; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_sock_destruct (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_rmem_release (struct sock*,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct udp_sock* udp_sk (struct sock*) ; 

void udp_destruct_sock(struct sock *sk)
{
	/* reclaim completely the forward allocated memory */
	struct udp_sock *up = udp_sk(sk);
	unsigned int total = 0;
	struct sk_buff *skb;

	skb_queue_splice_tail_init(&sk->sk_receive_queue, &up->reader_queue);
	while ((skb = __skb_dequeue(&up->reader_queue)) != NULL) {
		total += skb->truesize;
		kfree_skb(skb);
	}
	udp_rmem_release(sk, total, 0, true);

	inet_sock_destruct(sk);
}