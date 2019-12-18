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
struct udp_sock {int forward_deficit; int /*<<< orphan*/  reader_queue; } ;
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sock {int sk_rcvbuf; int sk_forward_alloc; int /*<<< orphan*/  sk_rmem_alloc; struct sk_buff_head sk_receive_queue; } ;

/* Variables and functions */
 int SK_MEM_QUANTUM ; 
 int SK_MEM_QUANTUM_SHIFT ; 
 int /*<<< orphan*/  __sk_mem_reduce_allocated (struct sock*,int) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct udp_sock* udp_sk (struct sock*) ; 

__attribute__((used)) static void udp_rmem_release(struct sock *sk, int size, int partial,
			     bool rx_queue_lock_held)
{
	struct udp_sock *up = udp_sk(sk);
	struct sk_buff_head *sk_queue;
	int amt;

	if (likely(partial)) {
		up->forward_deficit += size;
		size = up->forward_deficit;
		if (size < (sk->sk_rcvbuf >> 2))
			return;
	} else {
		size += up->forward_deficit;
	}
	up->forward_deficit = 0;

	/* acquire the sk_receive_queue for fwd allocated memory scheduling,
	 * if the called don't held it already
	 */
	sk_queue = &sk->sk_receive_queue;
	if (!rx_queue_lock_held)
		spin_lock(&sk_queue->lock);


	sk->sk_forward_alloc += size;
	amt = (sk->sk_forward_alloc - partial) & ~(SK_MEM_QUANTUM - 1);
	sk->sk_forward_alloc -= amt;

	if (amt)
		__sk_mem_reduce_allocated(sk, amt >> SK_MEM_QUANTUM_SHIFT);

	atomic_sub(size, &sk->sk_rmem_alloc);

	/* this can save us from acquiring the rx queue lock on next receive */
	skb_queue_splice_tail_init(sk_queue, &up->reader_queue);

	if (!rx_queue_lock_held)
		spin_unlock(&sk_queue->lock);
}