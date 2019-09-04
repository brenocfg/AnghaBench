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
struct rcu_torture {int /*<<< orphan*/  rtort_rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu_sched (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_torture_cb ; 

__attribute__((used)) static void rcu_sched_torture_deferred_free(struct rcu_torture *p)
{
	call_rcu_sched(&p->rtort_rcu, rcu_torture_cb);
}