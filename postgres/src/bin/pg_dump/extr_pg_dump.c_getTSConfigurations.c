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
struct TYPE_19__ {int /*<<< orphan*/  dump; int /*<<< orphan*/  namespace; void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_18__ {int remoteVersion; } ;
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_5__ dobj; void* cfgparser; void* rolname; } ;
typedef  TYPE_2__ TSConfigInfo ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_5__*) ; 
 int /*<<< orphan*/  DO_TSCONFIG ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  findNamespace (TYPE_4__*,void*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  username_subquery ; 

TSConfigInfo *
getTSConfigurations(Archive *fout, int *numTSConfigs)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	TSConfigInfo *cfginfo;
	int			i_tableoid;
	int			i_oid;
	int			i_cfgname;
	int			i_cfgnamespace;
	int			i_rolname;
	int			i_cfgparser;

	/* Before 8.3, there is no built-in text search support */
	if (fout->remoteVersion < 80300)
	{
		*numTSConfigs = 0;
		return NULL;
	}

	query = createPQExpBuffer();

	appendPQExpBuffer(query, "SELECT tableoid, oid, cfgname, "
					  "cfgnamespace, (%s cfgowner) AS rolname, cfgparser "
					  "FROM pg_ts_config",
					  username_subquery);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numTSConfigs = ntups;

	cfginfo = (TSConfigInfo *) pg_malloc(ntups * sizeof(TSConfigInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_cfgname = PQfnumber(res, "cfgname");
	i_cfgnamespace = PQfnumber(res, "cfgnamespace");
	i_rolname = PQfnumber(res, "rolname");
	i_cfgparser = PQfnumber(res, "cfgparser");

	for (i = 0; i < ntups; i++)
	{
		cfginfo[i].dobj.objType = DO_TSCONFIG;
		cfginfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		cfginfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&cfginfo[i].dobj);
		cfginfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_cfgname));
		cfginfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_cfgnamespace)));
		cfginfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));
		cfginfo[i].cfgparser = atooid(PQgetvalue(res, i, i_cfgparser));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(cfginfo[i].dobj), fout);

		/* Text Search Configurations do not currently have ACLs. */
		cfginfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return cfginfo;
}