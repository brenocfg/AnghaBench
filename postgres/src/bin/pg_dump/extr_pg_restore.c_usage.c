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
usage(const char *progname)
{
	printf(_("%s restores a PostgreSQL database from an archive created by pg_dump.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... [FILE]\n"), progname);

	printf(_("\nGeneral options:\n"));
	printf(_("  -d, --dbname=NAME        connect to database name\n"));
	printf(_("  -f, --file=FILENAME      output file name (- for stdout)\n"));
	printf(_("  -F, --format=c|d|t       backup file format (should be automatic)\n"));
	printf(_("  -l, --list               print summarized TOC of the archive\n"));
	printf(_("  -v, --verbose            verbose mode\n"));
	printf(_("  -V, --version            output version information, then exit\n"));
	printf(_("  -?, --help               show this help, then exit\n"));

	printf(_("\nOptions controlling the restore:\n"));
	printf(_("  -a, --data-only              restore only the data, no schema\n"));
	printf(_("  -c, --clean                  clean (drop) database objects before recreating\n"));
	printf(_("  -C, --create                 create the target database\n"));
	printf(_("  -e, --exit-on-error          exit on error, default is to continue\n"));
	printf(_("  -I, --index=NAME             restore named index\n"));
	printf(_("  -j, --jobs=NUM               use this many parallel jobs to restore\n"));
	printf(_("  -L, --use-list=FILENAME      use table of contents from this file for\n"
			 "                               selecting/ordering output\n"));
	printf(_("  -n, --schema=NAME            restore only objects in this schema\n"));
	printf(_("  -N, --exclude-schema=NAME    do not restore objects in this schema\n"));
	printf(_("  -O, --no-owner               skip restoration of object ownership\n"));
	printf(_("  -P, --function=NAME(args)    restore named function\n"));
	printf(_("  -s, --schema-only            restore only the schema, no data\n"));
	printf(_("  -S, --superuser=NAME         superuser user name to use for disabling triggers\n"));
	printf(_("  -t, --table=NAME             restore named relation (table, view, etc.)\n"));
	printf(_("  -T, --trigger=NAME           restore named trigger\n"));
	printf(_("  -x, --no-privileges          skip restoration of access privileges (grant/revoke)\n"));
	printf(_("  -1, --single-transaction     restore as a single transaction\n"));
	printf(_("  --disable-triggers           disable triggers during data-only restore\n"));
	printf(_("  --enable-row-security        enable row security\n"));
	printf(_("  --if-exists                  use IF EXISTS when dropping objects\n"));
	printf(_("  --no-comments                do not restore comments\n"));
	printf(_("  --no-data-for-failed-tables  do not restore data of tables that could not be\n"
			 "                               created\n"));
	printf(_("  --no-publications            do not restore publications\n"));
	printf(_("  --no-security-labels         do not restore security labels\n"));
	printf(_("  --no-subscriptions           do not restore subscriptions\n"));
	printf(_("  --no-tablespaces             do not restore tablespace assignments\n"));
	printf(_("  --section=SECTION            restore named section (pre-data, data, or post-data)\n"));
	printf(_("  --strict-names               require table and/or schema include patterns to\n"
			 "                               match at least one entity each\n"));
	printf(_("  --use-set-session-authorization\n"
			 "                               use SET SESSION AUTHORIZATION commands instead of\n"
			 "                               ALTER OWNER commands to set ownership\n"));

	printf(_("\nConnection options:\n"));
	printf(_("  -h, --host=HOSTNAME      database server host or socket directory\n"));
	printf(_("  -p, --port=PORT          database server port number\n"));
	printf(_("  -U, --username=NAME      connect as specified database user\n"));
	printf(_("  -w, --no-password        never prompt for password\n"));
	printf(_("  -W, --password           force password prompt (should happen automatically)\n"));
	printf(_("  --role=ROLENAME          do SET ROLE before restore\n"));

	printf(_("\n"
			 "The options -I, -n, -N, -P, -t, -T, and --section can be combined and specified\n"
			 "multiple times to select multiple objects.\n"));
	printf(_("\nIf no input file name is supplied, then standard input is used.\n\n"));
	printf(_("Report bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}