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
struct smc_sock {int /*<<< orphan*/  accept_q_lock; int /*<<< orphan*/  accept_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_acceptq_added (struct sock*) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smc_accept_enqueue(struct sock *parent, struct sock *sk)
{
	struct smc_sock *par = smc_sk(parent);

	sock_hold(sk); /* sock_put in smc_accept_unlink () */
	spin_lock(&par->accept_q_lock);
	list_add_tail(&smc_sk(sk)->accept_q, &par->accept_q);
	spin_unlock(&par->accept_q_lock);
	sk_acceptq_added(parent);
}