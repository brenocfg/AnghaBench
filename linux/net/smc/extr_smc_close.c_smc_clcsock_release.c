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
struct socket {int dummy; } ;
struct smc_sock {int /*<<< orphan*/  clcsock_release_lock; struct socket* clcsock; int /*<<< orphan*/  smc_listen_work; scalar_t__ listen_smc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * current_work () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

void smc_clcsock_release(struct smc_sock *smc)
{
	struct socket *tcp;

	if (smc->listen_smc && current_work() != &smc->smc_listen_work)
		cancel_work_sync(&smc->smc_listen_work);
	mutex_lock(&smc->clcsock_release_lock);
	if (smc->clcsock) {
		tcp = smc->clcsock;
		smc->clcsock = NULL;
		sock_release(tcp);
	}
	mutex_unlock(&smc->clcsock_release_lock);
}