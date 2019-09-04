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
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct smap_psock {int /*<<< orphan*/  rcu; int /*<<< orphan*/  state; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMAP_TX_RUNNING ; 
 int /*<<< orphan*/  call_rcu_sched (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ psock_is_smap_sk (struct sock*) ; 
 int /*<<< orphan*/  rcu_assign_sk_user_data (struct sock*,int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smap_destroy_psock ; 
 int /*<<< orphan*/  smap_stop_sock (struct smap_psock*,struct sock*) ; 
 int /*<<< orphan*/  tcp_cleanup_ulp (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smap_release_sock(struct smap_psock *psock, struct sock *sock)
{
	if (refcount_dec_and_test(&psock->refcnt)) {
		if (psock_is_smap_sk(sock))
			tcp_cleanup_ulp(sock);
		write_lock_bh(&sock->sk_callback_lock);
		smap_stop_sock(psock, sock);
		write_unlock_bh(&sock->sk_callback_lock);
		clear_bit(SMAP_TX_RUNNING, &psock->state);
		rcu_assign_sk_user_data(sock, NULL);
		call_rcu_sched(&psock->rcu, smap_destroy_psock);
	}
}