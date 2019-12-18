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
do_help(void)
{
	printf(_("%s is a utility to initialize, start, stop, or control a PostgreSQL server.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s init[db]   [-D DATADIR] [-s] [-o OPTIONS]\n"), progname);
	printf(_("  %s start      [-D DATADIR] [-l FILENAME] [-W] [-t SECS] [-s]\n"
			 "                    [-o OPTIONS] [-p PATH] [-c]\n"), progname);
	printf(_("  %s stop       [-D DATADIR] [-m SHUTDOWN-MODE] [-W] [-t SECS] [-s]\n"), progname);
	printf(_("  %s restart    [-D DATADIR] [-m SHUTDOWN-MODE] [-W] [-t SECS] [-s]\n"
			 "                    [-o OPTIONS] [-c]\n"), progname);
	printf(_("  %s reload     [-D DATADIR] [-s]\n"), progname);
	printf(_("  %s status     [-D DATADIR]\n"), progname);
	printf(_("  %s promote    [-D DATADIR] [-W] [-t SECS] [-s]\n"), progname);
	printf(_("  %s logrotate  [-D DATADIR] [-s]\n"), progname);
	printf(_("  %s kill       SIGNALNAME PID\n"), progname);
#ifdef WIN32
	printf(_("  %s register   [-D DATADIR] [-N SERVICENAME] [-U USERNAME] [-P PASSWORD]\n"
			 "                    [-S START-TYPE] [-e SOURCE] [-W] [-t SECS] [-s] [-o OPTIONS]\n"), progname);
	printf(_("  %s unregister [-N SERVICENAME]\n"), progname);
#endif

	printf(_("\nCommon options:\n"));
	printf(_("  -D, --pgdata=DATADIR   location of the database storage area\n"));
#ifdef WIN32
	printf(_("  -e SOURCE              event source for logging when running as a service\n"));
#endif
	printf(_("  -s, --silent           only print errors, no informational messages\n"));
	printf(_("  -t, --timeout=SECS     seconds to wait when using -w option\n"));
	printf(_("  -V, --version          output version information, then exit\n"));
	printf(_("  -w, --wait             wait until operation completes (default)\n"));
	printf(_("  -W, --no-wait          do not wait until operation completes\n"));
	printf(_("  -?, --help             show this help, then exit\n"));
	printf(_("If the -D option is omitted, the environment variable PGDATA is used.\n"));

	printf(_("\nOptions for start or restart:\n"));
#if defined(HAVE_GETRLIMIT) && defined(RLIMIT_CORE)
	printf(_("  -c, --core-files       allow postgres to produce core files\n"));
#else
	printf(_("  -c, --core-files       not applicable on this platform\n"));
#endif
	printf(_("  -l, --log=FILENAME     write (or append) server log to FILENAME\n"));
	printf(_("  -o, --options=OPTIONS  command line options to pass to postgres\n"
			 "                         (PostgreSQL server executable) or initdb\n"));
	printf(_("  -p PATH-TO-POSTGRES    normally not necessary\n"));
	printf(_("\nOptions for stop or restart:\n"));
	printf(_("  -m, --mode=MODE        MODE can be \"smart\", \"fast\", or \"immediate\"\n"));

	printf(_("\nShutdown modes are:\n"));
	printf(_("  smart       quit after all clients have disconnected\n"));
	printf(_("  fast        quit directly, with proper shutdown (default)\n"));
	printf(_("  immediate   quit without complete shutdown; will lead to recovery on restart\n"));

	printf(_("\nAllowed signal names for kill:\n"));
	printf("  ABRT HUP INT KILL QUIT TERM USR1 USR2\n");

#ifdef WIN32
	printf(_("\nOptions for register and unregister:\n"));
	printf(_("  -N SERVICENAME  service name with which to register PostgreSQL server\n"));
	printf(_("  -P PASSWORD     password of account to register PostgreSQL server\n"));
	printf(_("  -U USERNAME     user name of account to register PostgreSQL server\n"));
	printf(_("  -S START-TYPE   service start type to register PostgreSQL server\n"));

	printf(_("\nStart types are:\n"));
	printf(_("  auto       start service automatically during system startup (default)\n"));
	printf(_("  demand     start service on demand\n"));
#endif

	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}