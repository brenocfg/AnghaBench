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
struct sock {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOBUFS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int pfkey_broadcast_one(struct sk_buff *skb, gfp_t allocation,
			       struct sock *sk)
{
	int err = -ENOBUFS;

	if (atomic_read(&sk->sk_rmem_alloc) > sk->sk_rcvbuf)
		return err;

	skb = skb_clone(skb, allocation);

	if (skb) {
		skb_set_owner_r(skb, sk);
		skb_queue_tail(&sk->sk_receive_queue, skb);
		sk->sk_data_ready(sk);
		err = 0;
	}
	return err;
}