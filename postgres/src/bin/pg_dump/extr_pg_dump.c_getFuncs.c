#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {void* oid; void* tableoid; } ;
struct TYPE_27__ {void* name; int /*<<< orphan*/  dump; int /*<<< orphan*/  namespace; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_26__ {int remoteVersion; TYPE_4__* dopt; } ;
struct TYPE_25__ {scalar_t__ binary_upgrade; } ;
struct TYPE_24__ {int nargs; TYPE_6__ dobj; void* rolname; int /*<<< orphan*/ * argtypes; void* initrproacl; void* initproacl; void* rproacl; void* proacl; void* prorettype; void* lang; } ;
struct TYPE_23__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ FuncInfo ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_6__*) ; 
 int /*<<< orphan*/  DO_FUNC ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buildACLQueries (TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,char*,char*,char*,scalar_t__) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  findNamespace (TYPE_5__*,void*) ; 
 int /*<<< orphan*/  g_last_builtin_oid ; 
 int /*<<< orphan*/  parseOidArray (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_log_warning (char*,void*) ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ pg_malloc0 (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ strlen (void*) ; 
 int /*<<< orphan*/  username_subquery ; 

FuncInfo *
getFuncs(Archive *fout, int *numFuncs)
{
	DumpOptions *dopt = fout->dopt;
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query = createPQExpBuffer();
	FuncInfo   *finfo;
	int			i_tableoid;
	int			i_oid;
	int			i_proname;
	int			i_pronamespace;
	int			i_rolname;
	int			i_prolang;
	int			i_pronargs;
	int			i_proargtypes;
	int			i_prorettype;
	int			i_proacl;
	int			i_rproacl;
	int			i_initproacl;
	int			i_initrproacl;

	/*
	 * Find all interesting functions.  This is a bit complicated:
	 *
	 * 1. Always exclude aggregates; those are handled elsewhere.
	 *
	 * 2. Always exclude functions that are internally dependent on something
	 * else, since presumably those will be created as a result of creating
	 * the something else.  This currently acts only to suppress constructor
	 * functions for range types (so we only need it in 9.2 and up).  Note
	 * this is OK only because the constructors don't have any dependencies
	 * the range type doesn't have; otherwise we might not get creation
	 * ordering correct.
	 *
	 * 3. Otherwise, we normally exclude functions in pg_catalog.  However, if
	 * they're members of extensions and we are in binary-upgrade mode then
	 * include them, since we want to dump extension members individually in
	 * that mode.  Also, if they are used by casts or transforms then we need
	 * to gather the information about them, though they won't be dumped if
	 * they are built-in.  Also, in 9.6 and up, include functions in
	 * pg_catalog if they have an ACL different from what's shown in
	 * pg_init_privs.
	 */
	if (fout->remoteVersion >= 90600)
	{
		PQExpBuffer acl_subquery = createPQExpBuffer();
		PQExpBuffer racl_subquery = createPQExpBuffer();
		PQExpBuffer initacl_subquery = createPQExpBuffer();
		PQExpBuffer initracl_subquery = createPQExpBuffer();
		const char *not_agg_check;

		buildACLQueries(acl_subquery, racl_subquery, initacl_subquery,
						initracl_subquery, "p.proacl", "p.proowner", "'f'",
						dopt->binary_upgrade);

		not_agg_check = (fout->remoteVersion >= 110000 ? "p.prokind <> 'a'"
						 : "NOT p.proisagg");

		appendPQExpBuffer(query,
						  "SELECT p.tableoid, p.oid, p.proname, p.prolang, "
						  "p.pronargs, p.proargtypes, p.prorettype, "
						  "%s AS proacl, "
						  "%s AS rproacl, "
						  "%s AS initproacl, "
						  "%s AS initrproacl, "
						  "p.pronamespace, "
						  "(%s p.proowner) AS rolname "
						  "FROM pg_proc p "
						  "LEFT JOIN pg_init_privs pip ON "
						  "(p.oid = pip.objoid "
						  "AND pip.classoid = 'pg_proc'::regclass "
						  "AND pip.objsubid = 0) "
						  "WHERE %s"
						  "\n  AND NOT EXISTS (SELECT 1 FROM pg_depend "
						  "WHERE classid = 'pg_proc'::regclass AND "
						  "objid = p.oid AND deptype = 'i')"
						  "\n  AND ("
						  "\n  pronamespace != "
						  "(SELECT oid FROM pg_namespace "
						  "WHERE nspname = 'pg_catalog')"
						  "\n  OR EXISTS (SELECT 1 FROM pg_cast"
						  "\n  WHERE pg_cast.oid > %u "
						  "\n  AND p.oid = pg_cast.castfunc)"
						  "\n  OR EXISTS (SELECT 1 FROM pg_transform"
						  "\n  WHERE pg_transform.oid > %u AND "
						  "\n  (p.oid = pg_transform.trffromsql"
						  "\n  OR p.oid = pg_transform.trftosql))",
						  acl_subquery->data,
						  racl_subquery->data,
						  initacl_subquery->data,
						  initracl_subquery->data,
						  username_subquery,
						  not_agg_check,
						  g_last_builtin_oid,
						  g_last_builtin_oid);
		if (dopt->binary_upgrade)
			appendPQExpBufferStr(query,
								 "\n  OR EXISTS(SELECT 1 FROM pg_depend WHERE "
								 "classid = 'pg_proc'::regclass AND "
								 "objid = p.oid AND "
								 "refclassid = 'pg_extension'::regclass AND "
								 "deptype = 'e')");
		appendPQExpBufferStr(query,
							 "\n  OR p.proacl IS DISTINCT FROM pip.initprivs");
		appendPQExpBufferChar(query, ')');

		destroyPQExpBuffer(acl_subquery);
		destroyPQExpBuffer(racl_subquery);
		destroyPQExpBuffer(initacl_subquery);
		destroyPQExpBuffer(initracl_subquery);
	}
	else
	{
		appendPQExpBuffer(query,
						  "SELECT tableoid, oid, proname, prolang, "
						  "pronargs, proargtypes, prorettype, proacl, "
						  "NULL as rproacl, "
						  "NULL as initproacl, NULL AS initrproacl, "
						  "pronamespace, "
						  "(%s proowner) AS rolname "
						  "FROM pg_proc p "
						  "WHERE NOT proisagg",
						  username_subquery);
		if (fout->remoteVersion >= 90200)
			appendPQExpBufferStr(query,
								 "\n  AND NOT EXISTS (SELECT 1 FROM pg_depend "
								 "WHERE classid = 'pg_proc'::regclass AND "
								 "objid = p.oid AND deptype = 'i')");
		appendPQExpBuffer(query,
						  "\n  AND ("
						  "\n  pronamespace != "
						  "(SELECT oid FROM pg_namespace "
						  "WHERE nspname = 'pg_catalog')"
						  "\n  OR EXISTS (SELECT 1 FROM pg_cast"
						  "\n  WHERE pg_cast.oid > '%u'::oid"
						  "\n  AND p.oid = pg_cast.castfunc)",
						  g_last_builtin_oid);

		if (fout->remoteVersion >= 90500)
			appendPQExpBuffer(query,
							  "\n  OR EXISTS (SELECT 1 FROM pg_transform"
							  "\n  WHERE pg_transform.oid > '%u'::oid"
							  "\n  AND (p.oid = pg_transform.trffromsql"
							  "\n  OR p.oid = pg_transform.trftosql))",
							  g_last_builtin_oid);

		if (dopt->binary_upgrade && fout->remoteVersion >= 90100)
			appendPQExpBufferStr(query,
								 "\n  OR EXISTS(SELECT 1 FROM pg_depend WHERE "
								 "classid = 'pg_proc'::regclass AND "
								 "objid = p.oid AND "
								 "refclassid = 'pg_extension'::regclass AND "
								 "deptype = 'e')");
		appendPQExpBufferChar(query, ')');
	}

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	*numFuncs = ntups;

	finfo = (FuncInfo *) pg_malloc0(ntups * sizeof(FuncInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_proname = PQfnumber(res, "proname");
	i_pronamespace = PQfnumber(res, "pronamespace");
	i_rolname = PQfnumber(res, "rolname");
	i_prolang = PQfnumber(res, "prolang");
	i_pronargs = PQfnumber(res, "pronargs");
	i_proargtypes = PQfnumber(res, "proargtypes");
	i_prorettype = PQfnumber(res, "prorettype");
	i_proacl = PQfnumber(res, "proacl");
	i_rproacl = PQfnumber(res, "rproacl");
	i_initproacl = PQfnumber(res, "initproacl");
	i_initrproacl = PQfnumber(res, "initrproacl");

	for (i = 0; i < ntups; i++)
	{
		finfo[i].dobj.objType = DO_FUNC;
		finfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		finfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&finfo[i].dobj);
		finfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_proname));
		finfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_pronamespace)));
		finfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		finfo[i].lang = atooid(PQgetvalue(res, i, i_prolang));
		finfo[i].prorettype = atooid(PQgetvalue(res, i, i_prorettype));
		finfo[i].proacl = pg_strdup(PQgetvalue(res, i, i_proacl));
		finfo[i].rproacl = pg_strdup(PQgetvalue(res, i, i_rproacl));
		finfo[i].initproacl = pg_strdup(PQgetvalue(res, i, i_initproacl));
		finfo[i].initrproacl = pg_strdup(PQgetvalue(res, i, i_initrproacl));
		finfo[i].nargs = atoi(PQgetvalue(res, i, i_pronargs));
		if (finfo[i].nargs == 0)
			finfo[i].argtypes = NULL;
		else
		{
			finfo[i].argtypes = (Oid *) pg_malloc(finfo[i].nargs * sizeof(Oid));
			parseOidArray(PQgetvalue(res, i, i_proargtypes),
						  finfo[i].argtypes, finfo[i].nargs);
		}

		/* Decide whether we want to dump it */
		selectDumpableObject(&(finfo[i].dobj), fout);

		/* Do not try to dump ACL if no ACL exists. */
		if (PQgetisnull(res, i, i_proacl) && PQgetisnull(res, i, i_rproacl) &&
			PQgetisnull(res, i, i_initproacl) &&
			PQgetisnull(res, i, i_initrproacl))
			finfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;

		if (strlen(finfo[i].rolname) == 0)
			pg_log_warning("owner of function \"%s\" appears to be invalid",
						   finfo[i].dobj.name);
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return finfo;
}