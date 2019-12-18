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
	printf(_("%s creates a new PostgreSQL role.\n\n"), progname);
	printf(_("Usage:\n"));
	printf(_("  %s [OPTION]... [ROLENAME]\n"), progname);
	printf(_("\nOptions:\n"));
	printf(_("  -c, --connection-limit=N  connection limit for role (default: no limit)\n"));
	printf(_("  -d, --createdb            role can create new databases\n"));
	printf(_("  -D, --no-createdb         role cannot create databases (default)\n"));
	printf(_("  -e, --echo                show the commands being sent to the server\n"));
	printf(_("  -g, --role=ROLE           new role will be a member of this role\n"));
	printf(_("  -i, --inherit             role inherits privileges of roles it is a\n"
			 "                            member of (default)\n"));
	printf(_("  -I, --no-inherit          role does not inherit privileges\n"));
	printf(_("  -l, --login               role can login (default)\n"));
	printf(_("  -L, --no-login            role cannot login\n"));
	printf(_("  -P, --pwprompt            assign a password to new role\n"));
	printf(_("  -r, --createrole          role can create new roles\n"));
	printf(_("  -R, --no-createrole       role cannot create roles (default)\n"));
	printf(_("  -s, --superuser           role will be superuser\n"));
	printf(_("  -S, --no-superuser        role will not be superuser (default)\n"));
	printf(_("  -V, --version             output version information, then exit\n"));
	printf(_("  --interactive             prompt for missing role name and attributes rather\n"
			 "                            than using defaults\n"));
	printf(_("  --replication             role can initiate replication\n"));
	printf(_("  --no-replication          role cannot initiate replication\n"));
	printf(_("  -?, --help                show this help, then exit\n"));
	printf(_("\nConnection options:\n"));
	printf(_("  -h, --host=HOSTNAME       database server host or socket directory\n"));
	printf(_("  -p, --port=PORT           database server port\n"));
	printf(_("  -U, --username=USERNAME   user name to connect as (not the one to create)\n"));
	printf(_("  -w, --no-password         never prompt for password\n"));
	printf(_("  -W, --password            force password prompt\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}