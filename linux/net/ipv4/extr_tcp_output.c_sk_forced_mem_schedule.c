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
struct sock {int sk_forward_alloc; scalar_t__ sk_memcg; } ;

/* Variables and functions */
 int SK_MEM_QUANTUM ; 
 int /*<<< orphan*/  mem_cgroup_charge_skmem (scalar_t__,int) ; 
 scalar_t__ mem_cgroup_sockets_enabled ; 
 int sk_mem_pages (int) ; 
 int /*<<< orphan*/  sk_memory_allocated_add (struct sock*,int) ; 

void sk_forced_mem_schedule(struct sock *sk, int size)
{
	int amt;

	if (size <= sk->sk_forward_alloc)
		return;
	amt = sk_mem_pages(size);
	sk->sk_forward_alloc += amt * SK_MEM_QUANTUM;
	sk_memory_allocated_add(sk, amt);

	if (mem_cgroup_sockets_enabled && sk->sk_memcg)
		mem_cgroup_charge_skmem(sk->sk_memcg, amt);
}