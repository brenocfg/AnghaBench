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
struct TYPE_2__ {scalar_t__ donetail; scalar_t__ curtail; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 TYPE_1__ rcu_ctrlblk ; 
 int /*<<< orphan*/  rcu_qs () ; 
 int /*<<< orphan*/  set_preempt_need_resched () ; 
 int /*<<< orphan*/  set_tsk_need_resched (int /*<<< orphan*/ ) ; 

void rcu_sched_clock_irq(int user)
{
	if (user) {
		rcu_qs();
	} else if (rcu_ctrlblk.donetail != rcu_ctrlblk.curtail) {
		set_tsk_need_resched(current);
		set_preempt_need_resched();
	}
}