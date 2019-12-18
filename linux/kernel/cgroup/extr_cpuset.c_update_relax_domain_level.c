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
struct cpuset {int relax_domain_level; int /*<<< orphan*/  cpus_allowed; } ;
typedef  int s64 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ is_sched_load_balance (struct cpuset*) ; 
 int /*<<< orphan*/  rebuild_sched_domains_locked () ; 
 int sched_domain_level_max ; 

__attribute__((used)) static int update_relax_domain_level(struct cpuset *cs, s64 val)
{
#ifdef CONFIG_SMP
	if (val < -1 || val >= sched_domain_level_max)
		return -EINVAL;
#endif

	if (val != cs->relax_domain_level) {
		cs->relax_domain_level = val;
		if (!cpumask_empty(cs->cpus_allowed) &&
		    is_sched_load_balance(cs))
			rebuild_sched_domains_locked();
	}

	return 0;
}