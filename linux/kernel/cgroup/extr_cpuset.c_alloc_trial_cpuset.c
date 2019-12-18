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
struct cpuset {int /*<<< orphan*/  effective_cpus; int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ alloc_cpumasks (struct cpuset*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cpuset*) ; 
 struct cpuset* kmemdup (struct cpuset*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cpuset *alloc_trial_cpuset(struct cpuset *cs)
{
	struct cpuset *trial;

	trial = kmemdup(cs, sizeof(*cs), GFP_KERNEL);
	if (!trial)
		return NULL;

	if (alloc_cpumasks(trial, NULL)) {
		kfree(trial);
		return NULL;
	}

	cpumask_copy(trial->cpus_allowed, cs->cpus_allowed);
	cpumask_copy(trial->effective_cpus, cs->effective_cpus);
	return trial;
}