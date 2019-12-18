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
 int /*<<< orphan*/  PATH_MAX ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *cpio_replace_env(char *new_location)
{
	char expanded[PATH_MAX + 1];
	char *start, *end, *var;

	while ((start = strstr(new_location, "${")) &&
	       (end = strchr(start + 2, '}'))) {
		*start = *end = 0;
		var = getenv(start + 2);
		snprintf(expanded, sizeof expanded, "%s%s%s",
			 new_location, var ? var : "", end + 1);
		strcpy(new_location, expanded);
	}

	return new_location;
}