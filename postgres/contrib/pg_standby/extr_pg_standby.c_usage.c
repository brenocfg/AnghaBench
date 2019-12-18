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
 char* progname ; 

__attribute__((used)) static void
usage(void)
{
	printf("%s allows PostgreSQL warm standby servers to be configured.\n\n", progname);
	printf("Usage:\n");
	printf("  %s [OPTION]... ARCHIVELOCATION NEXTWALFILE XLOGFILEPATH [RESTARTWALFILE]\n", progname);
	printf("\nOptions:\n");
	printf("  -c                 copy file from archive (default)\n");
	printf("  -d                 generate lots of debugging output (testing only)\n");
	printf("  -k NUMFILESTOKEEP  if RESTARTWALFILE is not used, remove files prior to limit\n"
		   "                     (0 keeps all)\n");
	printf("  -l                 does nothing; use of link is now deprecated\n");
	printf("  -r MAXRETRIES      max number of times to retry, with progressive wait\n"
		   "                     (default=3)\n");
	printf("  -s SLEEPTIME       seconds to wait between file checks (min=1, max=60,\n"
		   "                     default=5)\n");
	printf("  -t TRIGGERFILE     trigger file to initiate failover (no default)\n");
	printf("  -V, --version      output version information, then exit\n");
	printf("  -w MAXWAITTIME     max seconds to wait for a file (0=no limit) (default=0)\n");
	printf("  -?, --help         show this help, then exit\n");
	printf("\n"
		   "Main intended use as restore_command in postgresql.conf:\n"
		   "  restore_command = 'pg_standby [OPTION]... ARCHIVELOCATION %%f %%p %%r'\n"
		   "e.g.\n"
		   "  restore_command = 'pg_standby /mnt/server/archiverdir %%f %%p %%r'\n");
	printf("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n");
}