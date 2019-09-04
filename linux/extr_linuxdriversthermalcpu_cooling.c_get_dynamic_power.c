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
typedef  int u32 ;
struct cpufreq_cooling_device {int last_load; } ;

/* Variables and functions */
 int cpu_freq_to_power (struct cpufreq_cooling_device*,unsigned long) ; 

__attribute__((used)) static u32 get_dynamic_power(struct cpufreq_cooling_device *cpufreq_cdev,
			     unsigned long freq)
{
	u32 raw_cpu_power;

	raw_cpu_power = cpu_freq_to_power(cpufreq_cdev, freq);
	return (raw_cpu_power * cpufreq_cdev->last_load) / 100;
}