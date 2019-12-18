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
	printf(_("%s removes older WAL files from PostgreSQL archives.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... ARCHIVELOCATION OLDESTKEPTWALFILE\n"), progname);
	printf(_("\nOptions:\n"));
	printf(_("  -d             generate debug output (verbose mode)\n"));
	printf(_("  -n             dry run, show the names of the files that would be removed\n"));
	printf(_("  -V, --version  output version information, then exit\n"));
	printf(_("  -x EXT         clean up files if they have this extension\n"));
	printf(_("  -?, --help     show this help, then exit\n"));
	printf(_("\n"
			 "For use as archive_cleanup_command in postgresql.conf:\n"
			 "  archive_cleanup_command = 'pg_archivecleanup [OPTION]... ARCHIVELOCATION %%r'\n"
			 "e.g.\n"
			 "  archive_cleanup_command = 'pg_archivecleanup /mnt/server/archiverdir %%r'\n"));
	printf(_("\n"
			 "Or for use as a standalone archive cleaner:\n"
			 "e.g.\n"
			 "  pg_archivecleanup /mnt/server/archiverdir 000000010000000000000010.00000020.backup\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}