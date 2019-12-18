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
	printf(_("%s takes a base backup of a running PostgreSQL server.\n\n"),
		   progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]...\n"), progname);
	printf(_("\nOptions controlling the output:\n"));
	printf(_("  -D, --pgdata=DIRECTORY receive base backup into directory\n"));
	printf(_("  -F, --format=p|t       output format (plain (default), tar)\n"));
	printf(_("  -r, --max-rate=RATE    maximum transfer rate to transfer data directory\n"
			 "                         (in kB/s, or use suffix \"k\" or \"M\")\n"));
	printf(_("  -R, --write-recovery-conf\n"
			 "                         write configuration for replication\n"));
	printf(_("  -T, --tablespace-mapping=OLDDIR=NEWDIR\n"
			 "                         relocate tablespace in OLDDIR to NEWDIR\n"));
	printf(_("      --waldir=WALDIR    location for the write-ahead log directory\n"));
	printf(_("  -X, --wal-method=none|fetch|stream\n"
			 "                         include required WAL files with specified method\n"));
	printf(_("  -z, --gzip             compress tar output\n"));
	printf(_("  -Z, --compress=0-9     compress tar output with given compression level\n"));
	printf(_("\nGeneral options:\n"));
	printf(_("  -c, --checkpoint=fast|spread\n"
			 "                         set fast or spread checkpointing\n"));
	printf(_("  -C, --create-slot      create replication slot\n"));
	printf(_("  -l, --label=LABEL      set backup label\n"));
	printf(_("  -n, --no-clean         do not clean up after errors\n"));
	printf(_("  -N, --no-sync          do not wait for changes to be written safely to disk\n"));
	printf(_("  -P, --progress         show progress information\n"));
	printf(_("  -S, --slot=SLOTNAME    replication slot to use\n"));
	printf(_("  -v, --verbose          output verbose messages\n"));
	printf(_("  -V, --version          output version information, then exit\n"));
	printf(_("      --no-slot          prevent creation of temporary replication slot\n"));
	printf(_("      --no-verify-checksums\n"
			 "                         do not verify checksums\n"));
	printf(_("  -?, --help             show this help, then exit\n"));
	printf(_("\nConnection options:\n"));
	printf(_("  -d, --dbname=CONNSTR   connection string\n"));
	printf(_("  -h, --host=HOSTNAME    database server host or socket directory\n"));
	printf(_("  -p, --port=PORT        database server port number\n"));
	printf(_("  -s, --status-interval=INTERVAL\n"
			 "                         time between status packets sent to server (in seconds)\n"));
	printf(_("  -U, --username=NAME    connect as specified database user\n"));
	printf(_("  -w, --no-password      never prompt for password\n"));
	printf(_("  -W, --password         force password prompt (should happen automatically)\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}