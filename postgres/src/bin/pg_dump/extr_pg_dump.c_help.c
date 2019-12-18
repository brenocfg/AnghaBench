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
	printf(_("%s dumps a database as a text file or to other formats.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... [DBNAME]\n"), progname);

	printf(_("\nGeneral options:\n"));
	printf(_("  -f, --file=FILENAME          output file or directory name\n"));
	printf(_("  -F, --format=c|d|t|p         output file format (custom, directory, tar,\n"
			 "                               plain text (default))\n"));
	printf(_("  -j, --jobs=NUM               use this many parallel jobs to dump\n"));
	printf(_("  -v, --verbose                verbose mode\n"));
	printf(_("  -V, --version                output version information, then exit\n"));
	printf(_("  -Z, --compress=0-9           compression level for compressed formats\n"));
	printf(_("  --lock-wait-timeout=TIMEOUT  fail after waiting TIMEOUT for a table lock\n"));
	printf(_("  --no-sync                    do not wait for changes to be written safely to disk\n"));
	printf(_("  -?, --help                   show this help, then exit\n"));

	printf(_("\nOptions controlling the output content:\n"));
	printf(_("  -a, --data-only              dump only the data, not the schema\n"));
	printf(_("  -b, --blobs                  include large objects in dump\n"));
	printf(_("  -B, --no-blobs               exclude large objects in dump\n"));
	printf(_("  -c, --clean                  clean (drop) database objects before recreating\n"));
	printf(_("  -C, --create                 include commands to create database in dump\n"));
	printf(_("  -E, --encoding=ENCODING      dump the data in encoding ENCODING\n"));
	printf(_("  -n, --schema=PATTERN         dump the specified schema(s) only\n"));
	printf(_("  -N, --exclude-schema=PATTERN do NOT dump the specified schema(s)\n"));
	printf(_("  -O, --no-owner               skip restoration of object ownership in\n"
			 "                               plain-text format\n"));
	printf(_("  -s, --schema-only            dump only the schema, no data\n"));
	printf(_("  -S, --superuser=NAME         superuser user name to use in plain-text format\n"));
	printf(_("  -t, --table=PATTERN          dump the specified table(s) only\n"));
	printf(_("  -T, --exclude-table=PATTERN  do NOT dump the specified table(s)\n"));
	printf(_("  -x, --no-privileges          do not dump privileges (grant/revoke)\n"));
	printf(_("  --binary-upgrade             for use by upgrade utilities only\n"));
	printf(_("  --column-inserts             dump data as INSERT commands with column names\n"));
	printf(_("  --disable-dollar-quoting     disable dollar quoting, use SQL standard quoting\n"));
	printf(_("  --disable-triggers           disable triggers during data-only restore\n"));
	printf(_("  --enable-row-security        enable row security (dump only content user has\n"
			 "                               access to)\n"));
	printf(_("  --exclude-table-data=PATTERN do NOT dump data for the specified table(s)\n"));
	printf(_("  --extra-float-digits=NUM     override default setting for extra_float_digits\n"));
	printf(_("  --if-exists                  use IF EXISTS when dropping objects\n"));
	printf(_("  --inserts                    dump data as INSERT commands, rather than COPY\n"));
	printf(_("  --load-via-partition-root    load partitions via the root table\n"));
	printf(_("  --no-comments                do not dump comments\n"));
	printf(_("  --no-publications            do not dump publications\n"));
	printf(_("  --no-security-labels         do not dump security label assignments\n"));
	printf(_("  --no-subscriptions           do not dump subscriptions\n"));
	printf(_("  --no-synchronized-snapshots  do not use synchronized snapshots in parallel jobs\n"));
	printf(_("  --no-tablespaces             do not dump tablespace assignments\n"));
	printf(_("  --no-unlogged-table-data     do not dump unlogged table data\n"));
	printf(_("  --on-conflict-do-nothing     add ON CONFLICT DO NOTHING to INSERT commands\n"));
	printf(_("  --quote-all-identifiers      quote all identifiers, even if not key words\n"));
	printf(_("  --rows-per-insert=NROWS      number of rows per INSERT; implies --inserts\n"));
	printf(_("  --section=SECTION            dump named section (pre-data, data, or post-data)\n"));
	printf(_("  --serializable-deferrable    wait until the dump can run without anomalies\n"));
	printf(_("  --snapshot=SNAPSHOT          use given snapshot for the dump\n"));
	printf(_("  --strict-names               require table and/or schema include patterns to\n"
			 "                               match at least one entity each\n"));
	printf(_("  --use-set-session-authorization\n"
			 "                               use SET SESSION AUTHORIZATION commands instead of\n"
			 "                               ALTER OWNER commands to set ownership\n"));

	printf(_("\nConnection options:\n"));
	printf(_("  -d, --dbname=DBNAME      database to dump\n"));
	printf(_("  -h, --host=HOSTNAME      database server host or socket directory\n"));
	printf(_("  -p, --port=PORT          database server port number\n"));
	printf(_("  -U, --username=NAME      connect as specified database user\n"));
	printf(_("  -w, --no-password        never prompt for password\n"));
	printf(_("  -W, --password           force password prompt (should happen automatically)\n"));
	printf(_("  --role=ROLENAME          do SET ROLE before dump\n"));

	printf(_("\nIf no database name is supplied, then the PGDATABASE environment\n"
			 "variable value is used.\n\n"));
	printf(_("Report bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}