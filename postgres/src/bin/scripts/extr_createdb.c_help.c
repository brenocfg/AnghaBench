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
	printf(_("%s creates a PostgreSQL database.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... [DBNAME] [DESCRIPTION]\n"), progname);
	printf(_("\nOptions:\n"));
	printf(_("  -D, --tablespace=TABLESPACE  default tablespace for the database\n"));
	printf(_("  -e, --echo                   show the commands being sent to the server\n"));
	printf(_("  -E, --encoding=ENCODING      encoding for the database\n"));
	printf(_("  -l, --locale=LOCALE          locale settings for the database\n"));
	printf(_("      --lc-collate=LOCALE      LC_COLLATE setting for the database\n"));
	printf(_("      --lc-ctype=LOCALE        LC_CTYPE setting for the database\n"));
	printf(_("  -O, --owner=OWNER            database user to own the new database\n"));
	printf(_("  -T, --template=TEMPLATE      template database to copy\n"));
	printf(_("  -V, --version                output version information, then exit\n"));
	printf(_("  -?, --help                   show this help, then exit\n"));
	printf(_("\nConnection options:\n"));
	printf(_("  -h, --host=HOSTNAME          database server host or socket directory\n"));
	printf(_("  -p, --port=PORT              database server port\n"));
	printf(_("  -U, --username=USERNAME      user name to connect as\n"));
	printf(_("  -w, --no-password            never prompt for password\n"));
	printf(_("  -W, --password               force password prompt\n"));
	printf(_("  --maintenance-db=DBNAME      alternate maintenance database\n"));
	printf(_("\nBy default, a database with the same name as the current user is created.\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}