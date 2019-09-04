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
struct cpuset {int /*<<< orphan*/  cpus_allowed; int /*<<< orphan*/  effective_cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cpuset*) ; 
 struct cpuset* kmemdup (struct cpuset*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cpuset *alloc_trial_cpuset(struct cpuset *cs)
{
	struct cpuset *trial;

	trial = kmemdup(cs, sizeof(*cs), GFP_KERNEL);
	if (!trial)
		return NULL;

	if (!alloc_cpumask_var(&trial->cpus_allowed, GFP_KERNEL))
		goto free_cs;
	if (!alloc_cpumask_var(&trial->effective_cpus, GFP_KERNEL))
		goto free_cpus;

	cpumask_copy(trial->cpus_allowed, cs->cpus_allowed);
	cpumask_copy(trial->effective_cpus, cs->effective_cpus);
	return trial;

free_cpus:
	free_cpumask_var(trial->cpus_allowed);
free_cs:
	kfree(trial);
	return NULL;
}