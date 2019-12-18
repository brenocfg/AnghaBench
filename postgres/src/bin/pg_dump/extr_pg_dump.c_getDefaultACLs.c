#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
struct TYPE_25__ {int remoteVersion; TYPE_3__* dopt; } ;
struct TYPE_21__ {void* oid; void* tableoid; } ;
struct TYPE_20__ {int /*<<< orphan*/ * namespace; void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_24__ {void* initrdefaclacl; void* initdefaclacl; void* rdefaclacl; void* defaclacl; int /*<<< orphan*/  defaclobjtype; void* defaclrole; TYPE_19__ dobj; } ;
struct TYPE_23__ {int /*<<< orphan*/  binary_upgrade; } ;
struct TYPE_22__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__ DumpOptions ;
typedef  TYPE_4__ DefaultACLInfo ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_19__*) ; 
 int /*<<< orphan*/  DO_DEFAULT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 void* atooid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buildACLQueries (TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/ * findNamespace (TYPE_5__*,scalar_t__) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selectDumpableDefaultACL (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  username_subquery ; 

DefaultACLInfo *
getDefaultACLs(Archive *fout, int *numDefaultACLs)
{
	DumpOptions *dopt = fout->dopt;
	DefaultACLInfo *daclinfo;
	PQExpBuffer query;
	PGresult   *res;
	int			i_oid;
	int			i_tableoid;
	int			i_defaclrole;
	int			i_defaclnamespace;
	int			i_defaclobjtype;
	int			i_defaclacl;
	int			i_rdefaclacl;
	int			i_initdefaclacl;
	int			i_initrdefaclacl;
	int			i,
				ntups;

	if (fout->remoteVersion < 90000)
	{
		*numDefaultACLs = 0;
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
						initracl_subquery, "defaclacl", "defaclrole",
						"CASE WHEN defaclobjtype = 'S' THEN 's' ELSE defaclobjtype END::\"char\"",
						dopt->binary_upgrade);

		appendPQExpBuffer(query, "SELECT d.oid, d.tableoid, "
						  "(%s d.defaclrole) AS defaclrole, "
						  "d.defaclnamespace, "
						  "d.defaclobjtype, "
						  "%s AS defaclacl, "
						  "%s AS rdefaclacl, "
						  "%s AS initdefaclacl, "
						  "%s AS initrdefaclacl "
						  "FROM pg_default_acl d "
						  "LEFT JOIN pg_init_privs pip ON "
						  "(d.oid = pip.objoid "
						  "AND pip.classoid = 'pg_default_acl'::regclass "
						  "AND pip.objsubid = 0) ",
						  username_subquery,
						  acl_subquery->data,
						  racl_subquery->data,
						  initacl_subquery->data,
						  initracl_subquery->data);
	}
	else
	{
		appendPQExpBuffer(query, "SELECT oid, tableoid, "
						  "(%s defaclrole) AS defaclrole, "
						  "defaclnamespace, "
						  "defaclobjtype, "
						  "defaclacl, "
						  "NULL AS rdefaclacl, "
						  "NULL AS initdefaclacl, "
						  "NULL AS initrdefaclacl "
						  "FROM pg_default_acl",
						  username_subquery);
	}

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numDefaultACLs = ntups;

	daclinfo = (DefaultACLInfo *) pg_malloc(ntups * sizeof(DefaultACLInfo));

	i_oid = PQfnumber(res, "oid");
	i_tableoid = PQfnumber(res, "tableoid");
	i_defaclrole = PQfnumber(res, "defaclrole");
	i_defaclnamespace = PQfnumber(res, "defaclnamespace");
	i_defaclobjtype = PQfnumber(res, "defaclobjtype");
	i_defaclacl = PQfnumber(res, "defaclacl");
	i_rdefaclacl = PQfnumber(res, "rdefaclacl");
	i_initdefaclacl = PQfnumber(res, "initdefaclacl");
	i_initrdefaclacl = PQfnumber(res, "initrdefaclacl");

	for (i = 0; i < ntups; i++)
	{
		Oid			nspid = atooid(PQgetvalue(res, i, i_defaclnamespace));

		daclinfo[i].dobj.objType = DO_DEFAULT_ACL;
		daclinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		daclinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&daclinfo[i].dobj);
		/* cheesy ... is it worth coming up with a better object name? */
		daclinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_defaclobjtype));

		if (nspid != InvalidOid)
			daclinfo[i].dobj.namespace = findNamespace(fout, nspid);
		else
			daclinfo[i].dobj.namespace = NULL;

		daclinfo[i].defaclrole = pg_strdup(PQgetvalue(res, i, i_defaclrole));
		daclinfo[i].defaclobjtype = *(PQgetvalue(res, i, i_defaclobjtype));
		daclinfo[i].defaclacl = pg_strdup(PQgetvalue(res, i, i_defaclacl));
		daclinfo[i].rdefaclacl = pg_strdup(PQgetvalue(res, i, i_rdefaclacl));
		daclinfo[i].initdefaclacl = pg_strdup(PQgetvalue(res, i, i_initdefaclacl));
		daclinfo[i].initrdefaclacl = pg_strdup(PQgetvalue(res, i, i_initrdefaclacl));

		/* Decide whether we want to dump it */
		selectDumpableDefaultACL(&(daclinfo[i]), dopt);
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return daclinfo;
}