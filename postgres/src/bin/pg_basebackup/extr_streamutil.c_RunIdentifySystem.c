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
typedef  int uint64 ;
typedef  int uint32 ;
typedef  int XLogRecPtr ;
typedef  int /*<<< orphan*/  TimeLineID ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,int*) ; 

bool
RunIdentifySystem(PGconn *conn, char **sysid, TimeLineID *starttli,
				  XLogRecPtr *startpos, char **db_name)
{
	PGresult   *res;
	uint32		hi,
				lo;

	/* Check connection existence */
	Assert(conn != NULL);

	res = PQexec(conn, "IDENTIFY_SYSTEM");
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		pg_log_error("could not send replication command \"%s\": %s",
					 "IDENTIFY_SYSTEM", PQerrorMessage(conn));

		PQclear(res);
		return false;
	}
	if (PQntuples(res) != 1 || PQnfields(res) < 3)
	{
		pg_log_error("could not identify system: got %d rows and %d fields, expected %d rows and %d or more fields",
					 PQntuples(res), PQnfields(res), 1, 3);

		PQclear(res);
		return false;
	}

	/* Get system identifier */
	if (sysid != NULL)
		*sysid = pg_strdup(PQgetvalue(res, 0, 0));

	/* Get timeline ID to start streaming from */
	if (starttli != NULL)
		*starttli = atoi(PQgetvalue(res, 0, 1));

	/* Get LSN start position if necessary */
	if (startpos != NULL)
	{
		if (sscanf(PQgetvalue(res, 0, 2), "%X/%X", &hi, &lo) != 2)
		{
			pg_log_error("could not parse write-ahead log location \"%s\"",
						 PQgetvalue(res, 0, 2));

			PQclear(res);
			return false;
		}
		*startpos = ((uint64) hi) << 32 | lo;
	}

	/* Get database name, only available in 9.4 and newer versions */
	if (db_name != NULL)
	{
		*db_name = NULL;
		if (PQserverVersion(conn) >= 90400)
		{
			if (PQnfields(res) < 4)
			{
				pg_log_error("could not identify system: got %d rows and %d fields, expected %d rows and %d or more fields",
							 PQntuples(res), PQnfields(res), 1, 4);

				PQclear(res);
				return false;
			}
			if (!PQgetisnull(res, 0, 3))
				*db_name = pg_strdup(PQgetvalue(res, 0, 3));
		}
	}

	PQclear(res);
	return true;
}