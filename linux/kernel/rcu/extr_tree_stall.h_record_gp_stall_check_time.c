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
struct TYPE_2__ {unsigned long gp_start; unsigned long jiffies_resched; int /*<<< orphan*/  n_force_qs; int /*<<< orphan*/  n_force_qs_gpstart; int /*<<< orphan*/  jiffies_stall; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long rcu_jiffies_till_stall_check () ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void record_gp_stall_check_time(void)
{
	unsigned long j = jiffies;
	unsigned long j1;

	rcu_state.gp_start = j;
	j1 = rcu_jiffies_till_stall_check();
	/* Record ->gp_start before ->jiffies_stall. */
	smp_store_release(&rcu_state.jiffies_stall, j + j1); /* ^^^ */
	rcu_state.jiffies_resched = j + j1 / 2;
	rcu_state.n_force_qs_gpstart = READ_ONCE(rcu_state.n_force_qs);
}