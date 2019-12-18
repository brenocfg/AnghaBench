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
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* get_user_name_or_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  pg_log_error (char*) ; 
 char* pg_strdup (char const*) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char *
get_id(void)
{
	const char *username;

#ifndef WIN32
	if (geteuid() == 0)			/* 0 is root's uid */
	{
		pg_log_error("cannot be run as root");
		fprintf(stderr,
				_("Please log in (using, e.g., \"su\") as the (unprivileged) user that will\n"
				  "own the server process.\n"));
		exit(1);
	}
#endif

	username = get_user_name_or_exit(progname);

	return pg_strdup(username);
}