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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  convert_sourcefiles () ; 
 int /*<<< orphan*/  doputenv (char*,char*) ; 
 char* encoding ; 
 void* getenv (char*) ; 
 char* hostname ; 
 int /*<<< orphan*/  load_resultmap () ; 
 char* make_temp_sockdir () ; 
 scalar_t__ nolocale ; 
 int port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* psprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 char* sockdir ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ temp_instance ; 
 int /*<<< orphan*/  unsetenv (char*) ; 
 char* user ; 

__attribute__((used)) static void
initialize_environment(void)
{
	/*
	 * Set default application_name.  (The test_function may choose to
	 * override this, but if it doesn't, we have something useful in place.)
	 */
	putenv("PGAPPNAME=pg_regress");

	if (nolocale)
	{
		/*
		 * Clear out any non-C locale settings
		 */
		unsetenv("LC_COLLATE");
		unsetenv("LC_CTYPE");
		unsetenv("LC_MONETARY");
		unsetenv("LC_NUMERIC");
		unsetenv("LC_TIME");
		unsetenv("LANG");

		/*
		 * Most platforms have adopted the POSIX locale as their
		 * implementation-defined default locale.  Exceptions include native
		 * Windows, macOS with --enable-nls, and Cygwin with --enable-nls.
		 * (Use of --enable-nls matters because libintl replaces setlocale().)
		 * Also, PostgreSQL does not support macOS with locale environment
		 * variables unset; see PostmasterMain().
		 */
#if defined(WIN32) || defined(__CYGWIN__) || defined(__darwin__)
		putenv("LANG=C");
#endif
	}

	/*
	 * Set translation-related settings to English; otherwise psql will
	 * produce translated messages and produce diffs.  (XXX If we ever support
	 * translation of pg_regress, this needs to be moved elsewhere, where psql
	 * is actually called.)
	 */
	unsetenv("LANGUAGE");
	unsetenv("LC_ALL");
	putenv("LC_MESSAGES=C");

	/*
	 * Set encoding as requested
	 */
	if (encoding)
		doputenv("PGCLIENTENCODING", encoding);
	else
		unsetenv("PGCLIENTENCODING");

	/*
	 * Set timezone and datestyle for datetime-related tests
	 */
	putenv("PGTZ=PST8PDT");
	putenv("PGDATESTYLE=Postgres, MDY");

	/*
	 * Likewise set intervalstyle to ensure consistent results.  This is a bit
	 * more painful because we must use PGOPTIONS, and we want to preserve the
	 * user's ability to set other variables through that.
	 */
	{
		const char *my_pgoptions = "-c intervalstyle=postgres_verbose";
		const char *old_pgoptions = getenv("PGOPTIONS");
		char	   *new_pgoptions;

		if (!old_pgoptions)
			old_pgoptions = "";
		new_pgoptions = psprintf("PGOPTIONS=%s %s",
								 old_pgoptions, my_pgoptions);
		putenv(new_pgoptions);
	}

	if (temp_instance)
	{
		/*
		 * Clear out any environment vars that might cause psql to connect to
		 * the wrong postmaster, or otherwise behave in nondefault ways. (Note
		 * we also use psql's -X switch consistently, so that ~/.psqlrc files
		 * won't mess things up.)  Also, set PGPORT to the temp port, and set
		 * PGHOST depending on whether we are using TCP or Unix sockets.
		 */
		unsetenv("PGDATABASE");
		unsetenv("PGUSER");
		unsetenv("PGSERVICE");
		unsetenv("PGSSLMODE");
		unsetenv("PGREQUIRESSL");
		unsetenv("PGCONNECT_TIMEOUT");
		unsetenv("PGDATA");
#ifdef HAVE_UNIX_SOCKETS
		if (hostname != NULL)
			doputenv("PGHOST", hostname);
		else
		{
			sockdir = getenv("PG_REGRESS_SOCK_DIR");
			if (!sockdir)
				sockdir = make_temp_sockdir();
			doputenv("PGHOST", sockdir);
		}
#else
		Assert(hostname != NULL);
		doputenv("PGHOST", hostname);
#endif
		unsetenv("PGHOSTADDR");
		if (port != -1)
		{
			char		s[16];

			sprintf(s, "%d", port);
			doputenv("PGPORT", s);
		}
	}
	else
	{
		const char *pghost;
		const char *pgport;

		/*
		 * When testing an existing install, we honor existing environment
		 * variables, except if they're overridden by command line options.
		 */
		if (hostname != NULL)
		{
			doputenv("PGHOST", hostname);
			unsetenv("PGHOSTADDR");
		}
		if (port != -1)
		{
			char		s[16];

			sprintf(s, "%d", port);
			doputenv("PGPORT", s);
		}
		if (user != NULL)
			doputenv("PGUSER", user);

		/*
		 * However, we *don't* honor PGDATABASE, since we certainly don't wish
		 * to connect to whatever database the user might like as default.
		 * (Most tests override PGDATABASE anyway, but there are some ECPG
		 * test cases that don't.)
		 */
		unsetenv("PGDATABASE");

		/*
		 * Report what we're connecting to
		 */
		pghost = getenv("PGHOST");
		pgport = getenv("PGPORT");
#ifndef HAVE_UNIX_SOCKETS
		if (!pghost)
			pghost = "localhost";
#endif

		if (pghost && pgport)
			printf(_("(using postmaster on %s, port %s)\n"), pghost, pgport);
		if (pghost && !pgport)
			printf(_("(using postmaster on %s, default port)\n"), pghost);
		if (!pghost && pgport)
			printf(_("(using postmaster on Unix socket, port %s)\n"), pgport);
		if (!pghost && !pgport)
			printf(_("(using postmaster on Unix socket, default port)\n"));
	}

	convert_sourcefiles();
	load_resultmap();
}