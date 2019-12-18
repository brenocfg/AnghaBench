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
struct TYPE_21__ {TYPE_6__ dobj; void* initrfdwacl; void* initfdwacl; void* rfdwacl; void* fdwacl; void* fdwoptions; void* fdwvalidator; void* fdwhandler; void* rolname; } ;
struct TYPE_20__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ FdwInfo ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_6__*) ; 
 int /*<<< orphan*/  DO_FDW ; 
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

FdwInfo *
getForeignDataWrappers(Archive *fout, int *numForeignDataWrappers)
{
	DumpOptions *dopt = fout->dopt;
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	FdwInfo    *fdwinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_fdwname;
	int			i_rolname;
	int			i_fdwhandler;
	int			i_fdwvalidator;
	int			i_fdwacl;
	int			i_rfdwacl;
	int			i_initfdwacl;
	int			i_initrfdwacl;
	int			i_fdwoptions;

	/* Before 8.4, there are no foreign-data wrappers */
	if (fout->remoteVersion < 80400)
	{
		*numForeignDataWrappers = 0;
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
						initracl_subquery, "f.fdwacl", "f.fdwowner", "'F'",
						dopt->binary_upgrade);

		appendPQExpBuffer(query, "SELECT f.tableoid, f.oid, f.fdwname, "
						  "(%s f.fdwowner) AS rolname, "
						  "f.fdwhandler::pg_catalog.regproc, "
						  "f.fdwvalidator::pg_catalog.regproc, "
						  "%s AS fdwacl, "
						  "%s AS rfdwacl, "
						  "%s AS initfdwacl, "
						  "%s AS initrfdwacl, "
						  "array_to_string(ARRAY("
						  "SELECT quote_ident(option_name) || ' ' || "
						  "quote_literal(option_value) "
						  "FROM pg_options_to_table(f.fdwoptions) "
						  "ORDER BY option_name"
						  "), E',\n    ') AS fdwoptions "
						  "FROM pg_foreign_data_wrapper f "
						  "LEFT JOIN pg_init_privs pip ON "
						  "(f.oid = pip.objoid "
						  "AND pip.classoid = 'pg_foreign_data_wrapper'::regclass "
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
	else if (fout->remoteVersion >= 90100)
	{
		appendPQExpBuffer(query, "SELECT tableoid, oid, fdwname, "
						  "(%s fdwowner) AS rolname, "
						  "fdwhandler::pg_catalog.regproc, "
						  "fdwvalidator::pg_catalog.regproc, fdwacl, "
						  "NULL as rfdwacl, "
						  "NULL as initfdwacl, NULL AS initrfdwacl, "
						  "array_to_string(ARRAY("
						  "SELECT quote_ident(option_name) || ' ' || "
						  "quote_literal(option_value) "
						  "FROM pg_options_to_table(fdwoptions) "
						  "ORDER BY option_name"
						  "), E',\n    ') AS fdwoptions "
						  "FROM pg_foreign_data_wrapper",
						  username_subquery);
	}
	else
	{
		appendPQExpBuffer(query, "SELECT tableoid, oid, fdwname, "
						  "(%s fdwowner) AS rolname, "
						  "'-' AS fdwhandler, "
						  "fdwvalidator::pg_catalog.regproc, fdwacl, "
						  "NULL as rfdwacl, "
						  "NULL as initfdwacl, NULL AS initrfdwacl, "
						  "array_to_string(ARRAY("
						  "SELECT quote_ident(option_name) || ' ' || "
						  "quote_literal(option_value) "
						  "FROM pg_options_to_table(fdwoptions) "
						  "ORDER BY option_name"
						  "), E',\n    ') AS fdwoptions "
						  "FROM pg_foreign_data_wrapper",
						  username_subquery);
	}

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numForeignDataWrappers = ntups;

	fdwinfo = (FdwInfo *) pg_malloc(ntups * sizeof(FdwInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_fdwname = PQfnumber(res, "fdwname");
	i_rolname = PQfnumber(res, "rolname");
	i_fdwhandler = PQfnumber(res, "fdwhandler");
	i_fdwvalidator = PQfnumber(res, "fdwvalidator");
	i_fdwacl = PQfnumber(res, "fdwacl");
	i_rfdwacl = PQfnumber(res, "rfdwacl");
	i_initfdwacl = PQfnumber(res, "initfdwacl");
	i_initrfdwacl = PQfnumber(res, "initrfdwacl");
	i_fdwoptions = PQfnumber(res, "fdwoptions");

	for (i = 0; i < ntups; i++)
	{
		fdwinfo[i].dobj.objType = DO_FDW;
		fdwinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		fdwinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&fdwinfo[i].dobj);
		fdwinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_fdwname));
		fdwinfo[i].dobj.namespace = NULL;
		fdwinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		fdwinfo[i].fdwhandler = pg_strdup(PQgetvalue(res, i, i_fdwhandler));
		fdwinfo[i].fdwvalidator = pg_strdup(PQgetvalue(res, i, i_fdwvalidator));
		fdwinfo[i].fdwoptions = pg_strdup(PQgetvalue(res, i, i_fdwoptions));
		fdwinfo[i].fdwacl = pg_strdup(PQgetvalue(res, i, i_fdwacl));
		fdwinfo[i].rfdwacl = pg_strdup(PQgetvalue(res, i, i_rfdwacl));
		fdwinfo[i].initfdwacl = pg_strdup(PQgetvalue(res, i, i_initfdwacl));
		fdwinfo[i].initrfdwacl = pg_strdup(PQgetvalue(res, i, i_initrfdwacl));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(fdwinfo[i].dobj), fout);

		/* Do not try to dump ACL if no ACL exists. */
		if (PQgetisnull(res, i, i_fdwacl) && PQgetisnull(res, i, i_rfdwacl) &&
			PQgetisnull(res, i, i_initfdwacl) &&
			PQgetisnull(res, i, i_initrfdwacl))
			fdwinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return fdwinfo;
}