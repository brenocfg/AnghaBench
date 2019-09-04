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
typedef  enum cpuidle_string { ____Placeholder_cpuidle_string } cpuidle_string ;

/* Variables and functions */
 int MAX_CPUIDLE_STRING_FILES ; 
 int MAX_LINE_LEN ; 
 int /*<<< orphan*/ * cpuidle_string_files ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 unsigned int sysfs_cpuidle_read_file (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *sysfs_cpuidle_get_one_string(enum cpuidle_string which)
{
	char linebuf[MAX_LINE_LEN];
	char *result;
	unsigned int len;

	if (which >= MAX_CPUIDLE_STRING_FILES)
		return NULL;

	len = sysfs_cpuidle_read_file(cpuidle_string_files[which],
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