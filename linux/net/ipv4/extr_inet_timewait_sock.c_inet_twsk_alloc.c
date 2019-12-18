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
struct sock {int /*<<< orphan*/  sk_cookie; TYPE_2__* sk_prot_creator; int /*<<< orphan*/  sk_hash; int /*<<< orphan*/  sk_reuseport; int /*<<< orphan*/  sk_reuse; int /*<<< orphan*/  sk_family; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct inet_timewait_sock {int tw_substate; TYPE_2__* tw_prot; int /*<<< orphan*/  tw_refcnt; int /*<<< orphan*/  tw_timer; int /*<<< orphan*/  tw_cookie; int /*<<< orphan*/  tw_transparent; scalar_t__ tw_ipv6only; int /*<<< orphan*/  tw_hash; int /*<<< orphan*/  tw_reuseport; int /*<<< orphan*/  tw_reuse; int /*<<< orphan*/  tw_family; int /*<<< orphan*/  tw_dport; int /*<<< orphan*/  tw_sport; int /*<<< orphan*/  tw_state; int /*<<< orphan*/  tw_num; int /*<<< orphan*/  tw_tos; int /*<<< orphan*/  tw_bound_dev_if; int /*<<< orphan*/  tw_rcv_saddr; int /*<<< orphan*/  tw_daddr; struct inet_timewait_death_row* tw_dr; } ;
struct inet_timewait_death_row {scalar_t__ sysctl_max_tw_buckets; int /*<<< orphan*/  tw_count; } ;
struct inet_sock {int /*<<< orphan*/  transparent; int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_sport; int /*<<< orphan*/  inet_num; int /*<<< orphan*/  tos; int /*<<< orphan*/  inet_rcv_saddr; int /*<<< orphan*/  inet_daddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; TYPE_1__* twsk_prot; } ;
struct TYPE_3__ {int /*<<< orphan*/  twsk_slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TCP_TIME_WAIT ; 
 int /*<<< orphan*/  TIMER_PINNED ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct inet_sock* inet_sk (struct sock const*) ; 
 struct inet_timewait_sock* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock const*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_timer_handler ; 
 int /*<<< orphan*/  twsk_net_set (struct inet_timewait_sock*,int /*<<< orphan*/ ) ; 

struct inet_timewait_sock *inet_twsk_alloc(const struct sock *sk,
					   struct inet_timewait_death_row *dr,
					   const int state)
{
	struct inet_timewait_sock *tw;

	if (atomic_read(&dr->tw_count) >= dr->sysctl_max_tw_buckets)
		return NULL;

	tw = kmem_cache_alloc(sk->sk_prot_creator->twsk_prot->twsk_slab,
			      GFP_ATOMIC);
	if (tw) {
		const struct inet_sock *inet = inet_sk(sk);

		tw->tw_dr	    = dr;
		/* Give us an identity. */
		tw->tw_daddr	    = inet->inet_daddr;
		tw->tw_rcv_saddr    = inet->inet_rcv_saddr;
		tw->tw_bound_dev_if = sk->sk_bound_dev_if;
		tw->tw_tos	    = inet->tos;
		tw->tw_num	    = inet->inet_num;
		tw->tw_state	    = TCP_TIME_WAIT;
		tw->tw_substate	    = state;
		tw->tw_sport	    = inet->inet_sport;
		tw->tw_dport	    = inet->inet_dport;
		tw->tw_family	    = sk->sk_family;
		tw->tw_reuse	    = sk->sk_reuse;
		tw->tw_reuseport    = sk->sk_reuseport;
		tw->tw_hash	    = sk->sk_hash;
		tw->tw_ipv6only	    = 0;
		tw->tw_transparent  = inet->transparent;
		tw->tw_prot	    = sk->sk_prot_creator;
		atomic64_set(&tw->tw_cookie, atomic64_read(&sk->sk_cookie));
		twsk_net_set(tw, sock_net(sk));
		timer_setup(&tw->tw_timer, tw_timer_handler, TIMER_PINNED);
		/*
		 * Because we use RCU lookups, we should not set tw_refcnt
		 * to a non null value before everything is setup for this
		 * timewait socket.
		 */
		refcount_set(&tw->tw_refcnt, 0);

		__module_get(tw->tw_prot->owner);
	}

	return tw;
}