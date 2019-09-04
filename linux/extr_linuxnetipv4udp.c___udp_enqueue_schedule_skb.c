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
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sock {int sk_rcvbuf; int sk_forward_alloc; int /*<<< orphan*/  sk_drops; int /*<<< orphan*/  sk_rmem_alloc; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;struct sk_buff_head sk_receive_queue; } ;
struct sk_buff {int truesize; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int SK_MEM_QUANTUM_SHIFT ; 
 int /*<<< orphan*/  SK_MEM_RECV ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  __sk_mem_raise_allocated (struct sock*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * busylock_acquire (struct sock*) ; 
 int /*<<< orphan*/  busylock_release (int /*<<< orphan*/ *) ; 
 int sk_mem_pages (int) ; 
 int /*<<< orphan*/  skb_condense (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_skb_set_dropcount (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  udp_set_dev_scratch (struct sk_buff*) ; 

int __udp_enqueue_schedule_skb(struct sock *sk, struct sk_buff *skb)
{
	struct sk_buff_head *list = &sk->sk_receive_queue;
	int rmem, delta, amt, err = -ENOMEM;
	spinlock_t *busy = NULL;
	int size;

	/* try to avoid the costly atomic add/sub pair when the receive
	 * queue is full; always allow at least a packet
	 */
	rmem = atomic_read(&sk->sk_rmem_alloc);
	if (rmem > sk->sk_rcvbuf)
		goto drop;

	/* Under mem pressure, it might be helpful to help udp_recvmsg()
	 * having linear skbs :
	 * - Reduce memory overhead and thus increase receive queue capacity
	 * - Less cache line misses at copyout() time
	 * - Less work at consume_skb() (less alien page frag freeing)
	 */
	if (rmem > (sk->sk_rcvbuf >> 1)) {
		skb_condense(skb);

		busy = busylock_acquire(sk);
	}
	size = skb->truesize;
	udp_set_dev_scratch(skb);

	/* we drop only if the receive buf is full and the receive
	 * queue contains some other skb
	 */
	rmem = atomic_add_return(size, &sk->sk_rmem_alloc);
	if (rmem > (size + sk->sk_rcvbuf))
		goto uncharge_drop;

	spin_lock(&list->lock);
	if (size >= sk->sk_forward_alloc) {
		amt = sk_mem_pages(size);
		delta = amt << SK_MEM_QUANTUM_SHIFT;
		if (!__sk_mem_raise_allocated(sk, delta, amt, SK_MEM_RECV)) {
			err = -ENOBUFS;
			spin_unlock(&list->lock);
			goto uncharge_drop;
		}

		sk->sk_forward_alloc += delta;
	}

	sk->sk_forward_alloc -= size;

	/* no need to setup a destructor, we will explicitly release the
	 * forward allocated memory on dequeue
	 */
	sock_skb_set_dropcount(sk, skb);

	__skb_queue_tail(list, skb);
	spin_unlock(&list->lock);

	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_ready(sk);

	busylock_release(busy);
	return 0;

uncharge_drop:
	atomic_sub(skb->truesize, &sk->sk_rmem_alloc);

drop:
	atomic_inc(&sk->sk_drops);
	busylock_release(busy);
	return err;
}