#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct thermal_zone_device {int dummy; } ;
struct thermal_cooling_device {struct cpufreq_cooling_device* devdata; } ;
struct cpufreq_cooling_device {unsigned long max_level; TYPE_2__* freq_table; TYPE_1__* policy; } ;
struct TYPE_4__ {unsigned int frequency; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpus; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int cpu_freq_to_power (struct cpufreq_cooling_device*,unsigned int) ; 
 unsigned int cpumask_weight (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_state2power(struct thermal_cooling_device *cdev,
			       struct thermal_zone_device *tz,
			       unsigned long state, u32 *power)
{
	unsigned int freq, num_cpus;
	struct cpufreq_cooling_device *cpufreq_cdev = cdev->devdata;

	/* Request state should be less than max_level */
	if (WARN_ON(state > cpufreq_cdev->max_level))
		return -EINVAL;

	num_cpus = cpumask_weight(cpufreq_cdev->policy->cpus);

	freq = cpufreq_cdev->freq_table[state].frequency;
	*power = cpu_freq_to_power(cpufreq_cdev, freq) * num_cpus;

	return 0;
}