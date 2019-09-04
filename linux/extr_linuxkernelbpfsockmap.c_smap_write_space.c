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
struct sock {int dummy; } ;
struct smap_psock {void (* save_write_space ) (struct sock*) ;int /*<<< orphan*/  tx_work; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMAP_TX_RUNNING ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct smap_psock* smap_psock_sk (struct sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smap_write_space(struct sock *sk)
{
	struct smap_psock *psock;
	void (*write_space)(struct sock *sk);

	rcu_read_lock();
	psock = smap_psock_sk(sk);
	if (likely(psock && test_bit(SMAP_TX_RUNNING, &psock->state)))
		schedule_work(&psock->tx_work);
	write_space = psock->save_write_space;
	rcu_read_unlock();
	write_space(sk);
}