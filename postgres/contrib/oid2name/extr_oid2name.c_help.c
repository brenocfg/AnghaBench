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
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 

__attribute__((used)) static void
help(const char *progname)
{
	printf("%s helps examining the file structure used by PostgreSQL.\n\n"
		   "Usage:\n"
		   "  %s [OPTION]...\n"
		   "\nOptions:\n"
		   "  -f, --filenode=FILENODE    show info for table with given file node\n"
		   "  -i, --indexes              show indexes and sequences too\n"
		   "  -o, --oid=OID              show info for table with given OID\n"
		   "  -q, --quiet                quiet (don't show headers)\n"
		   "  -s, --tablespaces          show all tablespaces\n"
		   "  -S, --system-objects       show system objects too\n"
		   "  -t, --table=TABLE          show info for named table\n"
		   "  -V, --version              output version information, then exit\n"
		   "  -x, --extended             extended (show additional columns)\n"
		   "  -?, --help                 show this help, then exit\n"
		   "\nConnection options:\n"
		   "  -d, --dbname=DBNAME        database to connect to\n"
		   "  -h, --host=HOSTNAME        database server host or socket directory\n"
		   "  -H                         same as -h, deprecated option\n"
		   "  -p, --port=PORT            database server port number\n"
		   "  -U, --username=USERNAME    connect as specified database user\n"
		   "\nThe default action is to show all database OIDs.\n\n"
		   "Report bugs to <pgsql-bugs@lists.postgresql.org>.\n",
		   progname, progname);
}