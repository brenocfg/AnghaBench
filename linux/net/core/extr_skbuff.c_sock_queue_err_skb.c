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
struct sock {int /*<<< orphan*/  (* sk_error_report ) (struct sock*) ;int /*<<< orphan*/  sk_error_queue; int /*<<< orphan*/  sk_rmem_alloc; int /*<<< orphan*/  sk_rcvbuf; } ;
struct sk_buff {unsigned int truesize; int /*<<< orphan*/  destructor; struct sock* sk; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst_force (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_err_queue (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_rmem_free ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

int sock_queue_err_skb(struct sock *sk, struct sk_buff *skb)
{
	if (atomic_read(&sk->sk_rmem_alloc) + skb->truesize >=
	    (unsigned int)READ_ONCE(sk->sk_rcvbuf))
		return -ENOMEM;

	skb_orphan(skb);
	skb->sk = sk;
	skb->destructor = sock_rmem_free;
	atomic_add(skb->truesize, &sk->sk_rmem_alloc);
	skb_set_err_queue(skb);

	/* before exiting rcu section, make sure dst is refcounted */
	skb_dst_force(skb);

	skb_queue_tail(&sk->sk_error_queue, skb);
	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_error_report(sk);
	return 0;
}