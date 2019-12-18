#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  name; } ;
struct TYPE_23__ {TYPE_2__ dobj; } ;
typedef  TYPE_3__ TypeInfo ;
struct TYPE_27__ {int remoteVersion; } ;
struct TYPE_21__ {void* oid; void* tableoid; } ;
struct TYPE_20__ {int /*<<< orphan*/  dump; int /*<<< orphan*/  name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_26__ {TYPE_19__ dobj; void* casttarget; void* castsource; void* castmethod; void* castcontext; void* castfunc; } ;
struct TYPE_25__ {int /*<<< orphan*/  data; } ;
struct TYPE_24__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ PQExpBufferData ;
typedef  TYPE_5__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_6__ CastInfo ;
typedef  TYPE_7__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_19__*) ; 
 int /*<<< orphan*/  DO_CAST ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 void** PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_5__*,char*) ; 
 void* atooid (void**) ; 
 TYPE_5__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_5__*) ; 
 TYPE_3__* findTypeByOid (void*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_4__*) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  selectDumpableCast (TYPE_6__*,TYPE_7__*) ; 

CastInfo *
getCasts(Archive *fout, int *numCasts)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query = createPQExpBuffer();
	CastInfo   *castinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_castsource;
	int			i_casttarget;
	int			i_castfunc;
	int			i_castcontext;
	int			i_castmethod;

	if (fout->remoteVersion >= 80400)
	{
		appendPQExpBufferStr(query, "SELECT tableoid, oid, "
							 "castsource, casttarget, castfunc, castcontext, "
							 "castmethod "
							 "FROM pg_cast ORDER BY 3,4");
	}
	else
	{
		appendPQExpBufferStr(query, "SELECT tableoid, oid, "
							 "castsource, casttarget, castfunc, castcontext, "
							 "CASE WHEN castfunc = 0 THEN 'b' ELSE 'f' END AS castmethod "
							 "FROM pg_cast ORDER BY 3,4");
	}

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	*numCasts = ntups;

	castinfo = (CastInfo *) pg_malloc(ntups * sizeof(CastInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_castsource = PQfnumber(res, "castsource");
	i_casttarget = PQfnumber(res, "casttarget");
	i_castfunc = PQfnumber(res, "castfunc");
	i_castcontext = PQfnumber(res, "castcontext");
	i_castmethod = PQfnumber(res, "castmethod");

	for (i = 0; i < ntups; i++)
	{
		PQExpBufferData namebuf;
		TypeInfo   *sTypeInfo;
		TypeInfo   *tTypeInfo;

		castinfo[i].dobj.objType = DO_CAST;
		castinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		castinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&castinfo[i].dobj);
		castinfo[i].castsource = atooid(PQgetvalue(res, i, i_castsource));
		castinfo[i].casttarget = atooid(PQgetvalue(res, i, i_casttarget));
		castinfo[i].castfunc = atooid(PQgetvalue(res, i, i_castfunc));
		castinfo[i].castcontext = *(PQgetvalue(res, i, i_castcontext));
		castinfo[i].castmethod = *(PQgetvalue(res, i, i_castmethod));

		/*
		 * Try to name cast as concatenation of typnames.  This is only used
		 * for purposes of sorting.  If we fail to find either type, the name
		 * will be an empty string.
		 */
		initPQExpBuffer(&namebuf);
		sTypeInfo = findTypeByOid(castinfo[i].castsource);
		tTypeInfo = findTypeByOid(castinfo[i].casttarget);
		if (sTypeInfo && tTypeInfo)
			appendPQExpBuffer(&namebuf, "%s %s",
							  sTypeInfo->dobj.name, tTypeInfo->dobj.name);
		castinfo[i].dobj.name = namebuf.data;

		/* Decide whether we want to dump it */
		selectDumpableCast(&(castinfo[i]), fout);

		/* Casts do not currently have ACLs. */
		castinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return castinfo;
}