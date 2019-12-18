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
	printf(_("%s is the PostgreSQL server.\n\n"), progname);
	printf(_("Usage:\n  %s [OPTION]...\n\n"), progname);
	printf(_("Options:\n"));
	printf(_("  -B NBUFFERS        number of shared buffers\n"));
	printf(_("  -c NAME=VALUE      set run-time parameter\n"));
	printf(_("  -C NAME            print value of run-time parameter, then exit\n"));
	printf(_("  -d 1-5             debugging level\n"));
	printf(_("  -D DATADIR         database directory\n"));
	printf(_("  -e                 use European date input format (DMY)\n"));
	printf(_("  -F                 turn fsync off\n"));
	printf(_("  -h HOSTNAME        host name or IP address to listen on\n"));
	printf(_("  -i                 enable TCP/IP connections\n"));
	printf(_("  -k DIRECTORY       Unix-domain socket location\n"));
#ifdef USE_SSL
	printf(_("  -l                 enable SSL connections\n"));
#endif
	printf(_("  -N MAX-CONNECT     maximum number of allowed connections\n"));
	printf(_("  -o OPTIONS         pass \"OPTIONS\" to each server process (obsolete)\n"));
	printf(_("  -p PORT            port number to listen on\n"));
	printf(_("  -s                 show statistics after each query\n"));
	printf(_("  -S WORK-MEM        set amount of memory for sorts (in kB)\n"));
	printf(_("  -V, --version      output version information, then exit\n"));
	printf(_("  --NAME=VALUE       set run-time parameter\n"));
	printf(_("  --describe-config  describe configuration parameters, then exit\n"));
	printf(_("  -?, --help         show this help, then exit\n"));

	printf(_("\nDeveloper options:\n"));
	printf(_("  -f s|i|n|m|h       forbid use of some plan types\n"));
	printf(_("  -n                 do not reinitialize shared memory after abnormal exit\n"));
	printf(_("  -O                 allow system table structure changes\n"));
	printf(_("  -P                 disable system indexes\n"));
	printf(_("  -t pa|pl|ex        show timings after each query\n"));
	printf(_("  -T                 send SIGSTOP to all backend processes if one dies\n"));
	printf(_("  -W NUM             wait NUM seconds to allow attach from a debugger\n"));

	printf(_("\nOptions for single-user mode:\n"));
	printf(_("  --single           selects single-user mode (must be first argument)\n"));
	printf(_("  DBNAME             database name (defaults to user name)\n"));
	printf(_("  -d 0-5             override debugging level\n"));
	printf(_("  -E                 echo statement before execution\n"));
	printf(_("  -j                 do not use newline as interactive query delimiter\n"));
	printf(_("  -r FILENAME        send stdout and stderr to given file\n"));

	printf(_("\nOptions for bootstrapping mode:\n"));
	printf(_("  --boot             selects bootstrapping mode (must be first argument)\n"));
	printf(_("  DBNAME             database name (mandatory argument in bootstrapping mode)\n"));
	printf(_("  -r FILENAME        send stdout and stderr to given file\n"));
	printf(_("  -x NUM             internal use\n"));

	printf(_("\nPlease read the documentation for the complete list of run-time\n"
			 "configuration settings and how to set them on the command line or in\n"
			 "the configuration file.\n\n"
			 "Report bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}