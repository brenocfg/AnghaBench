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
 int EINVAL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_power_off () ; 
 int /*<<< orphan*/  n_rcu_perf_writer_finished ; 
 scalar_t__ nrealwriters ; 
 int /*<<< orphan*/  rcu_perf_cleanup () ; 
 int /*<<< orphan*/  shutdown_wq ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rcu_perf_shutdown(void *arg)
{
	do {
		wait_event(shutdown_wq,
			   atomic_read(&n_rcu_perf_writer_finished) >=
			   nrealwriters);
	} while (atomic_read(&n_rcu_perf_writer_finished) < nrealwriters);
	smp_mb(); /* Wake before output. */
	rcu_perf_cleanup();
	kernel_power_off();
	return -EINVAL;
}