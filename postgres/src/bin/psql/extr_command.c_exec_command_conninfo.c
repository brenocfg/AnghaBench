#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  backslashResult ;
struct TYPE_2__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 char* PQdb (int /*<<< orphan*/ ) ; 
 char* PQhost (int /*<<< orphan*/ ) ; 
 char* PQhostaddr (int /*<<< orphan*/ ) ; 
 char* PQport (int /*<<< orphan*/ ) ; 
 char* PQuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 char* _ (char*) ; 
 scalar_t__ is_absolute_path (char*) ; 
 int /*<<< orphan*/  printGSSInfo () ; 
 int /*<<< orphan*/  printSSLInfo () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__ pset ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static backslashResult
exec_command_conninfo(PsqlScanState scan_state, bool active_branch)
{
	if (active_branch)
	{
		char	   *db = PQdb(pset.db);

		if (db == NULL)
			printf(_("You are currently not connected to a database.\n"));
		else
		{
			char	   *host = PQhost(pset.db);
			char	   *hostaddr = PQhostaddr(pset.db);

			/*
			 * If the host is an absolute path, the connection is via socket
			 * unless overridden by hostaddr
			 */
			if (is_absolute_path(host))
			{
				if (hostaddr && *hostaddr)
					printf(_("You are connected to database \"%s\" as user \"%s\" on address \"%s\" at port \"%s\".\n"),
						   db, PQuser(pset.db), hostaddr, PQport(pset.db));
				else
					printf(_("You are connected to database \"%s\" as user \"%s\" via socket in \"%s\" at port \"%s\".\n"),
						   db, PQuser(pset.db), host, PQport(pset.db));
			}
			else
			{
				if (hostaddr && *hostaddr && strcmp(host, hostaddr) != 0)
					printf(_("You are connected to database \"%s\" as user \"%s\" on host \"%s\" (address \"%s\") at port \"%s\".\n"),
						   db, PQuser(pset.db), host, hostaddr, PQport(pset.db));
				else
					printf(_("You are connected to database \"%s\" as user \"%s\" on host \"%s\" at port \"%s\".\n"),
						   db, PQuser(pset.db), host, PQport(pset.db));
			}
			printSSLInfo();
			printGSSInfo();
		}
	}

	return PSQL_CMD_SKIP_LINE;
}