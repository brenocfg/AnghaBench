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
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strstr (char*,char const*) ; 

unsigned int err_pos(char *cmd, const char *str)
{
	char *found;

	if (WARN_ON(!strlen(cmd)))
		return 0;

	found = strstr(cmd, str);
	if (found)
		return found - cmd;

	return 0;
}