#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  db; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int EditableObjectType ;

/* Variables and functions */
#define  EditableFunction 129 
#define  EditableView 128 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendStringLiteralConn (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atooid (int /*<<< orphan*/ ) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  echo_hidden_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minimal_error_message (int /*<<< orphan*/ *) ; 
 TYPE_2__ pset ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 

__attribute__((used)) static bool
lookup_object_oid(EditableObjectType obj_type, const char *desc,
				  Oid *obj_oid)
{
	bool		result = true;
	PQExpBuffer query = createPQExpBuffer();
	PGresult   *res;

	switch (obj_type)
	{
		case EditableFunction:

			/*
			 * We have a function description, e.g. "x" or "x(int)".  Issue a
			 * query to retrieve the function's OID using a cast to regproc or
			 * regprocedure (as appropriate).
			 */
			appendPQExpBufferStr(query, "SELECT ");
			appendStringLiteralConn(query, desc, pset.db);
			appendPQExpBuffer(query, "::pg_catalog.%s::pg_catalog.oid",
							  strchr(desc, '(') ? "regprocedure" : "regproc");
			break;

		case EditableView:

			/*
			 * Convert view name (possibly schema-qualified) to OID.  Note:
			 * this code doesn't check if the relation is actually a view.
			 * We'll detect that in get_create_object_cmd().
			 */
			appendPQExpBufferStr(query, "SELECT ");
			appendStringLiteralConn(query, desc, pset.db);
			appendPQExpBufferStr(query, "::pg_catalog.regclass::pg_catalog.oid");
			break;
	}

	if (!echo_hidden_command(query->data))
	{
		destroyPQExpBuffer(query);
		return false;
	}
	res = PQexec(pset.db, query->data);
	if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) == 1)
		*obj_oid = atooid(PQgetvalue(res, 0, 0));
	else
	{
		minimal_error_message(res);
		result = false;
	}

	PQclear(res);
	destroyPQExpBuffer(query);

	return result;
}