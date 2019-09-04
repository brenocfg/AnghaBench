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
struct sk_buff_head {int dummy; } ;
struct sock {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_rmem_alloc; struct sk_buff_head sk_receive_queue; } ;
struct sk_buff {int /*<<< orphan*/  truesize; int /*<<< orphan*/  destructor; struct sock* sk; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_rfree ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_rmem_schedule (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int kcm_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
	struct sk_buff_head *list = &sk->sk_receive_queue;

	if (atomic_read(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf)
		return -ENOMEM;

	if (!sk_rmem_schedule(sk, skb, skb->truesize))
		return -ENOBUFS;

	skb->dev = NULL;

	skb_orphan(skb);
	skb->sk = sk;
	skb->destructor = kcm_rfree;
	atomic_add(skb->truesize, &sk->sk_rmem_alloc);
	sk_mem_charge(sk, skb->truesize);

	skb_queue_tail(list, skb);

	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_ready(sk);

	return 0;
}