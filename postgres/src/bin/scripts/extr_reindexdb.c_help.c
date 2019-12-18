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
help(const char *progname)
{
	printf(_("%s reindexes a PostgreSQL database.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... [DBNAME]\n"), progname);
	printf(_("\nOptions:\n"));
	printf(_("  -a, --all                 reindex all databases\n"));
	printf(_("      --concurrently        reindex concurrently\n"));
	printf(_("  -d, --dbname=DBNAME       database to reindex\n"));
	printf(_("  -e, --echo                show the commands being sent to the server\n"));
	printf(_("  -i, --index=INDEX         recreate specific index(es) only\n"));
	printf(_("  -j, --jobs=NUM            use this many concurrent connections to reindex\n"));
	printf(_("  -q, --quiet               don't write any messages\n"));
	printf(_("  -s, --system              reindex system catalogs\n"));
	printf(_("  -S, --schema=SCHEMA       reindex specific schema(s) only\n"));
	printf(_("  -t, --table=TABLE         reindex specific table(s) only\n"));
	printf(_("  -v, --verbose             write a lot of output\n"));
	printf(_("  -V, --version             output version information, then exit\n"));
	printf(_("  -?, --help                show this help, then exit\n"));
	printf(_("\nConnection options:\n"));
	printf(_("  -h, --host=HOSTNAME       database server host or socket directory\n"));
	printf(_("  -p, --port=PORT           database server port\n"));
	printf(_("  -U, --username=USERNAME   user name to connect as\n"));
	printf(_("  -w, --no-password         never prompt for password\n"));
	printf(_("  -W, --password            force password prompt\n"));
	printf(_("  --maintenance-db=DBNAME   alternate maintenance database\n"));
	printf(_("\nRead the description of the SQL command REINDEX for details.\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}