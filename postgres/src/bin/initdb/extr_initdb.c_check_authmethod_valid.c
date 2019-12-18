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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,char const*) ; 
 int strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char const* const) ; 
 scalar_t__ strncmp (char const*,char const* const,char const*) ; 

__attribute__((used)) static void
check_authmethod_valid(const char *authmethod, const char *const *valid_methods, const char *conntype)
{
	const char *const *p;

	for (p = valid_methods; *p; p++)
	{
		if (strcmp(authmethod, *p) == 0)
			return;
		/* with space = param */
		if (strchr(authmethod, ' '))
			if (strncmp(authmethod, *p, (authmethod - strchr(authmethod, ' '))) == 0)
				return;
	}

	pg_log_error("invalid authentication method \"%s\" for \"%s\" connections",
				 authmethod, conntype);
	exit(1);
}