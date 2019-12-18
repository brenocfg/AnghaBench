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
struct sk_buff_head {int /*<<< orphan*/  lock; int /*<<< orphan*/  prev; } ;
struct sock {struct sk_buff_head sk_receive_queue; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 unsigned int MSG_DONTWAIT ; 
 struct sk_buff* READ_ONCE (int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_try_recv_from_queue (struct sock*,struct sk_buff_head*,unsigned int,void (*) (struct sock*,struct sk_buff*),int*,int*,struct sk_buff**) ; 
 int /*<<< orphan*/  sk_busy_loop (struct sock*,unsigned int) ; 
 int /*<<< orphan*/  sk_can_busy_loop (struct sock*) ; 
 int sock_error (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct sk_buff *__skb_try_recv_datagram(struct sock *sk, unsigned int flags,
					void (*destructor)(struct sock *sk,
							   struct sk_buff *skb),
					int *off, int *err,
					struct sk_buff **last)
{
	struct sk_buff_head *queue = &sk->sk_receive_queue;
	struct sk_buff *skb;
	unsigned long cpu_flags;
	/*
	 * Caller is allowed not to check sk->sk_err before skb_recv_datagram()
	 */
	int error = sock_error(sk);

	if (error)
		goto no_packet;

	do {
		/* Again only user level code calls this function, so nothing
		 * interrupt level will suddenly eat the receive_queue.
		 *
		 * Look at current nfs client by the way...
		 * However, this function was correct in any case. 8)
		 */
		spin_lock_irqsave(&queue->lock, cpu_flags);
		skb = __skb_try_recv_from_queue(sk, queue, flags, destructor,
						off, &error, last);
		spin_unlock_irqrestore(&queue->lock, cpu_flags);
		if (error)
			goto no_packet;
		if (skb)
			return skb;

		if (!sk_can_busy_loop(sk))
			break;

		sk_busy_loop(sk, flags & MSG_DONTWAIT);
	} while (READ_ONCE(sk->sk_receive_queue.prev) != *last);

	error = -EAGAIN;

no_packet:
	*err = error;
	return NULL;
}