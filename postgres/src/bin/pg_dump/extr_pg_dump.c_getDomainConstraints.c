#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  oid; } ;
struct TYPE_15__ {int /*<<< orphan*/  namespace; TYPE_1__ catId; } ;
struct TYPE_19__ {int nDomChecks; TYPE_12__ dobj; TYPE_5__* domChecks; } ;
typedef  TYPE_3__ TypeInfo ;
struct TYPE_22__ {int remoteVersion; } ;
struct TYPE_18__ {void* oid; void* tableoid; } ;
struct TYPE_16__ {int /*<<< orphan*/  dumpId; int /*<<< orphan*/  namespace; void* name; TYPE_2__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_21__ {char contype; int condeferrable; int condeferred; int conislocal; int separate; TYPE_14__ dobj; scalar_t__ conindex; int /*<<< orphan*/  confrelid; void* condef; TYPE_3__* condomain; int /*<<< orphan*/ * contable; } ;
struct TYPE_20__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_4__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_5__ ConstraintInfo ;
typedef  TYPE_6__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_14__*) ; 
 int /*<<< orphan*/  DO_CONSTRAINT ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addObjectDependency (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (char*) ; 
 TYPE_4__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_4__*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (char*) ; 

__attribute__((used)) static void
getDomainConstraints(Archive *fout, TypeInfo *tyinfo)
{
	int			i;
	ConstraintInfo *constrinfo;
	PQExpBuffer query;
	PGresult   *res;
	int			i_tableoid,
				i_oid,
				i_conname,
				i_consrc;
	int			ntups;

	query = createPQExpBuffer();

	if (fout->remoteVersion >= 90100)
		appendPQExpBuffer(query, "SELECT tableoid, oid, conname, "
						  "pg_catalog.pg_get_constraintdef(oid) AS consrc, "
						  "convalidated "
						  "FROM pg_catalog.pg_constraint "
						  "WHERE contypid = '%u'::pg_catalog.oid "
						  "ORDER BY conname",
						  tyinfo->dobj.catId.oid);

	else
		appendPQExpBuffer(query, "SELECT tableoid, oid, conname, "
						  "pg_catalog.pg_get_constraintdef(oid) AS consrc, "
						  "true as convalidated "
						  "FROM pg_catalog.pg_constraint "
						  "WHERE contypid = '%u'::pg_catalog.oid "
						  "ORDER BY conname",
						  tyinfo->dobj.catId.oid);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_conname = PQfnumber(res, "conname");
	i_consrc = PQfnumber(res, "consrc");

	constrinfo = (ConstraintInfo *) pg_malloc(ntups * sizeof(ConstraintInfo));

	tyinfo->nDomChecks = ntups;
	tyinfo->domChecks = constrinfo;

	for (i = 0; i < ntups; i++)
	{
		bool		validated = PQgetvalue(res, i, 4)[0] == 't';

		constrinfo[i].dobj.objType = DO_CONSTRAINT;
		constrinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		constrinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&constrinfo[i].dobj);
		constrinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_conname));
		constrinfo[i].dobj.namespace = tyinfo->dobj.namespace;
		constrinfo[i].contable = NULL;
		constrinfo[i].condomain = tyinfo;
		constrinfo[i].contype = 'c';
		constrinfo[i].condef = pg_strdup(PQgetvalue(res, i, i_consrc));
		constrinfo[i].confrelid = InvalidOid;
		constrinfo[i].conindex = 0;
		constrinfo[i].condeferrable = false;
		constrinfo[i].condeferred = false;
		constrinfo[i].conislocal = true;

		constrinfo[i].separate = !validated;

		/*
		 * Make the domain depend on the constraint, ensuring it won't be
		 * output till any constraint dependencies are OK.  If the constraint
		 * has not been validated, it's going to be dumped after the domain
		 * anyway, so this doesn't matter.
		 */
		if (validated)
			addObjectDependency(&tyinfo->dobj,
								constrinfo[i].dobj.dumpId);
	}

	PQclear(res);

	destroyPQExpBuffer(query);
}