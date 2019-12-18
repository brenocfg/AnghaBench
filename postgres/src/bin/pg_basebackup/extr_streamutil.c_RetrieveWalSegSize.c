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
 int DEFAULT_XLOG_SEG_SIZE ; 
 int /*<<< orphan*/  IsValidWalSegSize (int) ; 
 scalar_t__ MINIMUM_VERSION_FOR_SHOW_CMD ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 scalar_t__ PQserverVersion (int /*<<< orphan*/ *) ; 
 int WalSegSz ; 
 int /*<<< orphan*/  ngettext (char*,char*,int) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

bool
RetrieveWalSegSize(PGconn *conn)
{
	PGresult   *res;
	char		xlog_unit[3];
	int			xlog_val,
				multiplier = 1;

	/* check connection existence */
	Assert(conn != NULL);

	/* for previous versions set the default xlog seg size */
	if (PQserverVersion(conn) < MINIMUM_VERSION_FOR_SHOW_CMD)
	{
		WalSegSz = DEFAULT_XLOG_SEG_SIZE;
		return true;
	}

	res = PQexec(conn, "SHOW wal_segment_size");
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		pg_log_error("could not send replication command \"%s\": %s",
					 "SHOW wal_segment_size", PQerrorMessage(conn));

		PQclear(res);
		return false;
	}
	if (PQntuples(res) != 1 || PQnfields(res) < 1)
	{
		pg_log_error("could not fetch WAL segment size: got %d rows and %d fields, expected %d rows and %d or more fields",
					 PQntuples(res), PQnfields(res), 1, 1);

		PQclear(res);
		return false;
	}

	/* fetch xlog value and unit from the result */
	if (sscanf(PQgetvalue(res, 0, 0), "%d%s", &xlog_val, xlog_unit) != 2)
	{
		pg_log_error("WAL segment size could not be parsed");
		return false;
	}

	/* set the multiplier based on unit to convert xlog_val to bytes */
	if (strcmp(xlog_unit, "MB") == 0)
		multiplier = 1024 * 1024;
	else if (strcmp(xlog_unit, "GB") == 0)
		multiplier = 1024 * 1024 * 1024;

	/* convert and set WalSegSz */
	WalSegSz = xlog_val * multiplier;

	if (!IsValidWalSegSize(WalSegSz))
	{
		pg_log_error(ngettext("WAL segment size must be a power of two between 1 MB and 1 GB, but the remote server reported a value of %d byte",
							  "WAL segment size must be a power of two between 1 MB and 1 GB, but the remote server reported a value of %d bytes",
							  WalSegSz),
					 WalSegSz);
		return false;
	}

	PQclear(res);
	return true;
}