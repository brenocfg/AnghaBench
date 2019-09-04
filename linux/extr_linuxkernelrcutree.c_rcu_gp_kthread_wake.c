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
struct rcu_state {scalar_t__ gp_kthread; int /*<<< orphan*/  gp_wq; int /*<<< orphan*/  gp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  in_serving_softirq () ; 
 int /*<<< orphan*/  swake_up_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_gp_kthread_wake(struct rcu_state *rsp)
{
	if ((current == rsp->gp_kthread &&
	     !in_interrupt() && !in_serving_softirq()) ||
	    !READ_ONCE(rsp->gp_flags) ||
	    !rsp->gp_kthread)
		return;
	swake_up_one(&rsp->gp_wq);
}