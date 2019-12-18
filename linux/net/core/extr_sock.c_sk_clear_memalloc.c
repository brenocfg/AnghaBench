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

/* Variables and functions */
 int /*<<< orphan*/  SOCK_MEMALLOC ; 
 int /*<<< orphan*/  __GFP_MEMALLOC ; 
 int /*<<< orphan*/  memalloc_socks_key ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_branch_dec (int /*<<< orphan*/ *) ; 

void sk_clear_memalloc(struct sock *sk)
{
	sock_reset_flag(sk, SOCK_MEMALLOC);
	sk->sk_allocation &= ~__GFP_MEMALLOC;
	static_branch_dec(&memalloc_socks_key);

	/*
	 * SOCK_MEMALLOC is allowed to ignore rmem limits to ensure forward
	 * progress of swapping. SOCK_MEMALLOC may be cleared while
	 * it has rmem allocations due to the last swapfile being deactivated
	 * but there is a risk that the socket is unusable due to exceeding
	 * the rmem limits. Reclaim the reserves and obey rmem limits again.
	 */
	sk_mem_reclaim(sk);
}