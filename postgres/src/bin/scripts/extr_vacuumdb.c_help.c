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
	printf(_("%s cleans and analyzes a PostgreSQL database.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... [DBNAME]\n"), progname);
	printf(_("\nOptions:\n"));
	printf(_("  -a, --all                       vacuum all databases\n"));
	printf(_("  -d, --dbname=DBNAME             database to vacuum\n"));
	printf(_("      --disable-page-skipping     disable all page-skipping behavior\n"));
	printf(_("  -e, --echo                      show the commands being sent to the server\n"));
	printf(_("  -f, --full                      do full vacuuming\n"));
	printf(_("  -F, --freeze                    freeze row transaction information\n"));
	printf(_("  -j, --jobs=NUM                  use this many concurrent connections to vacuum\n"));
	printf(_("      --min-mxid-age=MXID_AGE     minimum multixact ID age of tables to vacuum\n"));
	printf(_("      --min-xid-age=XID_AGE       minimum transaction ID age of tables to vacuum\n"));
	printf(_("  -q, --quiet                     don't write any messages\n"));
	printf(_("      --skip-locked               skip relations that cannot be immediately locked\n"));
	printf(_("  -t, --table='TABLE[(COLUMNS)]'  vacuum specific table(s) only\n"));
	printf(_("  -v, --verbose                   write a lot of output\n"));
	printf(_("  -V, --version                   output version information, then exit\n"));
	printf(_("  -z, --analyze                   update optimizer statistics\n"));
	printf(_("  -Z, --analyze-only              only update optimizer statistics; no vacuum\n"));
	printf(_("      --analyze-in-stages         only update optimizer statistics, in multiple\n"
			 "                                  stages for faster results; no vacuum\n"));
	printf(_("  -?, --help                      show this help, then exit\n"));
	printf(_("\nConnection options:\n"));
	printf(_("  -h, --host=HOSTNAME       database server host or socket directory\n"));
	printf(_("  -p, --port=PORT           database server port\n"));
	printf(_("  -U, --username=USERNAME   user name to connect as\n"));
	printf(_("  -w, --no-password         never prompt for password\n"));
	printf(_("  -W, --password            force password prompt\n"));
	printf(_("  --maintenance-db=DBNAME   alternate maintenance database\n"));
	printf(_("\nRead the description of the SQL command VACUUM for details.\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}