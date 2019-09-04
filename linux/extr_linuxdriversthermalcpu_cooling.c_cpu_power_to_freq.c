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
typedef  scalar_t__ u32 ;
struct freq_table {scalar_t__ power; scalar_t__ frequency; } ;
struct cpufreq_cooling_device {int max_level; struct freq_table* freq_table; } ;

/* Variables and functions */

__attribute__((used)) static u32 cpu_power_to_freq(struct cpufreq_cooling_device *cpufreq_cdev,
			     u32 power)
{
	int i;
	struct freq_table *freq_table = cpufreq_cdev->freq_table;

	for (i = 1; i <= cpufreq_cdev->max_level; i++)
		if (power > freq_table[i].power)
			break;

	return freq_table[i - 1].frequency;
}