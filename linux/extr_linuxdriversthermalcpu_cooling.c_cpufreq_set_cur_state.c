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
struct thermal_cooling_device {struct cpufreq_cooling_device* devdata; } ;
struct cpufreq_cooling_device {unsigned long max_level; unsigned long cpufreq_state; unsigned int clipped_freq; TYPE_1__* policy; TYPE_2__* freq_table; } ;
struct TYPE_4__ {unsigned int frequency; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cpufreq_update_policy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpufreq_set_cur_state(struct thermal_cooling_device *cdev,
				 unsigned long state)
{
	struct cpufreq_cooling_device *cpufreq_cdev = cdev->devdata;
	unsigned int clip_freq;

	/* Request state should be less than max_level */
	if (WARN_ON(state > cpufreq_cdev->max_level))
		return -EINVAL;

	/* Check if the old cooling action is same as new cooling action */
	if (cpufreq_cdev->cpufreq_state == state)
		return 0;

	clip_freq = cpufreq_cdev->freq_table[state].frequency;
	cpufreq_cdev->cpufreq_state = state;
	cpufreq_cdev->clipped_freq = clip_freq;

	cpufreq_update_policy(cpufreq_cdev->policy->cpu);

	return 0;
}