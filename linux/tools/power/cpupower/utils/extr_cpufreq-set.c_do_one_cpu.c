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
struct cpufreq_policy {int /*<<< orphan*/  governor; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int cpufreq_modify_policy_governor (unsigned int,int /*<<< orphan*/ ) ; 
 int cpufreq_modify_policy_max (unsigned int,int /*<<< orphan*/ ) ; 
 int cpufreq_modify_policy_min (unsigned int,int /*<<< orphan*/ ) ; 
 int cpufreq_set_frequency (unsigned int,unsigned long) ; 
 int do_new_policy (unsigned int,struct cpufreq_policy*) ; 

__attribute__((used)) static int do_one_cpu(unsigned int cpu, struct cpufreq_policy *new_pol,
		unsigned long freq, unsigned int pc)
{
	switch (pc) {
	case 0:
		return cpufreq_set_frequency(cpu, freq);

	case 1:
		/* if only one value of a policy is to be changed, we can
		 * use a "fast path".
		 */
		if (new_pol->min)
			return cpufreq_modify_policy_min(cpu, new_pol->min);
		else if (new_pol->max)
			return cpufreq_modify_policy_max(cpu, new_pol->max);
		else if (new_pol->governor)
			return cpufreq_modify_policy_governor(cpu,
							new_pol->governor);

	default:
		/* slow path */
		return do_new_policy(cpu, new_pol);
	}
}