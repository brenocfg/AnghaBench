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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 char* pg_strdup (char*) ; 
 char* setlocale (int,char const*) ; 

__attribute__((used)) static void
check_locale_name(int category, const char *locale, char **canonname)
{
	char	   *save;
	char	   *res;

	if (canonname)
		*canonname = NULL;		/* in case of failure */

	save = setlocale(category, NULL);
	if (!save)
	{
		pg_log_error("setlocale() failed");
		exit(1);
	}

	/* save may be pointing at a modifiable scratch variable, so copy it. */
	save = pg_strdup(save);

	/* for setlocale() call */
	if (!locale)
		locale = "";

	/* set the locale with setlocale, to see if it accepts it. */
	res = setlocale(category, locale);

	/* save canonical name if requested. */
	if (res && canonname)
		*canonname = pg_strdup(res);

	/* restore old value. */
	if (!setlocale(category, save))
	{
		pg_log_error("failed to restore old locale \"%s\"", save);
		exit(1);
	}
	free(save);

	/* complain if locale wasn't valid */
	if (res == NULL)
	{
		if (*locale)
			pg_log_error("invalid locale name \"%s\"", locale);
		else
		{
			/*
			 * If no relevant switch was given on command line, locale is an
			 * empty string, which is not too helpful to report.  Presumably
			 * setlocale() found something it did not like in the environment.
			 * Ideally we'd report the bad environment variable, but since
			 * setlocale's behavior is implementation-specific, it's hard to
			 * be sure what it didn't like.  Print a safe generic message.
			 */
			pg_log_error("invalid locale settings; check LANG and LC_* environment variables");
		}
		exit(1);
	}
}