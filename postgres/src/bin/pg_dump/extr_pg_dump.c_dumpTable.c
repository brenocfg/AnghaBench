#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_15__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  oid; } ;
struct TYPE_27__ {int dump; char* name; TYPE_2__* namespace; int /*<<< orphan*/  dumpId; TYPE_15__ catId; } ;
struct TYPE_28__ {scalar_t__ relkind; char* relacl; char* rrelacl; char* initrelacl; char* initrrelacl; int /*<<< orphan*/  rolname; TYPE_3__ dobj; } ;
typedef  TYPE_4__ TableInfo ;
struct TYPE_31__ {int remoteVersion; TYPE_6__* dopt; } ;
struct TYPE_30__ {int /*<<< orphan*/  binary_upgrade; scalar_t__ dataOnly; } ;
struct TYPE_29__ {int /*<<< orphan*/  data; } ;
struct TYPE_25__ {int /*<<< orphan*/  name; } ;
struct TYPE_26__ {TYPE_1__ dobj; } ;
typedef  TYPE_5__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_6__ DumpOptions ;
typedef  TYPE_7__ Archive ;

/* Variables and functions */
 int DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_5__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  buildACLQueries (TYPE_5__*,TYPE_5__*,TYPE_5__*,TYPE_5__*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_5__*) ; 
 int /*<<< orphan*/  dumpACL (TYPE_7__*,TYPE_15__,int /*<<< orphan*/ ,char const*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  dumpSequence (TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dumpTableSchema (TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fmtId (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dumpTable(Archive *fout, TableInfo *tbinfo)
{
	DumpOptions *dopt = fout->dopt;
	char	   *namecopy;

	/*
	 * noop if we are not dumping anything about this table, or if we are
	 * doing a data-only dump
	 */
	if (!tbinfo->dobj.dump || dopt->dataOnly)
		return;

	if (tbinfo->relkind == RELKIND_SEQUENCE)
		dumpSequence(fout, tbinfo);
	else
		dumpTableSchema(fout, tbinfo);

	/* Handle the ACL here */
	namecopy = pg_strdup(fmtId(tbinfo->dobj.name));
	if (tbinfo->dobj.dump & DUMP_COMPONENT_ACL)
	{
		const char *objtype =
		(tbinfo->relkind == RELKIND_SEQUENCE) ? "SEQUENCE" : "TABLE";

		dumpACL(fout, tbinfo->dobj.catId, tbinfo->dobj.dumpId,
				objtype, namecopy, NULL,
				tbinfo->dobj.namespace->dobj.name, tbinfo->rolname,
				tbinfo->relacl, tbinfo->rrelacl,
				tbinfo->initrelacl, tbinfo->initrrelacl);
	}

	/*
	 * Handle column ACLs, if any.  Note: we pull these with a separate query
	 * rather than trying to fetch them during getTableAttrs, so that we won't
	 * miss ACLs on system columns.
	 */
	if (fout->remoteVersion >= 80400 && tbinfo->dobj.dump & DUMP_COMPONENT_ACL)
	{
		PQExpBuffer query = createPQExpBuffer();
		PGresult   *res;
		int			i;

		if (fout->remoteVersion >= 90600)
		{
			PQExpBuffer acl_subquery = createPQExpBuffer();
			PQExpBuffer racl_subquery = createPQExpBuffer();
			PQExpBuffer initacl_subquery = createPQExpBuffer();
			PQExpBuffer initracl_subquery = createPQExpBuffer();

			buildACLQueries(acl_subquery, racl_subquery, initacl_subquery,
							initracl_subquery, "at.attacl", "c.relowner", "'c'",
							dopt->binary_upgrade);

			appendPQExpBuffer(query,
							  "SELECT at.attname, "
							  "%s AS attacl, "
							  "%s AS rattacl, "
							  "%s AS initattacl, "
							  "%s AS initrattacl "
							  "FROM pg_catalog.pg_attribute at "
							  "JOIN pg_catalog.pg_class c ON (at.attrelid = c.oid) "
							  "LEFT JOIN pg_catalog.pg_init_privs pip ON "
							  "(at.attrelid = pip.objoid "
							  "AND pip.classoid = 'pg_catalog.pg_class'::pg_catalog.regclass "
							  "AND at.attnum = pip.objsubid) "
							  "WHERE at.attrelid = '%u'::pg_catalog.oid AND "
							  "NOT at.attisdropped "
							  "AND ("
							  "%s IS NOT NULL OR "
							  "%s IS NOT NULL OR "
							  "%s IS NOT NULL OR "
							  "%s IS NOT NULL)"
							  "ORDER BY at.attnum",
							  acl_subquery->data,
							  racl_subquery->data,
							  initacl_subquery->data,
							  initracl_subquery->data,
							  tbinfo->dobj.catId.oid,
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
			appendPQExpBuffer(query,
							  "SELECT attname, attacl, NULL as rattacl, "
							  "NULL AS initattacl, NULL AS initrattacl "
							  "FROM pg_catalog.pg_attribute "
							  "WHERE attrelid = '%u'::pg_catalog.oid AND NOT attisdropped "
							  "AND attacl IS NOT NULL "
							  "ORDER BY attnum",
							  tbinfo->dobj.catId.oid);
		}

		res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

		for (i = 0; i < PQntuples(res); i++)
		{
			char	   *attname = PQgetvalue(res, i, 0);
			char	   *attacl = PQgetvalue(res, i, 1);
			char	   *rattacl = PQgetvalue(res, i, 2);
			char	   *initattacl = PQgetvalue(res, i, 3);
			char	   *initrattacl = PQgetvalue(res, i, 4);
			char	   *attnamecopy;

			attnamecopy = pg_strdup(fmtId(attname));
			/* Column's GRANT type is always TABLE */
			dumpACL(fout, tbinfo->dobj.catId, tbinfo->dobj.dumpId,
					"TABLE", namecopy, attnamecopy,
					tbinfo->dobj.namespace->dobj.name, tbinfo->rolname,
					attacl, rattacl, initattacl, initrattacl);
			free(attnamecopy);
		}
		PQclear(res);
		destroyPQExpBuffer(query);
	}

	free(namecopy);

	return;
}