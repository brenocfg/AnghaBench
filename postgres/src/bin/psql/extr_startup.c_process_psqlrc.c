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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int MAXPGPATH ; 
 char* PSQLRC ; 
 char* SYSPSQLRC ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_tilde (char**) ; 
 scalar_t__ find_my_exec (char*,char*) ; 
 int /*<<< orphan*/  get_etc_path (char*,char*) ; 
 scalar_t__ get_home_path (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  pg_log_fatal (char*) ; 
 int /*<<< orphan*/  process_psqlrc_file (char*) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
process_psqlrc(char *argv0)
{
	char		home[MAXPGPATH];
	char		rc_file[MAXPGPATH];
	char		my_exec_path[MAXPGPATH];
	char		etc_path[MAXPGPATH];
	char	   *envrc = getenv("PSQLRC");

	if (find_my_exec(argv0, my_exec_path) < 0)
	{
		pg_log_fatal("could not find own program executable");
		exit(EXIT_FAILURE);
	}

	get_etc_path(my_exec_path, etc_path);

	snprintf(rc_file, MAXPGPATH, "%s/%s", etc_path, SYSPSQLRC);
	process_psqlrc_file(rc_file);

	if (envrc != NULL && strlen(envrc) > 0)
	{
		/* might need to free() this */
		char	   *envrc_alloc = pstrdup(envrc);

		expand_tilde(&envrc_alloc);
		process_psqlrc_file(envrc_alloc);
	}
	else if (get_home_path(home))
	{
		snprintf(rc_file, MAXPGPATH, "%s/%s", home, PSQLRC);
		process_psqlrc_file(rc_file);
	}
}