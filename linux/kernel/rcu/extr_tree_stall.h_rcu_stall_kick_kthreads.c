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
struct TYPE_2__ {int /*<<< orphan*/  jiffies_kick_kthreads; scalar_t__ gp_kthread; int /*<<< orphan*/  name; int /*<<< orphan*/  gp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_ALL ; 
 scalar_t__ HZ ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rcu_ftrace_dump (int /*<<< orphan*/ ) ; 
 scalar_t__ rcu_gp_in_progress () ; 
 int /*<<< orphan*/  rcu_kick_kthreads ; 
 TYPE_1__ rcu_state ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static void rcu_stall_kick_kthreads(void)
{
	unsigned long j;

	if (!rcu_kick_kthreads)
		return;
	j = READ_ONCE(rcu_state.jiffies_kick_kthreads);
	if (time_after(jiffies, j) && rcu_state.gp_kthread &&
	    (rcu_gp_in_progress() || READ_ONCE(rcu_state.gp_flags))) {
		WARN_ONCE(1, "Kicking %s grace-period kthread\n",
			  rcu_state.name);
		rcu_ftrace_dump(DUMP_ALL);
		wake_up_process(rcu_state.gp_kthread);
		WRITE_ONCE(rcu_state.jiffies_kick_kthreads, j + HZ);
	}
}