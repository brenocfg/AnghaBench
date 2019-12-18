#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int remoteVersion; int minRemoteVersion; int maxRemoteVersion; int isStandby; int /*<<< orphan*/  remoteVersionStr; } ;
struct TYPE_5__ {TYPE_1__ public; int /*<<< orphan*/  archiveRemoteVersion; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_2__ ArchiveHandle ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PG_VERSION ; 
 int PG_VERSION_NUM ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* PQparameterStatus (int /*<<< orphan*/ ,char*) ; 
 int PQserverVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strdup (char const*) ; 
 int /*<<< orphan*/  progname ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
_check_database_version(ArchiveHandle *AH)
{
	const char *remoteversion_str;
	int			remoteversion;
	PGresult   *res;

	remoteversion_str = PQparameterStatus(AH->connection, "server_version");
	remoteversion = PQserverVersion(AH->connection);
	if (remoteversion == 0 || !remoteversion_str)
		fatal("could not get server_version from libpq");

	AH->public.remoteVersionStr = pg_strdup(remoteversion_str);
	AH->public.remoteVersion = remoteversion;
	if (!AH->archiveRemoteVersion)
		AH->archiveRemoteVersion = AH->public.remoteVersionStr;

	if (remoteversion != PG_VERSION_NUM
		&& (remoteversion < AH->public.minRemoteVersion ||
			remoteversion > AH->public.maxRemoteVersion))
	{
		pg_log_error("server version: %s; %s version: %s",
					 remoteversion_str, progname, PG_VERSION);
		fatal("aborting because of server version mismatch");
	}

	/*
	 * When running against 9.0 or later, check if we are in recovery mode,
	 * which means we are on a hot standby.
	 */
	if (remoteversion >= 90000)
	{
		res = ExecuteSqlQueryForSingleRow((Archive *) AH, "SELECT pg_catalog.pg_is_in_recovery()");

		AH->public.isStandby = (strcmp(PQgetvalue(res, 0, 0), "t") == 0);
		PQclear(res);
	}
	else
		AH->public.isStandby = false;
}