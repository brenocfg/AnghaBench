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
struct TYPE_2__ {scalar_t__ gp_kthread; int /*<<< orphan*/  gp_wq; int /*<<< orphan*/  gp_seq; int /*<<< orphan*/  gp_wake_seq; int /*<<< orphan*/  gp_wake_time; int /*<<< orphan*/  gp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  in_serving_softirq () ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_1__ rcu_state ; 
 int /*<<< orphan*/  swake_up_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcu_gp_kthread_wake(void)
{
	if ((current == rcu_state.gp_kthread &&
	     !in_irq() && !in_serving_softirq()) ||
	    !READ_ONCE(rcu_state.gp_flags) ||
	    !rcu_state.gp_kthread)
		return;
	WRITE_ONCE(rcu_state.gp_wake_time, jiffies);
	WRITE_ONCE(rcu_state.gp_wake_seq, READ_ONCE(rcu_state.gp_seq));
	swake_up_one(&rcu_state.gp_wq);
}