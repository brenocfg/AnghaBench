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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(const char *progname)
{
	printf(_("%s initializes a PostgreSQL database cluster.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... [DATADIR]\n"), progname);
	printf(_("\nOptions:\n"));
	printf(_("  -A, --auth=METHOD         default authentication method for local connections\n"));
	printf(_("      --auth-host=METHOD    default authentication method for local TCP/IP connections\n"));
	printf(_("      --auth-local=METHOD   default authentication method for local-socket connections\n"));
	printf(_(" [-D, --pgdata=]DATADIR     location for this database cluster\n"));
	printf(_("  -E, --encoding=ENCODING   set default encoding for new databases\n"));
	printf(_("  -g, --allow-group-access  allow group read/execute on data directory\n"));
	printf(_("      --locale=LOCALE       set default locale for new databases\n"));
	printf(_("      --lc-collate=, --lc-ctype=, --lc-messages=LOCALE\n"
			 "      --lc-monetary=, --lc-numeric=, --lc-time=LOCALE\n"
			 "                            set default locale in the respective category for\n"
			 "                            new databases (default taken from environment)\n"));
	printf(_("      --no-locale           equivalent to --locale=C\n"));
	printf(_("      --pwfile=FILE         read password for the new superuser from file\n"));
	printf(_("  -T, --text-search-config=CFG\n"
			 "                            default text search configuration\n"));
	printf(_("  -U, --username=NAME       database superuser name\n"));
	printf(_("  -W, --pwprompt            prompt for a password for the new superuser\n"));
	printf(_("  -X, --waldir=WALDIR       location for the write-ahead log directory\n"));
	printf(_("      --wal-segsize=SIZE    size of WAL segments, in megabytes\n"));
	printf(_("\nLess commonly used options:\n"));
	printf(_("  -d, --debug               generate lots of debugging output\n"));
	printf(_("  -k, --data-checksums      use data page checksums\n"));
	printf(_("  -L DIRECTORY              where to find the input files\n"));
	printf(_("  -n, --no-clean            do not clean up after errors\n"));
	printf(_("  -N, --no-sync             do not wait for changes to be written safely to disk\n"));
	printf(_("  -s, --show                show internal settings\n"));
	printf(_("  -S, --sync-only           only sync data directory\n"));
	printf(_("\nOther options:\n"));
	printf(_("  -V, --version             output version information, then exit\n"));
	printf(_("  -?, --help                show this help, then exit\n"));
	printf(_("\nIf the data directory is not specified, the environment variable PGDATA\n"
			 "is used.\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}