#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct smc_sock {int /*<<< orphan*/  sk; int /*<<< orphan*/  accept_q_lock; } ;
struct TYPE_2__ {struct smc_sock* listen_smc; int /*<<< orphan*/  accept_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_acceptq_removed (int /*<<< orphan*/ *) ; 
 TYPE_1__* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smc_accept_unlink(struct sock *sk)
{
	struct smc_sock *par = smc_sk(sk)->listen_smc;

	spin_lock(&par->accept_q_lock);
	list_del_init(&smc_sk(sk)->accept_q);
	spin_unlock(&par->accept_q_lock);
	sk_acceptq_removed(&smc_sk(sk)->listen_smc->sk);
	sock_put(sk); /* sock_hold in smc_accept_enqueue */
}