#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_7__ {int /*<<< orphan*/  streamConn; scalar_t__ logical; } ;
typedef  TYPE_1__ WalReceiverConn ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int CRSSnapshotAction ;

/* Variables and functions */
#define  CRS_EXPORT_SNAPSHOT 130 
#define  CRS_NOEXPORT_SNAPSHOT 129 
#define  CRS_USE_SNAPSHOT 128 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/ * libpqrcv_PQexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pchomp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_lsn_in ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
libpqrcv_create_slot(WalReceiverConn *conn, const char *slotname,
					 bool temporary, CRSSnapshotAction snapshot_action,
					 XLogRecPtr *lsn)
{
	PGresult   *res;
	StringInfoData cmd;
	char	   *snapshot;

	initStringInfo(&cmd);

	appendStringInfo(&cmd, "CREATE_REPLICATION_SLOT \"%s\"", slotname);

	if (temporary)
		appendStringInfoString(&cmd, " TEMPORARY");

	if (conn->logical)
	{
		appendStringInfoString(&cmd, " LOGICAL pgoutput");
		switch (snapshot_action)
		{
			case CRS_EXPORT_SNAPSHOT:
				appendStringInfoString(&cmd, " EXPORT_SNAPSHOT");
				break;
			case CRS_NOEXPORT_SNAPSHOT:
				appendStringInfoString(&cmd, " NOEXPORT_SNAPSHOT");
				break;
			case CRS_USE_SNAPSHOT:
				appendStringInfoString(&cmd, " USE_SNAPSHOT");
				break;
		}
	}

	res = libpqrcv_PQexec(conn->streamConn, cmd.data);
	pfree(cmd.data);

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		PQclear(res);
		ereport(ERROR,
				(errmsg("could not create replication slot \"%s\": %s",
						slotname, pchomp(PQerrorMessage(conn->streamConn)))));
	}

	*lsn = DatumGetLSN(DirectFunctionCall1Coll(pg_lsn_in, InvalidOid,
											   CStringGetDatum(PQgetvalue(res, 0, 1))));
	if (!PQgetisnull(res, 0, 2))
		snapshot = pstrdup(PQgetvalue(res, 0, 2));
	else
		snapshot = NULL;

	PQclear(res);

	return snapshot;
}