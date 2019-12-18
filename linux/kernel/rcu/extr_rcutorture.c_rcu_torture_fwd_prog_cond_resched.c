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
 int /*<<< orphan*/  CONFIG_NO_HZ_FULL ; 
 int /*<<< orphan*/  CONFIG_PREEMPT ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void rcu_torture_fwd_prog_cond_resched(unsigned long iter)
{
	if (IS_ENABLED(CONFIG_PREEMPT) && IS_ENABLED(CONFIG_NO_HZ_FULL)) {
		// Real call_rcu() floods hit userspace, so emulate that.
		if (need_resched() || (iter & 0xfff))
			schedule();
	} else {
		// No userspace emulation: CB invocation throttles call_rcu()
		cond_resched();
	}
}