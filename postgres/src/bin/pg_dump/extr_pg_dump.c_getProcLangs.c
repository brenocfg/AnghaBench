#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
struct TYPE_24__ {int remoteVersion; TYPE_4__* dopt; } ;
struct TYPE_23__ {int /*<<< orphan*/  binary_upgrade; } ;
struct TYPE_22__ {int /*<<< orphan*/  data; } ;
struct TYPE_20__ {void* oid; void* tableoid; } ;
struct TYPE_19__ {int /*<<< orphan*/  dump; void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_21__ {int lanpltrusted; TYPE_18__ dobj; void* lanowner; void* initrlanacl; void* initlanacl; void* rlanacl; void* lanacl; void* lanvalidator; void* laninline; void* lanplcallfoid; } ;
typedef  TYPE_2__ ProcLangInfo ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_18__*) ; 
 int /*<<< orphan*/  DO_PROCLANG ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,int /*<<< orphan*/ ,...) ; 
 void* atooid (char*) ; 
 int /*<<< orphan*/  buildACLQueries (TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (char*) ; 
 int /*<<< orphan*/  selectDumpableProcLang (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  username_subquery ; 

ProcLangInfo *
getProcLangs(Archive *fout, int *numProcLangs)
{
	DumpOptions *dopt = fout->dopt;
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query = createPQExpBuffer();
	ProcLangInfo *planginfo;
	int			i_tableoid;
	int			i_oid;
	int			i_lanname;
	int			i_lanpltrusted;
	int			i_lanplcallfoid;
	int			i_laninline;
	int			i_lanvalidator;
	int			i_lanacl;
	int			i_rlanacl;
	int			i_initlanacl;
	int			i_initrlanacl;
	int			i_lanowner;

	if (fout->remoteVersion >= 90600)
	{
		PQExpBuffer acl_subquery = createPQExpBuffer();
		PQExpBuffer racl_subquery = createPQExpBuffer();
		PQExpBuffer initacl_subquery = createPQExpBuffer();
		PQExpBuffer initracl_subquery = createPQExpBuffer();

		buildACLQueries(acl_subquery, racl_subquery, initacl_subquery,
						initracl_subquery, "l.lanacl", "l.lanowner", "'l'",
						dopt->binary_upgrade);

		/* pg_language has a laninline column */
		appendPQExpBuffer(query, "SELECT l.tableoid, l.oid, "
						  "l.lanname, l.lanpltrusted, l.lanplcallfoid, "
						  "l.laninline, l.lanvalidator, "
						  "%s AS lanacl, "
						  "%s AS rlanacl, "
						  "%s AS initlanacl, "
						  "%s AS initrlanacl, "
						  "(%s l.lanowner) AS lanowner "
						  "FROM pg_language l "
						  "LEFT JOIN pg_init_privs pip ON "
						  "(l.oid = pip.objoid "
						  "AND pip.classoid = 'pg_language'::regclass "
						  "AND pip.objsubid = 0) "
						  "WHERE l.lanispl "
						  "ORDER BY l.oid",
						  acl_subquery->data,
						  racl_subquery->data,
						  initacl_subquery->data,
						  initracl_subquery->data,
						  username_subquery);

		destroyPQExpBuffer(acl_subquery);
		destroyPQExpBuffer(racl_subquery);
		destroyPQExpBuffer(initacl_subquery);
		destroyPQExpBuffer(initracl_subquery);
	}
	else if (fout->remoteVersion >= 90000)
	{
		/* pg_language has a laninline column */
		appendPQExpBuffer(query, "SELECT tableoid, oid, "
						  "lanname, lanpltrusted, lanplcallfoid, "
						  "laninline, lanvalidator, lanacl, NULL AS rlanacl, "
						  "NULL AS initlanacl, NULL AS initrlanacl, "
						  "(%s lanowner) AS lanowner "
						  "FROM pg_language "
						  "WHERE lanispl "
						  "ORDER BY oid",
						  username_subquery);
	}
	else if (fout->remoteVersion >= 80300)
	{
		/* pg_language has a lanowner column */
		appendPQExpBuffer(query, "SELECT tableoid, oid, "
						  "lanname, lanpltrusted, lanplcallfoid, "
						  "0 AS laninline, lanvalidator, lanacl, "
						  "NULL AS rlanacl, "
						  "NULL AS initlanacl, NULL AS initrlanacl, "
						  "(%s lanowner) AS lanowner "
						  "FROM pg_language "
						  "WHERE lanispl "
						  "ORDER BY oid",
						  username_subquery);
	}
	else if (fout->remoteVersion >= 80100)
	{
		/* Languages are owned by the bootstrap superuser, OID 10 */
		appendPQExpBuffer(query, "SELECT tableoid, oid, "
						  "lanname, lanpltrusted, lanplcallfoid, "
						  "0 AS laninline, lanvalidator, lanacl, "
						  "NULL AS rlanacl, "
						  "NULL AS initlanacl, NULL AS initrlanacl, "
						  "(%s '10') AS lanowner "
						  "FROM pg_language "
						  "WHERE lanispl "
						  "ORDER BY oid",
						  username_subquery);
	}
	else
	{
		/* Languages are owned by the bootstrap superuser, sysid 1 */
		appendPQExpBuffer(query, "SELECT tableoid, oid, "
						  "lanname, lanpltrusted, lanplcallfoid, "
						  "0 AS laninline, lanvalidator, lanacl, "
						  "NULL AS rlanacl, "
						  "NULL AS initlanacl, NULL AS initrlanacl, "
						  "(%s '1') AS lanowner "
						  "FROM pg_language "
						  "WHERE lanispl "
						  "ORDER BY oid",
						  username_subquery);
	}

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	*numProcLangs = ntups;

	planginfo = (ProcLangInfo *) pg_malloc(ntups * sizeof(ProcLangInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_lanname = PQfnumber(res, "lanname");
	i_lanpltrusted = PQfnumber(res, "lanpltrusted");
	i_lanplcallfoid = PQfnumber(res, "lanplcallfoid");
	i_laninline = PQfnumber(res, "laninline");
	i_lanvalidator = PQfnumber(res, "lanvalidator");
	i_lanacl = PQfnumber(res, "lanacl");
	i_rlanacl = PQfnumber(res, "rlanacl");
	i_initlanacl = PQfnumber(res, "initlanacl");
	i_initrlanacl = PQfnumber(res, "initrlanacl");
	i_lanowner = PQfnumber(res, "lanowner");

	for (i = 0; i < ntups; i++)
	{
		planginfo[i].dobj.objType = DO_PROCLANG;
		planginfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		planginfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&planginfo[i].dobj);

		planginfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_lanname));
		planginfo[i].lanpltrusted = *(PQgetvalue(res, i, i_lanpltrusted)) == 't';
		planginfo[i].lanplcallfoid = atooid(PQgetvalue(res, i, i_lanplcallfoid));
		planginfo[i].laninline = atooid(PQgetvalue(res, i, i_laninline));
		planginfo[i].lanvalidator = atooid(PQgetvalue(res, i, i_lanvalidator));
		planginfo[i].lanacl = pg_strdup(PQgetvalue(res, i, i_lanacl));
		planginfo[i].rlanacl = pg_strdup(PQgetvalue(res, i, i_rlanacl));
		planginfo[i].initlanacl = pg_strdup(PQgetvalue(res, i, i_initlanacl));
		planginfo[i].initrlanacl = pg_strdup(PQgetvalue(res, i, i_initrlanacl));
		planginfo[i].lanowner = pg_strdup(PQgetvalue(res, i, i_lanowner));

		/* Decide whether we want to dump it */
		selectDumpableProcLang(&(planginfo[i]), fout);

		/* Do not try to dump ACL if no ACL exists. */
		if (PQgetisnull(res, i, i_lanacl) && PQgetisnull(res, i, i_rlanacl) &&
			PQgetisnull(res, i, i_initlanacl) &&
			PQgetisnull(res, i, i_initrlanacl))
			planginfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return planginfo;
}