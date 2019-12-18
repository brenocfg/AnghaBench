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
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sock {struct sk_buff_head sk_receive_queue; } ;
struct sk_buff {int len; } ;
struct TYPE_2__ {struct sk_buff_head reader_queue; } ;

/* Variables and functions */
 struct sk_buff* __first_packet_length (struct sock*,struct sk_buff_head*,int*) ; 
 int /*<<< orphan*/  skb_queue_empty_lockless (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_rmem_release (struct sock*,int,int,int) ; 
 TYPE_1__* udp_sk (struct sock*) ; 

__attribute__((used)) static int first_packet_length(struct sock *sk)
{
	struct sk_buff_head *rcvq = &udp_sk(sk)->reader_queue;
	struct sk_buff_head *sk_queue = &sk->sk_receive_queue;
	struct sk_buff *skb;
	int total = 0;
	int res;

	spin_lock_bh(&rcvq->lock);
	skb = __first_packet_length(sk, rcvq, &total);
	if (!skb && !skb_queue_empty_lockless(sk_queue)) {
		spin_lock(&sk_queue->lock);
		skb_queue_splice_tail_init(sk_queue, rcvq);
		spin_unlock(&sk_queue->lock);

		skb = __first_packet_length(sk, rcvq, &total);
	}
	res = skb ? skb->len : -1;
	if (total)
		udp_rmem_release(sk, total, 1, false);
	spin_unlock_bh(&rcvq->lock);
	return res;
}