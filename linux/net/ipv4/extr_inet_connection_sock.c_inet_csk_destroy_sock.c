#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_state; TYPE_1__* sk_prot; } ;
struct TYPE_6__ {int /*<<< orphan*/  icsk_bind_hash; } ;
struct TYPE_5__ {scalar_t__ inet_num; } ;
struct TYPE_4__ {int /*<<< orphan*/  orphan_count; int /*<<< orphan*/  (* destroy ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ TCP_CLOSE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_3__* inet_csk (struct sock*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_refcnt_debug_release (struct sock*) ; 
 int /*<<< orphan*/  sk_stream_kill_queues (struct sock*) ; 
 int /*<<< orphan*/  sk_unhashed (struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  xfrm_sk_free_policy (struct sock*) ; 

void inet_csk_destroy_sock(struct sock *sk)
{
	WARN_ON(sk->sk_state != TCP_CLOSE);
	WARN_ON(!sock_flag(sk, SOCK_DEAD));

	/* It cannot be in hash table! */
	WARN_ON(!sk_unhashed(sk));

	/* If it has not 0 inet_sk(sk)->inet_num, it must be bound */
	WARN_ON(inet_sk(sk)->inet_num && !inet_csk(sk)->icsk_bind_hash);

	sk->sk_prot->destroy(sk);

	sk_stream_kill_queues(sk);

	xfrm_sk_free_policy(sk);

	sk_refcnt_debug_release(sk);

	percpu_counter_dec(sk->sk_prot->orphan_count);

	sock_put(sk);
}