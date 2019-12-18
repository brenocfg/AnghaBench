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
struct TYPE_12__ {TYPE_4__ dobj; void* rolname; void* oprcode; int /*<<< orphan*/  oprkind; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ OprInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_4__*) ; 
 int /*<<< orphan*/  DO_OPERATOR ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ *) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  findNamespace (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,void*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  username_subquery ; 

OprInfo *
getOperators(Archive *fout, int *numOprs)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query = createPQExpBuffer();
	OprInfo    *oprinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_oprname;
	int			i_oprnamespace;
	int			i_rolname;
	int			i_oprkind;
	int			i_oprcode;

	/*
	 * find all operators, including builtin operators; we filter out
	 * system-defined operators at dump-out time.
	 */

	appendPQExpBuffer(query, "SELECT tableoid, oid, oprname, "
					  "oprnamespace, "
					  "(%s oprowner) AS rolname, "
					  "oprkind, "
					  "oprcode::oid AS oprcode "
					  "FROM pg_operator",
					  username_subquery);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numOprs = ntups;

	oprinfo = (OprInfo *) pg_malloc(ntups * sizeof(OprInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_oprname = PQfnumber(res, "oprname");
	i_oprnamespace = PQfnumber(res, "oprnamespace");
	i_rolname = PQfnumber(res, "rolname");
	i_oprkind = PQfnumber(res, "oprkind");
	i_oprcode = PQfnumber(res, "oprcode");

	for (i = 0; i < ntups; i++)
	{
		oprinfo[i].dobj.objType = DO_OPERATOR;
		oprinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		oprinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&oprinfo[i].dobj);
		oprinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_oprname));
		oprinfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_oprnamespace)));
		oprinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		oprinfo[i].oprkind = (PQgetvalue(res, i, i_oprkind))[0];
		oprinfo[i].oprcode = atooid(PQgetvalue(res, i, i_oprcode));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(oprinfo[i].dobj), fout);

		/* Operators do not currently have ACLs. */
		oprinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;

		if (strlen(oprinfo[i].rolname) == 0)
			pg_log_warning("owner of operator \"%s\" appears to be invalid",
						   oprinfo[i].dobj.name);
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return oprinfo;
}