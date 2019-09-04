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
struct TYPE_2__ {int /*<<< orphan*/  gp_seq; } ;

/* Variables and functions */
 TYPE_1__ rcu_sched_state ; 
 int /*<<< orphan*/  rcu_seq_done (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  synchronize_sched () ; 

void cond_synchronize_sched(unsigned long oldstate)
{
	if (!rcu_seq_done(&rcu_sched_state.gp_seq, oldstate))
		synchronize_sched();
	else
		smp_mb(); /* Ensure GP ends before subsequent accesses. */
}