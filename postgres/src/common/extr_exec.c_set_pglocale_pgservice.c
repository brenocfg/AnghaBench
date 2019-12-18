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
typedef  int /*<<< orphan*/  env_path ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_TEXTDOMAIN (char*) ; 
 int /*<<< orphan*/  bindtextdomain (char const*,char*) ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 scalar_t__ find_my_exec (char const*,char*) ; 
 int /*<<< orphan*/  get_etc_path (char*,char*) ; 
 int /*<<< orphan*/  get_locale_path (char*,char*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  textdomain (char const*) ; 

void
set_pglocale_pgservice(const char *argv0, const char *app)
{
	char		path[MAXPGPATH];
	char		my_exec_path[MAXPGPATH];
	char		env_path[MAXPGPATH + sizeof("PGSYSCONFDIR=")];	/* longer than
																 * PGLOCALEDIR */
	char	   *dup_path;

	/* don't set LC_ALL in the backend */
	if (strcmp(app, PG_TEXTDOMAIN("postgres")) != 0)
	{
		setlocale(LC_ALL, "");

		/*
		 * One could make a case for reproducing here PostmasterMain()'s test
		 * for whether the process is multithreaded.  Unlike the postmaster,
		 * no frontend program calls sigprocmask() or otherwise provides for
		 * mutual exclusion between signal handlers.  While frontends using
		 * fork(), if multithreaded, are formally exposed to undefined
		 * behavior, we have not witnessed a concrete bug.  Therefore,
		 * complaining about multithreading here may be mere pedantry.
		 */
	}

	if (find_my_exec(argv0, my_exec_path) < 0)
		return;

#ifdef ENABLE_NLS
	get_locale_path(my_exec_path, path);
	bindtextdomain(app, path);
	textdomain(app);

	if (getenv("PGLOCALEDIR") == NULL)
	{
		/* set for libpq to use */
		snprintf(env_path, sizeof(env_path), "PGLOCALEDIR=%s", path);
		canonicalize_path(env_path + 12);
		dup_path = strdup(env_path);
		if (dup_path)
			putenv(dup_path);
	}
#endif

	if (getenv("PGSYSCONFDIR") == NULL)
	{
		get_etc_path(my_exec_path, path);

		/* set for libpq to use */
		snprintf(env_path, sizeof(env_path), "PGSYSCONFDIR=%s", path);
		canonicalize_path(env_path + 13);
		dup_path = strdup(env_path);
		if (dup_path)
			putenv(dup_path);
	}
}