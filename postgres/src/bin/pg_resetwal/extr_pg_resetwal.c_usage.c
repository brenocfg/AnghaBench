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
 char* progname ; 

__attribute__((used)) static void
usage(void)
{
	printf(_("%s resets the PostgreSQL write-ahead log.\n\n"), progname);
	printf(_("Usage:\n  %s [OPTION]... DATADIR\n\n"), progname);
	printf(_("Options:\n"));
	printf(_("  -c, --commit-timestamp-ids=XID,XID\n"
			 "                                 set oldest and newest transactions bearing\n"
			 "                                 commit timestamp (zero means no change)\n"));
	printf(_(" [-D, --pgdata=]DATADIR          data directory\n"));
	printf(_("  -e, --epoch=XIDEPOCH           set next transaction ID epoch\n"));
	printf(_("  -f, --force                    force update to be done\n"));
	printf(_("  -l, --next-wal-file=WALFILE    set minimum starting location for new WAL\n"));
	printf(_("  -m, --multixact-ids=MXID,MXID  set next and oldest multitransaction ID\n"));
	printf(_("  -n, --dry-run                  no update, just show what would be done\n"));
	printf(_("  -o, --next-oid=OID             set next OID\n"));
	printf(_("  -O, --multixact-offset=OFFSET  set next multitransaction offset\n"));
	printf(_("  -V, --version                  output version information, then exit\n"));
	printf(_("  -x, --next-transaction-id=XID  set next transaction ID\n"));
	printf(_("      --wal-segsize=SIZE         size of WAL segments, in megabytes\n"));
	printf(_("  -?, --help                     show this help, then exit\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}