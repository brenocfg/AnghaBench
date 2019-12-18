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
struct sugov_tunables {int /*<<< orphan*/  attr_set; } ;
struct sugov_policy {int /*<<< orphan*/  tunables_hook; struct sugov_tunables* tunables; } ;
struct cpufreq_policy {struct sugov_policy* governor_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_disable_fast_switch (struct cpufreq_policy*) ; 
 int /*<<< orphan*/  global_tunables_lock ; 
 unsigned int gov_attr_set_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sugov_kthread_stop (struct sugov_policy*) ; 
 int /*<<< orphan*/  sugov_policy_free (struct sugov_policy*) ; 
 int /*<<< orphan*/  sugov_tunables_free (struct sugov_tunables*) ; 

__attribute__((used)) static void sugov_exit(struct cpufreq_policy *policy)
{
	struct sugov_policy *sg_policy = policy->governor_data;
	struct sugov_tunables *tunables = sg_policy->tunables;
	unsigned int count;

	mutex_lock(&global_tunables_lock);

	count = gov_attr_set_put(&tunables->attr_set, &sg_policy->tunables_hook);
	policy->governor_data = NULL;
	if (!count)
		sugov_tunables_free(tunables);

	mutex_unlock(&global_tunables_lock);

	sugov_kthread_stop(sg_policy);
	sugov_policy_free(sg_policy);
	cpufreq_disable_fast_switch(policy);
}