#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,int,...) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

bool
CreateReplicationSlot(PGconn *conn, const char *slot_name, const char *plugin,
					  bool is_temporary, bool is_physical, bool reserve_wal,
					  bool slot_exists_ok)
{
	PQExpBuffer query;
	PGresult   *res;

	query = createPQExpBuffer();

	Assert((is_physical && plugin == NULL) ||
		   (!is_physical && plugin != NULL));
	Assert(slot_name != NULL);

	/* Build query */
	appendPQExpBuffer(query, "CREATE_REPLICATION_SLOT \"%s\"", slot_name);
	if (is_temporary)
		appendPQExpBufferStr(query, " TEMPORARY");
	if (is_physical)
	{
		appendPQExpBufferStr(query, " PHYSICAL");
		if (reserve_wal)
			appendPQExpBufferStr(query, " RESERVE_WAL");
	}
	else
	{
		appendPQExpBuffer(query, " LOGICAL \"%s\"", plugin);
		if (PQserverVersion(conn) >= 100000)
			/* pg_recvlogical doesn't use an exported snapshot, so suppress */
			appendPQExpBufferStr(query, " NOEXPORT_SNAPSHOT");
	}

	res = PQexec(conn, query->data);
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		const char *sqlstate = PQresultErrorField(res, PG_DIAG_SQLSTATE);

		if (slot_exists_ok &&
			sqlstate &&
			strcmp(sqlstate, ERRCODE_DUPLICATE_OBJECT) == 0)
		{
			destroyPQExpBuffer(query);
			PQclear(res);
			return true;
		}
		else
		{
			pg_log_error("could not send replication command \"%s\": %s",
						 query->data, PQerrorMessage(conn));

			destroyPQExpBuffer(query);
			PQclear(res);
			return false;
		}
	}

	if (PQntuples(res) != 1 || PQnfields(res) != 4)
	{
		pg_log_error("could not create replication slot \"%s\": got %d rows and %d fields, expected %d rows and %d fields",
					 slot_name,
					 PQntuples(res), PQnfields(res), 1, 4);

		destroyPQExpBuffer(query);
		PQclear(res);
		return false;
	}

	destroyPQExpBuffer(query);
	PQclear(res);
	return true;
}