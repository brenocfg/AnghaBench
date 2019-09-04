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

__attribute__((used)) static void module_assert_mutex_or_preempt(void)
{
#ifdef CONFIG_LOCKDEP
	if (unlikely(!debug_locks))
		return;

	WARN_ON_ONCE(!rcu_read_lock_sched_held() &&
		!lockdep_is_held(&module_mutex));
#endif
}