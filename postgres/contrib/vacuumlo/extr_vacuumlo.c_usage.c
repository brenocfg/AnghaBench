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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
usage(const char *progname)
{
	printf("%s removes unreferenced large objects from databases.\n\n", progname);
	printf("Usage:\n  %s [OPTION]... DBNAME...\n\n", progname);
	printf("Options:\n");
	printf("  -l, --limit=LIMIT         commit after removing each LIMIT large objects\n");
	printf("  -n, --dry-run             don't remove large objects, just show what would be done\n");
	printf("  -v, --verbose             write a lot of progress messages\n");
	printf("  -V, --version             output version information, then exit\n");
	printf("  -?, --help                show this help, then exit\n");
	printf("\nConnection options:\n");
	printf("  -h, --host=HOSTNAME       database server host or socket directory\n");
	printf("  -p, --port=PORT           database server port\n");
	printf("  -U, --username=USERNAME   user name to connect as\n");
	printf("  -w, --no-password         never prompt for password\n");
	printf("  -W, --password            force password prompt\n");
	printf("\n");
	printf("Report bugs to <pgsql-bugs@lists.postgresql.org>.\n");
}