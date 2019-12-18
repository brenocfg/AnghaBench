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
typedef  int /*<<< orphan*/  linebuf ;
typedef  enum cpufreq_value { ____Placeholder_cpufreq_value } cpufreq_value ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int MAX_CPUFREQ_VALUE_READ_FILES ; 
 int MAX_LINE_LEN ; 
 int /*<<< orphan*/ * cpufreq_value_files ; 
 scalar_t__ errno ; 
 unsigned long strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 unsigned int sysfs_cpufreq_read_file (unsigned int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static unsigned long sysfs_cpufreq_get_one_value(unsigned int cpu,
						 enum cpufreq_value which)
{
	unsigned long value;
	unsigned int len;
	char linebuf[MAX_LINE_LEN];
	char *endp;

	if (which >= MAX_CPUFREQ_VALUE_READ_FILES)
		return 0;

	len = sysfs_cpufreq_read_file(cpu, cpufreq_value_files[which],
				linebuf, sizeof(linebuf));

	if (len == 0)
		return 0;

	value = strtoul(linebuf, &endp, 0);

	if (endp == linebuf || errno == ERANGE)
		return 0;

	return value;
}