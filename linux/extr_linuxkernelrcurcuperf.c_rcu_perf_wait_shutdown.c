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

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched_tasks_rcu_qs () ; 
 int /*<<< orphan*/  n_rcu_perf_writer_finished ; 
 scalar_t__ nrealwriters ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  torture_must_stop () ; 

__attribute__((used)) static void rcu_perf_wait_shutdown(void)
{
	cond_resched_tasks_rcu_qs();
	if (atomic_read(&n_rcu_perf_writer_finished) < nrealwriters)
		return;
	while (!torture_must_stop())
		schedule_timeout_uninterruptible(1);
}