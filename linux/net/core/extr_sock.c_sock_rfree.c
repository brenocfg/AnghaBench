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
struct sock {int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {unsigned int truesize; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,unsigned int) ; 

void sock_rfree(struct sk_buff *skb)
{
	struct sock *sk = skb->sk;
	unsigned int len = skb->truesize;

	atomic_sub(len, &sk->sk_rmem_alloc);
	sk_mem_uncharge(sk, len);
}