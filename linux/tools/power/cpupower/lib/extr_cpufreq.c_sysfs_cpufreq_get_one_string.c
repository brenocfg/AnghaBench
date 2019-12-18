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
typedef  enum cpufreq_string { ____Placeholder_cpufreq_string } cpufreq_string ;

/* Variables and functions */
 int MAX_CPUFREQ_STRING_FILES ; 
 int MAX_LINE_LEN ; 
 int /*<<< orphan*/ * cpufreq_string_files ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 unsigned int sysfs_cpufreq_read_file (unsigned int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *sysfs_cpufreq_get_one_string(unsigned int cpu,
					   enum cpufreq_string which)
{
	char linebuf[MAX_LINE_LEN];
	char *result;
	unsigned int len;

	if (which >= MAX_CPUFREQ_STRING_FILES)
		return NULL;

	len = sysfs_cpufreq_read_file(cpu, cpufreq_string_files[which],
				linebuf, sizeof(linebuf));
	if (len == 0)
		return NULL;

	result = strdup(linebuf);
	if (result == NULL)
		return NULL;

	if (result[strlen(result) - 1] == '\n')
		result[strlen(result) - 1] = '\0';

	return result;
}