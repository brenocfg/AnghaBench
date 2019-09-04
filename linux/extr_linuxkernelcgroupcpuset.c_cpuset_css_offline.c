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
struct cpuset {int /*<<< orphan*/  flags; } ;
struct cgroup_subsys_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ONLINE ; 
 int /*<<< orphan*/  CS_SCHED_LOAD_BALANCE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuset_dec () ; 
 int /*<<< orphan*/  cpuset_mutex ; 
 struct cpuset* css_cs (struct cgroup_subsys_state*) ; 
 scalar_t__ is_sched_load_balance (struct cpuset*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_flag (int /*<<< orphan*/ ,struct cpuset*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpuset_css_offline(struct cgroup_subsys_state *css)
{
	struct cpuset *cs = css_cs(css);

	mutex_lock(&cpuset_mutex);

	if (is_sched_load_balance(cs))
		update_flag(CS_SCHED_LOAD_BALANCE, cs, 0);

	cpuset_dec();
	clear_bit(CS_ONLINE, &cs->flags);

	mutex_unlock(&cpuset_mutex);
}