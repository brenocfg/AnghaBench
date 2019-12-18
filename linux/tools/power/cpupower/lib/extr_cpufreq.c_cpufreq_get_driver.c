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
 int /*<<< orphan*/  SCALING_DRIVER ; 
 char* sysfs_cpufreq_get_one_string (unsigned int,int /*<<< orphan*/ ) ; 

char *cpufreq_get_driver(unsigned int cpu)
{
	return sysfs_cpufreq_get_one_string(cpu, SCALING_DRIVER);
}