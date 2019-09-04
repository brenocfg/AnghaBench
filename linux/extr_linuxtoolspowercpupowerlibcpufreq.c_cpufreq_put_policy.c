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
struct cpufreq_policy {struct cpufreq_policy* governor; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cpufreq_policy*) ; 

void cpufreq_put_policy(struct cpufreq_policy *policy)
{
	if ((!policy) || (!policy->governor))
		return;

	free(policy->governor);
	policy->governor = NULL;
	free(policy);
}