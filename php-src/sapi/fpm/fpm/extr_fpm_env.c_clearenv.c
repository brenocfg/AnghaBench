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
 char** environ ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

void clearenv() /* {{{ */
{
	char **envp;
	char *s;

	/* this algo is the only one known to me
		that works well on all systems */
	while (*(envp = environ)) {
		char *eq = strchr(*envp, '=');

		s = strdup(*envp);

		if (eq) s[eq - *envp] = '\0';

		unsetenv(s);
		free(s);
	}

}