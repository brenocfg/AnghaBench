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
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct page_frag {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_enter_memory_pressure (struct sock*) ; 
 int /*<<< orphan*/  sk_stream_moderate_sndbuf (struct sock*) ; 
 int /*<<< orphan*/  skb_page_frag_refill (unsigned int,struct page_frag*,int /*<<< orphan*/ ) ; 

bool sk_page_frag_refill(struct sock *sk, struct page_frag *pfrag)
{
	if (likely(skb_page_frag_refill(32U, pfrag, sk->sk_allocation)))
		return true;

	sk_enter_memory_pressure(sk);
	sk_stream_moderate_sndbuf(sk);
	return false;
}