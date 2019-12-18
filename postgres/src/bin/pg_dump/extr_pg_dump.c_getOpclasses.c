#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* oid; void* tableoid; } ;
struct TYPE_13__ {void* name; int /*<<< orphan*/  dump; int /*<<< orphan*/  namespace; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_12__ {TYPE_4__ dobj; void* rolname; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ OpclassInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_4__*) ; 
 int /*<<< orphan*/  DO_OPCLASS ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  findNamespace (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,void*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  username_subquery ; 

OpclassInfo *
getOpclasses(Archive *fout, int *numOpclasses)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query = createPQExpBuffer();
	OpclassInfo *opcinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_opcname;
	int			i_opcnamespace;
	int			i_rolname;

	/*
	 * find all opclasses, including builtin opclasses; we filter out
	 * system-defined opclasses at dump-out time.
	 */

	appendPQExpBuffer(query, "SELECT tableoid, oid, opcname, "
					  "opcnamespace, "
					  "(%s opcowner) AS rolname "
					  "FROM pg_opclass",
					  username_subquery);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numOpclasses = ntups;

	opcinfo = (OpclassInfo *) pg_malloc(ntups * sizeof(OpclassInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_opcname = PQfnumber(res, "opcname");
	i_opcnamespace = PQfnumber(res, "opcnamespace");
	i_rolname = PQfnumber(res, "rolname");

	for (i = 0; i < ntups; i++)
	{
		opcinfo[i].dobj.objType = DO_OPCLASS;
		opcinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		opcinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&opcinfo[i].dobj);
		opcinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_opcname));
		opcinfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_opcnamespace)));
		opcinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(opcinfo[i].dobj), fout);

		/* Op Classes do not currently have ACLs. */
		opcinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;

		if (strlen(opcinfo[i].rolname) == 0)
			pg_log_warning("owner of operator class \"%s\" appears to be invalid",
						   opcinfo[i].dobj.name);
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return opcinfo;
}