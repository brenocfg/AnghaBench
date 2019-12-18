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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {struct sk_buff_head reader_queue; } ;

/* Variables and functions */
 int EAGAIN ; 
 unsigned int MSG_DONTWAIT ; 
 struct sk_buff* __skb_try_recv_from_queue (struct sock*,struct sk_buff_head*,unsigned int,int /*<<< orphan*/ ,int*,int*,struct sk_buff**) ; 
 int /*<<< orphan*/  __skb_wait_for_more_packets (struct sock*,int*,long*,struct sk_buff*) ; 
 int /*<<< orphan*/  sk_busy_loop (struct sock*,unsigned int) ; 
 int /*<<< orphan*/  sk_can_busy_loop (struct sock*) ; 
 scalar_t__ skb_queue_empty_lockless (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,struct sk_buff_head*) ; 
 int sock_error (struct sock*) ; 
 long sock_rcvtimeo (struct sock*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 TYPE_1__* udp_sk (struct sock*) ; 
 int /*<<< orphan*/  udp_skb_destructor ; 
 int /*<<< orphan*/  udp_skb_dtor_locked ; 

struct sk_buff *__skb_recv_udp(struct sock *sk, unsigned int flags,
			       int noblock, int *off, int *err)
{
	struct sk_buff_head *sk_queue = &sk->sk_receive_queue;
	struct sk_buff_head *queue;
	struct sk_buff *last;
	long timeo;
	int error;

	queue = &udp_sk(sk)->reader_queue;
	flags |= noblock ? MSG_DONTWAIT : 0;
	timeo = sock_rcvtimeo(sk, flags & MSG_DONTWAIT);
	do {
		struct sk_buff *skb;

		error = sock_error(sk);
		if (error)
			break;

		error = -EAGAIN;
		do {
			spin_lock_bh(&queue->lock);
			skb = __skb_try_recv_from_queue(sk, queue, flags,
							udp_skb_destructor,
							off, err, &last);
			if (skb) {
				spin_unlock_bh(&queue->lock);
				return skb;
			}

			if (skb_queue_empty_lockless(sk_queue)) {
				spin_unlock_bh(&queue->lock);
				goto busy_check;
			}

			/* refill the reader queue and walk it again
			 * keep both queues locked to avoid re-acquiring
			 * the sk_receive_queue lock if fwd memory scheduling
			 * is needed.
			 */
			spin_lock(&sk_queue->lock);
			skb_queue_splice_tail_init(sk_queue, queue);

			skb = __skb_try_recv_from_queue(sk, queue, flags,
							udp_skb_dtor_locked,
							off, err, &last);
			spin_unlock(&sk_queue->lock);
			spin_unlock_bh(&queue->lock);
			if (skb)
				return skb;

busy_check:
			if (!sk_can_busy_loop(sk))
				break;

			sk_busy_loop(sk, flags & MSG_DONTWAIT);
		} while (!skb_queue_empty_lockless(sk_queue));

		/* sk_queue is empty, reader_queue may contain peeked packets */
	} while (timeo &&
		 !__skb_wait_for_more_packets(sk, &error, &timeo,
					      (struct sk_buff *)sk_queue));

	*err = error;
	return NULL;
}