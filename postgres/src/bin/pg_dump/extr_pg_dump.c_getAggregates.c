#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {void* oid; void* tableoid; } ;
struct TYPE_29__ {int /*<<< orphan*/  dump; void* name; int /*<<< orphan*/  namespace; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_24__ {int nargs; TYPE_7__ dobj; int /*<<< orphan*/ * argtypes; void* initrproacl; void* initproacl; void* rproacl; void* proacl; void* prorettype; void* lang; void* rolname; } ;
struct TYPE_28__ {TYPE_2__ aggfn; } ;
struct TYPE_27__ {int remoteVersion; TYPE_4__* dopt; } ;
struct TYPE_26__ {scalar_t__ binary_upgrade; } ;
struct TYPE_25__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;
typedef  TYPE_6__ AggInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_7__*) ; 
 int /*<<< orphan*/  DO_AGG ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_3__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buildACLQueries (TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,char*,char*,char*,scalar_t__) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  findNamespace (TYPE_5__*,void*) ; 
 int /*<<< orphan*/  parseOidArray (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_log_warning (char*,void*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_7__*,TYPE_5__*) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  username_subquery ; 

AggInfo *
getAggregates(Archive *fout, int *numAggs)
{
	DumpOptions *dopt = fout->dopt;
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query = createPQExpBuffer();
	AggInfo    *agginfo;
	int			i_tableoid;
	int			i_oid;
	int			i_aggname;
	int			i_aggnamespace;
	int			i_pronargs;
	int			i_proargtypes;
	int			i_rolname;
	int			i_aggacl;
	int			i_raggacl;
	int			i_initaggacl;
	int			i_initraggacl;

	/*
	 * Find all interesting aggregates.  See comment in getFuncs() for the
	 * rationale behind the filtering logic.
	 */
	if (fout->remoteVersion >= 90600)
	{
		PQExpBuffer acl_subquery = createPQExpBuffer();
		PQExpBuffer racl_subquery = createPQExpBuffer();
		PQExpBuffer initacl_subquery = createPQExpBuffer();
		PQExpBuffer initracl_subquery = createPQExpBuffer();
		const char *agg_check;

		buildACLQueries(acl_subquery, racl_subquery, initacl_subquery,
						initracl_subquery, "p.proacl", "p.proowner", "'f'",
						dopt->binary_upgrade);

		agg_check = (fout->remoteVersion >= 110000 ? "p.prokind = 'a'"
					 : "p.proisagg");

		appendPQExpBuffer(query, "SELECT p.tableoid, p.oid, "
						  "p.proname AS aggname, "
						  "p.pronamespace AS aggnamespace, "
						  "p.pronargs, p.proargtypes, "
						  "(%s p.proowner) AS rolname, "
						  "%s AS aggacl, "
						  "%s AS raggacl, "
						  "%s AS initaggacl, "
						  "%s AS initraggacl "
						  "FROM pg_proc p "
						  "LEFT JOIN pg_init_privs pip ON "
						  "(p.oid = pip.objoid "
						  "AND pip.classoid = 'pg_proc'::regclass "
						  "AND pip.objsubid = 0) "
						  "WHERE %s AND ("
						  "p.pronamespace != "
						  "(SELECT oid FROM pg_namespace "
						  "WHERE nspname = 'pg_catalog') OR "
						  "p.proacl IS DISTINCT FROM pip.initprivs",
						  username_subquery,
						  acl_subquery->data,
						  racl_subquery->data,
						  initacl_subquery->data,
						  initracl_subquery->data,
						  agg_check);
		if (dopt->binary_upgrade)
			appendPQExpBufferStr(query,
								 " OR EXISTS(SELECT 1 FROM pg_depend WHERE "
								 "classid = 'pg_proc'::regclass AND "
								 "objid = p.oid AND "
								 "refclassid = 'pg_extension'::regclass AND "
								 "deptype = 'e')");
		appendPQExpBufferChar(query, ')');

		destroyPQExpBuffer(acl_subquery);
		destroyPQExpBuffer(racl_subquery);
		destroyPQExpBuffer(initacl_subquery);
		destroyPQExpBuffer(initracl_subquery);
	}
	else if (fout->remoteVersion >= 80200)
	{
		appendPQExpBuffer(query, "SELECT tableoid, oid, proname AS aggname, "
						  "pronamespace AS aggnamespace, "
						  "pronargs, proargtypes, "
						  "(%s proowner) AS rolname, "
						  "proacl AS aggacl, "
						  "NULL AS raggacl, "
						  "NULL AS initaggacl, NULL AS initraggacl "
						  "FROM pg_proc p "
						  "WHERE proisagg AND ("
						  "pronamespace != "
						  "(SELECT oid FROM pg_namespace "
						  "WHERE nspname = 'pg_catalog')",
						  username_subquery);
		if (dopt->binary_upgrade && fout->remoteVersion >= 90100)
			appendPQExpBufferStr(query,
								 " OR EXISTS(SELECT 1 FROM pg_depend WHERE "
								 "classid = 'pg_proc'::regclass AND "
								 "objid = p.oid AND "
								 "refclassid = 'pg_extension'::regclass AND "
								 "deptype = 'e')");
		appendPQExpBufferChar(query, ')');
	}
	else
	{
		appendPQExpBuffer(query, "SELECT tableoid, oid, proname AS aggname, "
						  "pronamespace AS aggnamespace, "
						  "CASE WHEN proargtypes[0] = 'pg_catalog.\"any\"'::pg_catalog.regtype THEN 0 ELSE 1 END AS pronargs, "
						  "proargtypes, "
						  "(%s proowner) AS rolname, "
						  "proacl AS aggacl, "
						  "NULL AS raggacl, "
						  "NULL AS initaggacl, NULL AS initraggacl "
						  "FROM pg_proc "
						  "WHERE proisagg "
						  "AND pronamespace != "
						  "(SELECT oid FROM pg_namespace WHERE nspname = 'pg_catalog')",
						  username_subquery);
	}

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numAggs = ntups;

	agginfo = (AggInfo *) pg_malloc(ntups * sizeof(AggInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_aggname = PQfnumber(res, "aggname");
	i_aggnamespace = PQfnumber(res, "aggnamespace");
	i_pronargs = PQfnumber(res, "pronargs");
	i_proargtypes = PQfnumber(res, "proargtypes");
	i_rolname = PQfnumber(res, "rolname");
	i_aggacl = PQfnumber(res, "aggacl");
	i_raggacl = PQfnumber(res, "raggacl");
	i_initaggacl = PQfnumber(res, "initaggacl");
	i_initraggacl = PQfnumber(res, "initraggacl");

	for (i = 0; i < ntups; i++)
	{
		agginfo[i].aggfn.dobj.objType = DO_AGG;
		agginfo[i].aggfn.dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		agginfo[i].aggfn.dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&agginfo[i].aggfn.dobj);
		agginfo[i].aggfn.dobj.name = pg_strdup(PQgetvalue(res, i, i_aggname));
		agginfo[i].aggfn.dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_aggnamespace)));
		agginfo[i].aggfn.rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		if (strlen(agginfo[i].aggfn.rolname) == 0)
			pg_log_warning("owner of aggregate function \"%s\" appears to be invalid",
						   agginfo[i].aggfn.dobj.name);
		agginfo[i].aggfn.lang = InvalidOid; /* not currently interesting */
		agginfo[i].aggfn.prorettype = InvalidOid;	/* not saved */
		agginfo[i].aggfn.proacl = pg_strdup(PQgetvalue(res, i, i_aggacl));
		agginfo[i].aggfn.rproacl = pg_strdup(PQgetvalue(res, i, i_raggacl));
		agginfo[i].aggfn.initproacl = pg_strdup(PQgetvalue(res, i, i_initaggacl));
		agginfo[i].aggfn.initrproacl = pg_strdup(PQgetvalue(res, i, i_initraggacl));
		agginfo[i].aggfn.nargs = atoi(PQgetvalue(res, i, i_pronargs));
		if (agginfo[i].aggfn.nargs == 0)
			agginfo[i].aggfn.argtypes = NULL;
		else
		{
			agginfo[i].aggfn.argtypes = (Oid *) pg_malloc(agginfo[i].aggfn.nargs * sizeof(Oid));
			parseOidArray(PQgetvalue(res, i, i_proargtypes),
						  agginfo[i].aggfn.argtypes,
						  agginfo[i].aggfn.nargs);
		}

		/* Decide whether we want to dump it */
		selectDumpableObject(&(agginfo[i].aggfn.dobj), fout);

		/* Do not try to dump ACL if no ACL exists. */
		if (PQgetisnull(res, i, i_aggacl) && PQgetisnull(res, i, i_raggacl) &&
			PQgetisnull(res, i, i_initaggacl) &&
			PQgetisnull(res, i, i_initraggacl))
			agginfo[i].aggfn.dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return agginfo;
}