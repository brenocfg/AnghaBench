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

/* Variables and functions */
 int /*<<< orphan*/  CPUINFO_CUR_FREQ ; 
 unsigned long sysfs_cpufreq_get_one_value (unsigned int,int /*<<< orphan*/ ) ; 

unsigned long cpufreq_get_freq_hardware(unsigned int cpu)
{
	return sysfs_cpufreq_get_one_value(cpu, CPUINFO_CUR_FREQ);
}