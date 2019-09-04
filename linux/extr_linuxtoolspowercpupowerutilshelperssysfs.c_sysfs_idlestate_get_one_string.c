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
typedef  enum idlestate_string { ____Placeholder_idlestate_string } idlestate_string ;

/* Variables and functions */
 int MAX_IDLESTATE_STRING_FILES ; 
 int MAX_LINE_LEN ; 
 int /*<<< orphan*/ * idlestate_string_files ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 unsigned int sysfs_idlestate_read_file (unsigned int,unsigned int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *sysfs_idlestate_get_one_string(unsigned int cpu,
					unsigned int idlestate,
					enum idlestate_string which)
{
	char linebuf[MAX_LINE_LEN];
	char *result;
	unsigned int len;

	if (which >= MAX_IDLESTATE_STRING_FILES)
		return NULL;

	len = sysfs_idlestate_read_file(cpu, idlestate,
					idlestate_string_files[which],
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