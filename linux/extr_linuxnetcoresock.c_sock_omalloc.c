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
struct sock {int /*<<< orphan*/  sk_omem_alloc; } ;
struct sk_buff {int /*<<< orphan*/  destructor; struct sock* sk; int /*<<< orphan*/  truesize; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ SKB_TRUESIZE (unsigned long) ; 
 struct sk_buff* alloc_skb (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_ofree ; 
 scalar_t__ sysctl_optmem_max ; 

struct sk_buff *sock_omalloc(struct sock *sk, unsigned long size,
			     gfp_t priority)
{
	struct sk_buff *skb;

	/* small safe race: SKB_TRUESIZE may differ from final skb->truesize */
	if (atomic_read(&sk->sk_omem_alloc) + SKB_TRUESIZE(size) >
	    sysctl_optmem_max)
		return NULL;

	skb = alloc_skb(size, priority);
	if (!skb)
		return NULL;

	atomic_add(skb->truesize, &sk->sk_omem_alloc);
	skb->sk = sk;
	skb->destructor = sock_ofree;
	return skb;
}