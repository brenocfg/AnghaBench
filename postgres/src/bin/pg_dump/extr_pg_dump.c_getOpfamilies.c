#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* oid; void* tableoid; } ;
struct TYPE_19__ {void* name; int /*<<< orphan*/  dump; int /*<<< orphan*/  namespace; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_18__ {int remoteVersion; } ;
struct TYPE_17__ {TYPE_5__ dobj; void* rolname; } ;
struct TYPE_16__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ OpfamilyInfo ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_5__*) ; 
 int /*<<< orphan*/  DO_OPFAMILY ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  findNamespace (TYPE_4__*,void*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,void*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  username_subquery ; 

OpfamilyInfo *
getOpfamilies(Archive *fout, int *numOpfamilies)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	OpfamilyInfo *opfinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_opfname;
	int			i_opfnamespace;
	int			i_rolname;

	/* Before 8.3, there is no separate concept of opfamilies */
	if (fout->remoteVersion < 80300)
	{
		*numOpfamilies = 0;
		return NULL;
	}

	query = createPQExpBuffer();

	/*
	 * find all opfamilies, including builtin opfamilies; we filter out
	 * system-defined opfamilies at dump-out time.
	 */

	appendPQExpBuffer(query, "SELECT tableoid, oid, opfname, "
					  "opfnamespace, "
					  "(%s opfowner) AS rolname "
					  "FROM pg_opfamily",
					  username_subquery);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numOpfamilies = ntups;

	opfinfo = (OpfamilyInfo *) pg_malloc(ntups * sizeof(OpfamilyInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_opfname = PQfnumber(res, "opfname");
	i_opfnamespace = PQfnumber(res, "opfnamespace");
	i_rolname = PQfnumber(res, "rolname");

	for (i = 0; i < ntups; i++)
	{
		opfinfo[i].dobj.objType = DO_OPFAMILY;
		opfinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		opfinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&opfinfo[i].dobj);
		opfinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_opfname));
		opfinfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_opfnamespace)));
		opfinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(opfinfo[i].dobj), fout);

		/* Extensions do not currently have ACLs. */
		opfinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;

		if (strlen(opfinfo[i].rolname) == 0)
			pg_log_warning("owner of operator family \"%s\" appears to be invalid",
						   opfinfo[i].dobj.name);
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return opfinfo;
}