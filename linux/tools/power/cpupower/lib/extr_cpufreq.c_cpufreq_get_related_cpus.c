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
struct cpufreq_affected_cpus {int dummy; } ;

/* Variables and functions */
 struct cpufreq_affected_cpus* sysfs_get_cpu_list (unsigned int,char*) ; 

struct cpufreq_affected_cpus *cpufreq_get_related_cpus(unsigned int cpu)
{
	return sysfs_get_cpu_list(cpu, "related_cpus");
}