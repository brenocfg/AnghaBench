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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ MINIMUM_VERSION_FOR_GROUP_ACCESS ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetDataDirectoryCreatePerm (int) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static bool
RetrieveDataDirCreatePerm(PGconn *conn)
{
	PGresult   *res;
	int			data_directory_mode;

	/* check connection existence */
	Assert(conn != NULL);

	/* for previous versions leave the default group access */
	if (PQserverVersion(conn) < MINIMUM_VERSION_FOR_GROUP_ACCESS)
		return true;

	res = PQexec(conn, "SHOW data_directory_mode");
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		pg_log_error("could not send replication command \"%s\": %s",
					 "SHOW data_directory_mode", PQerrorMessage(conn));

		PQclear(res);
		return false;
	}
	if (PQntuples(res) != 1 || PQnfields(res) < 1)
	{
		pg_log_error("could not fetch group access flag: got %d rows and %d fields, expected %d rows and %d or more fields",
					 PQntuples(res), PQnfields(res), 1, 1);

		PQclear(res);
		return false;
	}

	if (sscanf(PQgetvalue(res, 0, 0), "%o", &data_directory_mode) != 1)
	{
		pg_log_error("group access flag could not be parsed: %s",
					 PQgetvalue(res, 0, 0));

		PQclear(res);
		return false;
	}

	SetDataDirectoryCreatePerm(data_directory_mode);

	PQclear(res);
	return true;
}