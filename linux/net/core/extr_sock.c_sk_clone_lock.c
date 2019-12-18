#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
struct sock {int sk_userlocks; int sk_flags; TYPE_2__* sk_prot; int /*<<< orphan*/  sk_wq; int /*<<< orphan*/  sk_refcnt; int /*<<< orphan*/  sk_net_refcnt; int /*<<< orphan*/  sk_incoming_cpu; scalar_t__ sk_priority; scalar_t__ sk_err_soft; scalar_t__ sk_err; int /*<<< orphan*/  sk_reuseport_cb; int /*<<< orphan*/  sk_filter; int /*<<< orphan*/  sk_cgrp_data; int /*<<< orphan*/  sk_zckey; int /*<<< orphan*/ * sk_send_head; int /*<<< orphan*/  sk_drops; scalar_t__ sk_forward_alloc; scalar_t__ sk_wmem_queued; scalar_t__ sk_dst_pending_confirm; int /*<<< orphan*/ * sk_dst_cache; int /*<<< orphan*/  sk_omem_alloc; int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_rmem_alloc; TYPE_1__ sk_backlog; int /*<<< orphan*/  sk_node; TYPE_2__* sk_prot_creator; int /*<<< orphan*/  sk_family; } ;
struct sk_filter {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {scalar_t__ sockets_allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct sk_filter*) ; 
 int SK_FLAGS_TIMESTAMP ; 
 int SOCK_BINDPORT_LOCK ; 
 int /*<<< orphan*/  SOCK_DONE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 scalar_t__ bpf_sk_storage_clone (struct sock const*,struct sock*) ; 
 int /*<<< orphan*/  cgroup_sk_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_net (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_cgroup_sk_alloc (struct sock*) ; 
 int /*<<< orphan*/  net_enable_timestamp () ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 struct sk_filter* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int sk_filter_charge (struct sock*,struct sk_filter*) ; 
 int /*<<< orphan*/  sk_free_unlock_clone (struct sock*) ; 
 int /*<<< orphan*/  sk_init_common (struct sock*) ; 
 int /*<<< orphan*/  sk_node_init (int /*<<< orphan*/ *) ; 
 struct sock* sk_prot_alloc (TYPE_2__*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_refcnt_debug_inc (struct sock*) ; 
 int /*<<< orphan*/  sk_set_socket (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_sockets_allocated_inc (struct sock*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  sock_copy (struct sock*,struct sock const*) ; 
 int /*<<< orphan*/  sock_inuse_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_lock_init (struct sock*) ; 
 scalar_t__ sock_needs_netstamp (struct sock const*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xfrm_sk_clone_policy (struct sock*,struct sock const*) ; 

struct sock *sk_clone_lock(const struct sock *sk, const gfp_t priority)
{
	struct sock *newsk;
	bool is_charged = true;

	newsk = sk_prot_alloc(sk->sk_prot, priority, sk->sk_family);
	if (newsk != NULL) {
		struct sk_filter *filter;

		sock_copy(newsk, sk);

		newsk->sk_prot_creator = sk->sk_prot;

		/* SANITY */
		if (likely(newsk->sk_net_refcnt))
			get_net(sock_net(newsk));
		sk_node_init(&newsk->sk_node);
		sock_lock_init(newsk);
		bh_lock_sock(newsk);
		newsk->sk_backlog.head	= newsk->sk_backlog.tail = NULL;
		newsk->sk_backlog.len = 0;

		atomic_set(&newsk->sk_rmem_alloc, 0);
		/*
		 * sk_wmem_alloc set to one (see sk_free() and sock_wfree())
		 */
		refcount_set(&newsk->sk_wmem_alloc, 1);
		atomic_set(&newsk->sk_omem_alloc, 0);
		sk_init_common(newsk);

		newsk->sk_dst_cache	= NULL;
		newsk->sk_dst_pending_confirm = 0;
		newsk->sk_wmem_queued	= 0;
		newsk->sk_forward_alloc = 0;
		atomic_set(&newsk->sk_drops, 0);
		newsk->sk_send_head	= NULL;
		newsk->sk_userlocks	= sk->sk_userlocks & ~SOCK_BINDPORT_LOCK;
		atomic_set(&newsk->sk_zckey, 0);

		sock_reset_flag(newsk, SOCK_DONE);
		mem_cgroup_sk_alloc(newsk);
		cgroup_sk_alloc(&newsk->sk_cgrp_data);

		rcu_read_lock();
		filter = rcu_dereference(sk->sk_filter);
		if (filter != NULL)
			/* though it's an empty new sock, the charging may fail
			 * if sysctl_optmem_max was changed between creation of
			 * original socket and cloning
			 */
			is_charged = sk_filter_charge(newsk, filter);
		RCU_INIT_POINTER(newsk->sk_filter, filter);
		rcu_read_unlock();

		if (unlikely(!is_charged || xfrm_sk_clone_policy(newsk, sk))) {
			/* We need to make sure that we don't uncharge the new
			 * socket if we couldn't charge it in the first place
			 * as otherwise we uncharge the parent's filter.
			 */
			if (!is_charged)
				RCU_INIT_POINTER(newsk->sk_filter, NULL);
			sk_free_unlock_clone(newsk);
			newsk = NULL;
			goto out;
		}
		RCU_INIT_POINTER(newsk->sk_reuseport_cb, NULL);

		if (bpf_sk_storage_clone(sk, newsk)) {
			sk_free_unlock_clone(newsk);
			newsk = NULL;
			goto out;
		}

		newsk->sk_err	   = 0;
		newsk->sk_err_soft = 0;
		newsk->sk_priority = 0;
		newsk->sk_incoming_cpu = raw_smp_processor_id();
		if (likely(newsk->sk_net_refcnt))
			sock_inuse_add(sock_net(newsk), 1);

		/*
		 * Before updating sk_refcnt, we must commit prior changes to memory
		 * (Documentation/RCU/rculist_nulls.txt for details)
		 */
		smp_wmb();
		refcount_set(&newsk->sk_refcnt, 2);

		/*
		 * Increment the counter in the same struct proto as the master
		 * sock (sk_refcnt_debug_inc uses newsk->sk_prot->socks, that
		 * is the same as sk->sk_prot->socks, as this field was copied
		 * with memcpy).
		 *
		 * This _changes_ the previous behaviour, where
		 * tcp_create_openreq_child always was incrementing the
		 * equivalent to tcp_prot->socks (inet_sock_nr), so this have
		 * to be taken into account in all callers. -acme
		 */
		sk_refcnt_debug_inc(newsk);
		sk_set_socket(newsk, NULL);
		RCU_INIT_POINTER(newsk->sk_wq, NULL);

		if (newsk->sk_prot->sockets_allocated)
			sk_sockets_allocated_inc(newsk);

		if (sock_needs_netstamp(sk) &&
		    newsk->sk_flags & SK_FLAGS_TIMESTAMP)
			net_enable_timestamp();
	}
out:
	return newsk;
}