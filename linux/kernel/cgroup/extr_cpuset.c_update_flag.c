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
struct cpuset {int /*<<< orphan*/  cpus_allowed; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  cpuset_flagbits_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct cpuset* alloc_trial_cpuset (struct cpuset*) ; 
 int /*<<< orphan*/  callback_lock ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpuset (struct cpuset*) ; 
 scalar_t__ is_sched_load_balance (struct cpuset*) ; 
 scalar_t__ is_spread_page (struct cpuset*) ; 
 scalar_t__ is_spread_slab (struct cpuset*) ; 
 int /*<<< orphan*/  rebuild_sched_domains_locked () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_tasks_flags (struct cpuset*) ; 
 int validate_change (struct cpuset*,struct cpuset*) ; 

__attribute__((used)) static int update_flag(cpuset_flagbits_t bit, struct cpuset *cs,
		       int turning_on)
{
	struct cpuset *trialcs;
	int balance_flag_changed;
	int spread_flag_changed;
	int err;

	trialcs = alloc_trial_cpuset(cs);
	if (!trialcs)
		return -ENOMEM;

	if (turning_on)
		set_bit(bit, &trialcs->flags);
	else
		clear_bit(bit, &trialcs->flags);

	err = validate_change(cs, trialcs);
	if (err < 0)
		goto out;

	balance_flag_changed = (is_sched_load_balance(cs) !=
				is_sched_load_balance(trialcs));

	spread_flag_changed = ((is_spread_slab(cs) != is_spread_slab(trialcs))
			|| (is_spread_page(cs) != is_spread_page(trialcs)));

	spin_lock_irq(&callback_lock);
	cs->flags = trialcs->flags;
	spin_unlock_irq(&callback_lock);

	if (!cpumask_empty(trialcs->cpus_allowed) && balance_flag_changed)
		rebuild_sched_domains_locked();

	if (spread_flag_changed)
		update_tasks_flags(cs);
out:
	free_cpuset(trialcs);
	return err;
}