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
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ sysfs__read_int (char*,int*) ; 
 int sysfs__read_ull (char*,unsigned long long*) ; 

int cpu__get_max_freq(unsigned long long *freq)
{
	char entry[PATH_MAX];
	int cpu;

	if (sysfs__read_int("devices/system/cpu/online", &cpu) < 0)
		return -1;

	snprintf(entry, sizeof(entry),
		 "devices/system/cpu/cpu%d/cpufreq/cpuinfo_max_freq", cpu);

	return sysfs__read_ull(entry, freq);
}