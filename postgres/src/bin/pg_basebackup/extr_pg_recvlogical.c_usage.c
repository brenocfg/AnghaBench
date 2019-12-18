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
 int fsync_interval ; 
 char* plugin ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* progname ; 
 int standby_message_timeout ; 

__attribute__((used)) static void
usage(void)
{
	printf(_("%s controls PostgreSQL logical decoding streams.\n\n"),
		   progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]...\n"), progname);
	printf(_("\nAction to be performed:\n"));
	printf(_("      --create-slot      create a new replication slot (for the slot's name see --slot)\n"));
	printf(_("      --drop-slot        drop the replication slot (for the slot's name see --slot)\n"));
	printf(_("      --start            start streaming in a replication slot (for the slot's name see --slot)\n"));
	printf(_("\nOptions:\n"));
	printf(_("  -E, --endpos=LSN       exit after receiving the specified LSN\n"));
	printf(_("  -f, --file=FILE        receive log into this file, - for stdout\n"));
	printf(_("  -F  --fsync-interval=SECS\n"
			 "                         time between fsyncs to the output file (default: %d)\n"), (fsync_interval / 1000));
	printf(_("      --if-not-exists    do not error if slot already exists when creating a slot\n"));
	printf(_("  -I, --startpos=LSN     where in an existing slot should the streaming start\n"));
	printf(_("  -n, --no-loop          do not loop on connection lost\n"));
	printf(_("  -o, --option=NAME[=VALUE]\n"
			 "                         pass option NAME with optional value VALUE to the\n"
			 "                         output plugin\n"));
	printf(_("  -P, --plugin=PLUGIN    use output plugin PLUGIN (default: %s)\n"), plugin);
	printf(_("  -s, --status-interval=SECS\n"
			 "                         time between status packets sent to server (default: %d)\n"), (standby_message_timeout / 1000));
	printf(_("  -S, --slot=SLOTNAME    name of the logical replication slot\n"));
	printf(_("  -v, --verbose          output verbose messages\n"));
	printf(_("  -V, --version          output version information, then exit\n"));
	printf(_("  -?, --help             show this help, then exit\n"));
	printf(_("\nConnection options:\n"));
	printf(_("  -d, --dbname=DBNAME    database to connect to\n"));
	printf(_("  -h, --host=HOSTNAME    database server host or socket directory\n"));
	printf(_("  -p, --port=PORT        database server port number\n"));
	printf(_("  -U, --username=NAME    connect as specified database user\n"));
	printf(_("  -w, --no-password      never prompt for password\n"));
	printf(_("  -W, --password         force password prompt (should happen automatically)\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}