#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ PGRES_COMMAND_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PQnfields (int /*<<< orphan*/ *) ; 
 scalar_t__ PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char const*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,scalar_t__,...) ; 

bool
DropReplicationSlot(PGconn *conn, const char *slot_name)
{
	PQExpBuffer query;
	PGresult   *res;

	Assert(slot_name != NULL);

	query = createPQExpBuffer();

	/* Build query */
	appendPQExpBuffer(query, "DROP_REPLICATION_SLOT \"%s\"",
					  slot_name);
	res = PQexec(conn, query->data);
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		pg_log_error("could not send replication command \"%s\": %s",
					 query->data, PQerrorMessage(conn));

		destroyPQExpBuffer(query);
		PQclear(res);
		return false;
	}

	if (PQntuples(res) != 0 || PQnfields(res) != 0)
	{
		pg_log_error("could not drop replication slot \"%s\": got %d rows and %d fields, expected %d rows and %d fields",
					 slot_name,
					 PQntuples(res), PQnfields(res), 0, 0);

		destroyPQExpBuffer(query);
		PQclear(res);
		return false;
	}

	destroyPQExpBuffer(query);
	PQclear(res);
	return true;
}