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
help(void)
{
	printf(_("PostgreSQL regression test driver\n"));
	printf(_("\n"));
	printf(_("Usage:\n  %s [OPTION]... [EXTRA-TEST]...\n"), progname);
	printf(_("\n"));
	printf(_("Options:\n"));
	printf(_("      --bindir=BINPATH          use BINPATH for programs that are run;\n"));
	printf(_("                                if empty, use PATH from the environment\n"));
	printf(_("      --config-auth=DATADIR     update authentication settings for DATADIR\n"));
	printf(_("      --create-role=ROLE        create the specified role before testing\n"));
	printf(_("      --dbname=DB               use database DB (default \"regression\")\n"));
	printf(_("      --debug                   turn on debug mode in programs that are run\n"));
	printf(_("      --dlpath=DIR              look for dynamic libraries in DIR\n"));
	printf(_("      --encoding=ENCODING       use ENCODING as the encoding\n"));
	printf(_("  -h, --help                    show this help, then exit\n"));
	printf(_("      --inputdir=DIR            take input files from DIR (default \".\")\n"));
	printf(_("      --launcher=CMD            use CMD as launcher of psql\n"));
	printf(_("      --load-extension=EXT      load the named extension before running the\n"));
	printf(_("                                tests; can appear multiple times\n"));
	printf(_("      --load-language=LANG      load the named language before running the\n"));
	printf(_("                                tests; can appear multiple times\n"));
	printf(_("      --max-connections=N       maximum number of concurrent connections\n"));
	printf(_("                                (default is 0, meaning unlimited)\n"));
	printf(_("      --max-concurrent-tests=N  maximum number of concurrent tests in schedule\n"));
	printf(_("                                (default is 0, meaning unlimited)\n"));
	printf(_("      --outputdir=DIR           place output files in DIR (default \".\")\n"));
	printf(_("      --schedule=FILE           use test ordering schedule from FILE\n"));
	printf(_("                                (can be used multiple times to concatenate)\n"));
	printf(_("      --temp-instance=DIR       create a temporary instance in DIR\n"));
	printf(_("      --use-existing            use an existing installation\n"));
	printf(_("  -V, --version                 output version information, then exit\n"));
	printf(_("\n"));
	printf(_("Options for \"temp-instance\" mode:\n"));
	printf(_("      --no-locale               use C locale\n"));
	printf(_("      --port=PORT               start postmaster on PORT\n"));
	printf(_("      --temp-config=FILE        append contents of FILE to temporary config\n"));
	printf(_("\n"));
	printf(_("Options for using an existing installation:\n"));
	printf(_("      --host=HOST               use postmaster running on HOST\n"));
	printf(_("      --port=PORT               use postmaster running at PORT\n"));
	printf(_("      --user=USER               connect as USER\n"));
	printf(_("\n"));
	printf(_("The exit status is 0 if all tests passed, 1 if some tests failed, and 2\n"));
	printf(_("if the tests could not be run for some reason.\n"));
	printf(_("\n"));
	printf(_("Report bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}