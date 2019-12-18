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
typedef  int /*<<< orphan*/  backslashResult ;
typedef  int /*<<< orphan*/  PsqlScanState ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  PSQL_CMD_ERROR ; 
 int /*<<< orphan*/  PSQL_CMD_SKIP_LINE ; 
 int /*<<< orphan*/  PSQL_CMD_UNKNOWN ; 
 int describeAccessMethods (char*,int) ; 
 int describeAggregates (char*,int,int) ; 
 int describeFunctions (char const*,char*,int,int) ; 
 int describeOperators (char*,int,int) ; 
 int describePublications (char*) ; 
 int describeRoles (char*,int,int) ; 
 int describeSubscriptions (char*,int) ; 
 int describeTableDetails (char*,int,int) ; 
 int describeTablespaces (char*,int) ; 
 int describeTypes (char*,int,int) ; 
 int do_lo_list () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ignore_slash_options (int /*<<< orphan*/ ) ; 
 int listCasts (char*,int) ; 
 int listCollations (char*,int,int) ; 
 int listConversions (char*,int,int) ; 
 int listDbRoleSettings (char*,char*) ; 
 int listDefaultACLs (char*) ; 
 int listDomains (char*,int,int) ; 
 int listEventTriggers (char*,int) ; 
 int listExtensionContents (char*) ; 
 int listExtensions (char*) ; 
 int listForeignDataWrappers (char*,int) ; 
 int listForeignServers (char*,int) ; 
 int listForeignTables (char*,int) ; 
 int listLanguages (char*,int,int) ; 
 int listPartitionedTables (char const*,char*,int) ; 
 int listPublications (char*) ; 
 int listSchemas (char*,int,int) ; 
 int listTSConfigs (char*,int) ; 
 int listTSDictionaries (char*,int) ; 
 int listTSParsers (char*,int) ; 
 int listTSTemplates (char*,int) ; 
 int listTables (char const*,char*,int,int) ; 
 int listUserMappings (char*,int) ; 
 int objectDescription (char*,int) ; 
 int permissionsList (char*) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static backslashResult
exec_command_d(PsqlScanState scan_state, bool active_branch, const char *cmd)
{
	backslashResult status = PSQL_CMD_SKIP_LINE;
	bool		success = true;

	if (active_branch)
	{
		char	   *pattern;
		bool		show_verbose,
					show_system;

		/* We don't do SQLID reduction on the pattern yet */
		pattern = psql_scan_slash_option(scan_state,
										 OT_NORMAL, NULL, true);

		show_verbose = strchr(cmd, '+') ? true : false;
		show_system = strchr(cmd, 'S') ? true : false;

		switch (cmd[1])
		{
			case '\0':
			case '+':
			case 'S':
				if (pattern)
					success = describeTableDetails(pattern, show_verbose, show_system);
				else
					/* standard listing of interesting things */
					success = listTables("tvmsE", NULL, show_verbose, show_system);
				break;
			case 'A':
				success = describeAccessMethods(pattern, show_verbose);
				break;
			case 'a':
				success = describeAggregates(pattern, show_verbose, show_system);
				break;
			case 'b':
				success = describeTablespaces(pattern, show_verbose);
				break;
			case 'c':
				success = listConversions(pattern, show_verbose, show_system);
				break;
			case 'C':
				success = listCasts(pattern, show_verbose);
				break;
			case 'd':
				if (strncmp(cmd, "ddp", 3) == 0)
					success = listDefaultACLs(pattern);
				else
					success = objectDescription(pattern, show_system);
				break;
			case 'D':
				success = listDomains(pattern, show_verbose, show_system);
				break;
			case 'f':			/* function subsystem */
				switch (cmd[2])
				{
					case '\0':
					case '+':
					case 'S':
					case 'a':
					case 'n':
					case 'p':
					case 't':
					case 'w':
						success = describeFunctions(&cmd[2], pattern, show_verbose, show_system);
						break;
					default:
						status = PSQL_CMD_UNKNOWN;
						break;
				}
				break;
			case 'g':
				/* no longer distinct from \du */
				success = describeRoles(pattern, show_verbose, show_system);
				break;
			case 'l':
				success = do_lo_list();
				break;
			case 'L':
				success = listLanguages(pattern, show_verbose, show_system);
				break;
			case 'n':
				success = listSchemas(pattern, show_verbose, show_system);
				break;
			case 'o':
				success = describeOperators(pattern, show_verbose, show_system);
				break;
			case 'O':
				success = listCollations(pattern, show_verbose, show_system);
				break;
			case 'p':
				success = permissionsList(pattern);
				break;
			case 'P':
				{
					switch (cmd[2])
					{
						case '\0':
						case '+':
						case 't':
						case 'i':
						case 'n':
							success = listPartitionedTables(&cmd[2], pattern, show_verbose);
							break;
						default:
							status = PSQL_CMD_UNKNOWN;
							break;
					}
				}
				break;
			case 'T':
				success = describeTypes(pattern, show_verbose, show_system);
				break;
			case 't':
			case 'v':
			case 'm':
			case 'i':
			case 's':
			case 'E':
				success = listTables(&cmd[1], pattern, show_verbose, show_system);
				break;
			case 'r':
				if (cmd[2] == 'd' && cmd[3] == 's')
				{
					char	   *pattern2 = NULL;

					if (pattern)
						pattern2 = psql_scan_slash_option(scan_state,
														  OT_NORMAL, NULL, true);
					success = listDbRoleSettings(pattern, pattern2);

					if (pattern2)
						free(pattern2);
				}
				else
					status = PSQL_CMD_UNKNOWN;
				break;
			case 'R':
				switch (cmd[2])
				{
					case 'p':
						if (show_verbose)
							success = describePublications(pattern);
						else
							success = listPublications(pattern);
						break;
					case 's':
						success = describeSubscriptions(pattern, show_verbose);
						break;
					default:
						status = PSQL_CMD_UNKNOWN;
				}
				break;
			case 'u':
				success = describeRoles(pattern, show_verbose, show_system);
				break;
			case 'F':			/* text search subsystem */
				switch (cmd[2])
				{
					case '\0':
					case '+':
						success = listTSConfigs(pattern, show_verbose);
						break;
					case 'p':
						success = listTSParsers(pattern, show_verbose);
						break;
					case 'd':
						success = listTSDictionaries(pattern, show_verbose);
						break;
					case 't':
						success = listTSTemplates(pattern, show_verbose);
						break;
					default:
						status = PSQL_CMD_UNKNOWN;
						break;
				}
				break;
			case 'e':			/* SQL/MED subsystem */
				switch (cmd[2])
				{
					case 's':
						success = listForeignServers(pattern, show_verbose);
						break;
					case 'u':
						success = listUserMappings(pattern, show_verbose);
						break;
					case 'w':
						success = listForeignDataWrappers(pattern, show_verbose);
						break;
					case 't':
						success = listForeignTables(pattern, show_verbose);
						break;
					default:
						status = PSQL_CMD_UNKNOWN;
						break;
				}
				break;
			case 'x':			/* Extensions */
				if (show_verbose)
					success = listExtensionContents(pattern);
				else
					success = listExtensions(pattern);
				break;
			case 'y':			/* Event Triggers */
				success = listEventTriggers(pattern, show_verbose);
				break;
			default:
				status = PSQL_CMD_UNKNOWN;
		}

		if (pattern)
			free(pattern);
	}
	else
		ignore_slash_options(scan_state);

	if (!success)
		status = PSQL_CMD_ERROR;

	return status;
}