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
 char** __env ; 
 int __nenv ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

char *kdbgetenv(const char *match)
{
	char **ep = __env;
	int matchlen = strlen(match);
	int i;

	for (i = 0; i < __nenv; i++) {
		char *e = *ep++;

		if (!e)
			continue;

		if ((strncmp(match, e, matchlen) == 0)
		 && ((e[matchlen] == '\0')
		   || (e[matchlen] == '='))) {
			char *cp = strchr(e, '=');
			return cp ? ++cp : "";
		}
	}
	return NULL;
}