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
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXPGPATH ; 
 int /*<<< orphan*/  PG_BACKEND_VERSIONSTR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv0 ; 
 int /*<<< orphan*/  canonicalize_path (char*) ; 
 char* exec_path ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* find_other_exec_or_die (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 char* pg_config ; 
 char* pg_data ; 
 char* pg_strdup (char*) ; 
 int /*<<< orphan*/  pg_strip_crlf (char*) ; 
 char* pgdata_opt ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 char* post_opts ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  write_stderr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
adjust_data_dir(void)
{
	char		cmd[MAXPGPATH],
				filename[MAXPGPATH],
			   *my_exec_path;
	FILE	   *fd;

	/* do nothing if we're working without knowledge of data dir */
	if (pg_config == NULL)
		return;

	/* If there is no postgresql.conf, it can't be a config-only dir */
	snprintf(filename, sizeof(filename), "%s/postgresql.conf", pg_config);
	if ((fd = fopen(filename, "r")) == NULL)
		return;
	fclose(fd);

	/* If PG_VERSION exists, it can't be a config-only dir */
	snprintf(filename, sizeof(filename), "%s/PG_VERSION", pg_config);
	if ((fd = fopen(filename, "r")) != NULL)
	{
		fclose(fd);
		return;
	}

	/* Must be a configuration directory, so find the data directory */

	/* we use a private my_exec_path to avoid interfering with later uses */
	if (exec_path == NULL)
		my_exec_path = find_other_exec_or_die(argv0, "postgres", PG_BACKEND_VERSIONSTR);
	else
		my_exec_path = pg_strdup(exec_path);

	/* it's important for -C to be the first option, see main.c */
	snprintf(cmd, MAXPGPATH, "\"%s\" -C data_directory %s%s",
			 my_exec_path,
			 pgdata_opt ? pgdata_opt : "",
			 post_opts ? post_opts : "");

	fd = popen(cmd, "r");
	if (fd == NULL || fgets(filename, sizeof(filename), fd) == NULL)
	{
		write_stderr(_("%s: could not determine the data directory using command \"%s\"\n"), progname, cmd);
		exit(1);
	}
	pclose(fd);
	free(my_exec_path);

	/* strip trailing newline and carriage return */
	(void) pg_strip_crlf(filename);

	free(pg_data);
	pg_data = pg_strdup(filename);
	canonicalize_path(pg_data);
}