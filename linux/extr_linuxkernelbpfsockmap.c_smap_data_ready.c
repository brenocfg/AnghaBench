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
struct smap_psock {int /*<<< orphan*/  strp; } ;

/* Variables and functions */
 scalar_t__ likely (struct smap_psock*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 int /*<<< orphan*/  strp_data_ready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smap_data_ready(struct sock *sk)
{
	struct smap_psock *psock;

	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (likely(psock)) {
		write_lock_bh(&sk->sk_callback_lock);
		strp_data_ready(&psock->strp);
		write_unlock_bh(&sk->sk_callback_lock);
	}
	rcu_read_unlock();
}