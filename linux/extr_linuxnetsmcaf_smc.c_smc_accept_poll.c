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
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct smc_sock* smc_sk (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t smc_accept_poll(struct sock *parent)
{
	struct smc_sock *isk = smc_sk(parent);
	__poll_t mask = 0;

	spin_lock(&isk->accept_q_lock);
	if (!list_empty(&isk->accept_q))
		mask = EPOLLIN | EPOLLRDNORM;
	spin_unlock(&isk->accept_q_lock);

	return mask;
}