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
	printf(_("%s enables, disables, or verifies data checksums in a PostgreSQL database cluster.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... [DATADIR]\n"), progname);
	printf(_("\nOptions:\n"));
	printf(_(" [-D, --pgdata=]DATADIR    data directory\n"));
	printf(_("  -c, --check              check data checksums (default)\n"));
	printf(_("  -d, --disable            disable data checksums\n"));
	printf(_("  -e, --enable             enable data checksums\n"));
	printf(_("  -f, --filenode=FILENODE  check only relation with specified filenode\n"));
	printf(_("  -N, --no-sync            do not wait for changes to be written safely to disk\n"));
	printf(_("  -P, --progress           show progress information\n"));
	printf(_("  -v, --verbose            output verbose messages\n"));
	printf(_("  -V, --version            output version information, then exit\n"));
	printf(_("  -?, --help               show this help, then exit\n"));
	printf(_("\nIf no data directory (DATADIR) is specified, "
			 "the environment variable PGDATA\nis used.\n\n"));
	printf(_("Report bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}