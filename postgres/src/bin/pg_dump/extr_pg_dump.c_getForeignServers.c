#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {void* oid; void* tableoid; } ;
struct TYPE_24__ {int /*<<< orphan*/  dump; int /*<<< orphan*/ * namespace; void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_23__ {int remoteVersion; TYPE_4__* dopt; } ;
struct TYPE_22__ {int /*<<< orphan*/  binary_upgrade; } ;
struct TYPE_21__ {TYPE_6__ dobj; void* initrsrvacl; void* initsrvacl; void* rsrvacl; void* srvacl; void* srvoptions; void* srvversion; void* srvtype; void* srvfdw; void* rolname; } ;
struct TYPE_20__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ ForeignServerInfo ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_6__*) ; 
 int /*<<< orphan*/  DO_FOREIGN_SERVER ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buildACLQueries (TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  username_subquery ; 

ForeignServerInfo *
getForeignServers(Archive *fout, int *numForeignServers)
{
	DumpOptions *dopt = fout->dopt;
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	ForeignServerInfo *srvinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_srvname;
	int			i_rolname;
	int			i_srvfdw;
	int			i_srvtype;
	int			i_srvversion;
	int			i_srvacl;
	int			i_rsrvacl;
	int			i_initsrvacl;
	int			i_initrsrvacl;
	int			i_srvoptions;

	/* Before 8.4, there are no foreign servers */
	if (fout->remoteVersion < 80400)
	{
		*numForeignServers = 0;
		return NULL;
	}

	query = createPQExpBuffer();

	if (fout->remoteVersion >= 90600)
	{
		PQExpBuffer acl_subquery = createPQExpBuffer();
		PQExpBuffer racl_subquery = createPQExpBuffer();
		PQExpBuffer initacl_subquery = createPQExpBuffer();
		PQExpBuffer initracl_subquery = createPQExpBuffer();

		buildACLQueries(acl_subquery, racl_subquery, initacl_subquery,
						initracl_subquery, "f.srvacl", "f.srvowner", "'S'",
						dopt->binary_upgrade);

		appendPQExpBuffer(query, "SELECT f.tableoid, f.oid, f.srvname, "
						  "(%s f.srvowner) AS rolname, "
						  "f.srvfdw, f.srvtype, f.srvversion, "
						  "%s AS srvacl, "
						  "%s AS rsrvacl, "
						  "%s AS initsrvacl, "
						  "%s AS initrsrvacl, "
						  "array_to_string(ARRAY("
						  "SELECT quote_ident(option_name) || ' ' || "
						  "quote_literal(option_value) "
						  "FROM pg_options_to_table(f.srvoptions) "
						  "ORDER BY option_name"
						  "), E',\n    ') AS srvoptions "
						  "FROM pg_foreign_server f "
						  "LEFT JOIN pg_init_privs pip "
						  "ON (f.oid = pip.objoid "
						  "AND pip.classoid = 'pg_foreign_server'::regclass "
						  "AND pip.objsubid = 0) ",
						  username_subquery,
						  acl_subquery->data,
						  racl_subquery->data,
						  initacl_subquery->data,
						  initracl_subquery->data);

		destroyPQExpBuffer(acl_subquery);
		destroyPQExpBuffer(racl_subquery);
		destroyPQExpBuffer(initacl_subquery);
		destroyPQExpBuffer(initracl_subquery);
	}
	else
	{
		appendPQExpBuffer(query, "SELECT tableoid, oid, srvname, "
						  "(%s srvowner) AS rolname, "
						  "srvfdw, srvtype, srvversion, srvacl, "
						  "NULL AS rsrvacl, "
						  "NULL AS initsrvacl, NULL AS initrsrvacl, "
						  "array_to_string(ARRAY("
						  "SELECT quote_ident(option_name) || ' ' || "
						  "quote_literal(option_value) "
						  "FROM pg_options_to_table(srvoptions) "
						  "ORDER BY option_name"
						  "), E',\n    ') AS srvoptions "
						  "FROM pg_foreign_server",
						  username_subquery);
	}

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numForeignServers = ntups;

	srvinfo = (ForeignServerInfo *) pg_malloc(ntups * sizeof(ForeignServerInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_srvname = PQfnumber(res, "srvname");
	i_rolname = PQfnumber(res, "rolname");
	i_srvfdw = PQfnumber(res, "srvfdw");
	i_srvtype = PQfnumber(res, "srvtype");
	i_srvversion = PQfnumber(res, "srvversion");
	i_srvacl = PQfnumber(res, "srvacl");
	i_rsrvacl = PQfnumber(res, "rsrvacl");
	i_initsrvacl = PQfnumber(res, "initsrvacl");
	i_initrsrvacl = PQfnumber(res, "initrsrvacl");
	i_srvoptions = PQfnumber(res, "srvoptions");

	for (i = 0; i < ntups; i++)
	{
		srvinfo[i].dobj.objType = DO_FOREIGN_SERVER;
		srvinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		srvinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&srvinfo[i].dobj);
		srvinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_srvname));
		srvinfo[i].dobj.namespace = NULL;
		srvinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		srvinfo[i].srvfdw = atooid(PQgetvalue(res, i, i_srvfdw));
		srvinfo[i].srvtype = pg_strdup(PQgetvalue(res, i, i_srvtype));
		srvinfo[i].srvversion = pg_strdup(PQgetvalue(res, i, i_srvversion));
		srvinfo[i].srvoptions = pg_strdup(PQgetvalue(res, i, i_srvoptions));
		srvinfo[i].srvacl = pg_strdup(PQgetvalue(res, i, i_srvacl));
		srvinfo[i].rsrvacl = pg_strdup(PQgetvalue(res, i, i_rsrvacl));
		srvinfo[i].initsrvacl = pg_strdup(PQgetvalue(res, i, i_initsrvacl));
		srvinfo[i].initrsrvacl = pg_strdup(PQgetvalue(res, i, i_initrsrvacl));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(srvinfo[i].dobj), fout);

		/* Do not try to dump ACL if no ACL exists. */
		if (PQgetisnull(res, i, i_srvacl) && PQgetisnull(res, i, i_rsrvacl) &&
			PQgetisnull(res, i, i_initsrvacl) &&
			PQgetisnull(res, i, i_initrsrvacl))
			srvinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return srvinfo;
}