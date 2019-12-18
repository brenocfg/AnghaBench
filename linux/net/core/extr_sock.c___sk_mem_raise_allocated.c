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
typedef  long u64 ;
struct sock {scalar_t__ sk_type; int sk_wmem_queued; scalar_t__ sk_forward_alloc; scalar_t__ sk_sndbuf; scalar_t__ sk_memcg; int /*<<< orphan*/  sk_rmem_alloc; int /*<<< orphan*/  sk_wmem_alloc; struct proto* sk_prot; } ;
struct proto {int dummy; } ;

/* Variables and functions */
 int SK_MEM_RECV ; 
 int SK_MEM_SEND ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int mem_cgroup_charge_skmem (scalar_t__,int) ; 
 scalar_t__ mem_cgroup_sockets_enabled ; 
 int /*<<< orphan*/  mem_cgroup_uncharge_skmem (scalar_t__,int) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_enter_memory_pressure (struct sock*) ; 
 scalar_t__ sk_get_rmem0 (struct sock*,struct proto*) ; 
 int sk_get_wmem0 (struct sock*,struct proto*) ; 
 scalar_t__ sk_has_memory_pressure (struct sock*) ; 
 int /*<<< orphan*/  sk_leave_memory_pressure (struct sock*) ; 
 long sk_mem_pages (scalar_t__) ; 
 long sk_memory_allocated_add (struct sock*,int) ; 
 int /*<<< orphan*/  sk_memory_allocated_sub (struct sock*,int) ; 
 long sk_prot_mem_limits (struct sock*,int) ; 
 long sk_sockets_allocated_read_positive (struct sock*) ; 
 int /*<<< orphan*/  sk_stream_moderate_sndbuf (struct sock*) ; 
 int /*<<< orphan*/  sk_under_memory_pressure (struct sock*) ; 
 int /*<<< orphan*/  trace_sock_exceed_buf_limit (struct sock*,struct proto*,long,int) ; 

int __sk_mem_raise_allocated(struct sock *sk, int size, int amt, int kind)
{
	struct proto *prot = sk->sk_prot;
	long allocated = sk_memory_allocated_add(sk, amt);
	bool charged = true;

	if (mem_cgroup_sockets_enabled && sk->sk_memcg &&
	    !(charged = mem_cgroup_charge_skmem(sk->sk_memcg, amt)))
		goto suppress_allocation;

	/* Under limit. */
	if (allocated <= sk_prot_mem_limits(sk, 0)) {
		sk_leave_memory_pressure(sk);
		return 1;
	}

	/* Under pressure. */
	if (allocated > sk_prot_mem_limits(sk, 1))
		sk_enter_memory_pressure(sk);

	/* Over hard limit. */
	if (allocated > sk_prot_mem_limits(sk, 2))
		goto suppress_allocation;

	/* guarantee minimum buffer size under pressure */
	if (kind == SK_MEM_RECV) {
		if (atomic_read(&sk->sk_rmem_alloc) < sk_get_rmem0(sk, prot))
			return 1;

	} else { /* SK_MEM_SEND */
		int wmem0 = sk_get_wmem0(sk, prot);

		if (sk->sk_type == SOCK_STREAM) {
			if (sk->sk_wmem_queued < wmem0)
				return 1;
		} else if (refcount_read(&sk->sk_wmem_alloc) < wmem0) {
				return 1;
		}
	}

	if (sk_has_memory_pressure(sk)) {
		u64 alloc;

		if (!sk_under_memory_pressure(sk))
			return 1;
		alloc = sk_sockets_allocated_read_positive(sk);
		if (sk_prot_mem_limits(sk, 2) > alloc *
		    sk_mem_pages(sk->sk_wmem_queued +
				 atomic_read(&sk->sk_rmem_alloc) +
				 sk->sk_forward_alloc))
			return 1;
	}

suppress_allocation:

	if (kind == SK_MEM_SEND && sk->sk_type == SOCK_STREAM) {
		sk_stream_moderate_sndbuf(sk);

		/* Fail only if socket is _under_ its sndbuf.
		 * In this case we cannot block, so that we have to fail.
		 */
		if (sk->sk_wmem_queued + size >= sk->sk_sndbuf)
			return 1;
	}

	if (kind == SK_MEM_SEND || (kind == SK_MEM_RECV && charged))
		trace_sock_exceed_buf_limit(sk, prot, allocated, kind);

	sk_memory_allocated_sub(sk, amt);

	if (mem_cgroup_sockets_enabled && sk->sk_memcg)
		mem_cgroup_uncharge_skmem(sk->sk_memcg, amt);

	return 0;
}