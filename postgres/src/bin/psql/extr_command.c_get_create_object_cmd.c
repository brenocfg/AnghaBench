#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int sversion; int /*<<< orphan*/  encoding; int /*<<< orphan*/  db; } ;
struct TYPE_12__ {char* data; int len; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int EditableObjectType ;

/* Variables and functions */
#define  EditableFunction 131 
#define  EditableView 130 
 scalar_t__ PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexec (int /*<<< orphan*/ ,char*) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ PQresultStatus (int /*<<< orphan*/ *) ; 
#define  RELKIND_MATVIEW 129 
#define  RELKIND_VIEW 128 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendReloptionsArray (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  echo_hidden_command (char*) ; 
 char* fmtId (char*) ; 
 int /*<<< orphan*/  minimal_error_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ pset ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  standard_strings () ; 
 int strlen (char*) ; 

__attribute__((used)) static bool
get_create_object_cmd(EditableObjectType obj_type, Oid oid,
					  PQExpBuffer buf)
{
	bool		result = true;
	PQExpBuffer query = createPQExpBuffer();
	PGresult   *res;

	switch (obj_type)
	{
		case EditableFunction:
			printfPQExpBuffer(query,
							  "SELECT pg_catalog.pg_get_functiondef(%u)",
							  oid);
			break;

		case EditableView:

			/*
			 * pg_get_viewdef() just prints the query, so we must prepend
			 * CREATE for ourselves.  We must fully qualify the view name to
			 * ensure the right view gets replaced.  Also, check relation kind
			 * to be sure it's a view.
			 *
			 * Starting with 9.2, views may have reloptions (security_barrier)
			 * and from 9.4 onwards they may also have WITH [LOCAL|CASCADED]
			 * CHECK OPTION.  These are not part of the view definition
			 * returned by pg_get_viewdef() and so need to be retrieved
			 * separately.  Materialized views (introduced in 9.3) may have
			 * arbitrary storage parameter reloptions.
			 */
			if (pset.sversion >= 90400)
			{
				printfPQExpBuffer(query,
								  "SELECT nspname, relname, relkind, "
								  "pg_catalog.pg_get_viewdef(c.oid, true), "
								  "pg_catalog.array_remove(pg_catalog.array_remove(c.reloptions,'check_option=local'),'check_option=cascaded') AS reloptions, "
								  "CASE WHEN 'check_option=local' = ANY (c.reloptions) THEN 'LOCAL'::text "
								  "WHEN 'check_option=cascaded' = ANY (c.reloptions) THEN 'CASCADED'::text ELSE NULL END AS checkoption "
								  "FROM pg_catalog.pg_class c "
								  "LEFT JOIN pg_catalog.pg_namespace n "
								  "ON c.relnamespace = n.oid WHERE c.oid = %u",
								  oid);
			}
			else if (pset.sversion >= 90200)
			{
				printfPQExpBuffer(query,
								  "SELECT nspname, relname, relkind, "
								  "pg_catalog.pg_get_viewdef(c.oid, true), "
								  "c.reloptions AS reloptions, "
								  "NULL AS checkoption "
								  "FROM pg_catalog.pg_class c "
								  "LEFT JOIN pg_catalog.pg_namespace n "
								  "ON c.relnamespace = n.oid WHERE c.oid = %u",
								  oid);
			}
			else
			{
				printfPQExpBuffer(query,
								  "SELECT nspname, relname, relkind, "
								  "pg_catalog.pg_get_viewdef(c.oid, true), "
								  "NULL AS reloptions, "
								  "NULL AS checkoption "
								  "FROM pg_catalog.pg_class c "
								  "LEFT JOIN pg_catalog.pg_namespace n "
								  "ON c.relnamespace = n.oid WHERE c.oid = %u",
								  oid);
			}
			break;
	}

	if (!echo_hidden_command(query->data))
	{
		destroyPQExpBuffer(query);
		return false;
	}
	res = PQexec(pset.db, query->data);
	if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) == 1)
	{
		resetPQExpBuffer(buf);
		switch (obj_type)
		{
			case EditableFunction:
				appendPQExpBufferStr(buf, PQgetvalue(res, 0, 0));
				break;

			case EditableView:
				{
					char	   *nspname = PQgetvalue(res, 0, 0);
					char	   *relname = PQgetvalue(res, 0, 1);
					char	   *relkind = PQgetvalue(res, 0, 2);
					char	   *viewdef = PQgetvalue(res, 0, 3);
					char	   *reloptions = PQgetvalue(res, 0, 4);
					char	   *checkoption = PQgetvalue(res, 0, 5);

					/*
					 * If the backend ever supports CREATE OR REPLACE
					 * MATERIALIZED VIEW, allow that here; but as of today it
					 * does not, so editing a matview definition in this way
					 * is impossible.
					 */
					switch (relkind[0])
					{
#ifdef NOT_USED
						case RELKIND_MATVIEW:
							appendPQExpBufferStr(buf, "CREATE OR REPLACE MATERIALIZED VIEW ");
							break;
#endif
						case RELKIND_VIEW:
							appendPQExpBufferStr(buf, "CREATE OR REPLACE VIEW ");
							break;
						default:
							pg_log_error("\"%s.%s\" is not a view",
										 nspname, relname);
							result = false;
							break;
					}
					appendPQExpBuffer(buf, "%s.", fmtId(nspname));
					appendPQExpBufferStr(buf, fmtId(relname));

					/* reloptions, if not an empty array "{}" */
					if (reloptions != NULL && strlen(reloptions) > 2)
					{
						appendPQExpBufferStr(buf, "\n WITH (");
						if (!appendReloptionsArray(buf, reloptions, "",
												   pset.encoding,
												   standard_strings()))
						{
							pg_log_error("could not parse reloptions array");
							result = false;
						}
						appendPQExpBufferChar(buf, ')');
					}

					/* View definition from pg_get_viewdef (a SELECT query) */
					appendPQExpBuffer(buf, " AS\n%s", viewdef);

					/* Get rid of the semicolon that pg_get_viewdef appends */
					if (buf->len > 0 && buf->data[buf->len - 1] == ';')
						buf->data[--(buf->len)] = '\0';

					/* WITH [LOCAL|CASCADED] CHECK OPTION */
					if (checkoption && checkoption[0] != '\0')
						appendPQExpBuffer(buf, "\n WITH %s CHECK OPTION",
										  checkoption);
				}
				break;
		}
		/* Make sure result ends with a newline */
		if (buf->len > 0 && buf->data[buf->len - 1] != '\n')
			appendPQExpBufferChar(buf, '\n');
	}
	else
	{
		minimal_error_message(res);
		result = false;
	}

	PQclear(res);
	destroyPQExpBuffer(query);

	return result;
}