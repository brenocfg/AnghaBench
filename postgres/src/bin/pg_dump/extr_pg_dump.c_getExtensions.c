#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int remoteVersion; int /*<<< orphan*/ * dopt; } ;
struct TYPE_14__ {void* oid; void* tableoid; } ;
struct TYPE_13__ {void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_16__ {int relocatable; void* extcondition; void* extconfig; void* extversion; void* namespace; TYPE_12__ dobj; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ ExtensionInfo ;
typedef  int /*<<< orphan*/  DumpOptions ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_12__*) ; 
 int /*<<< orphan*/  DO_EXTENSION ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 void* atooid (char*) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (char*) ; 
 int /*<<< orphan*/  selectDumpableExtension (TYPE_3__*,int /*<<< orphan*/ *) ; 

ExtensionInfo *
getExtensions(Archive *fout, int *numExtensions)
{
	DumpOptions *dopt = fout->dopt;
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	ExtensionInfo *extinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_extname;
	int			i_nspname;
	int			i_extrelocatable;
	int			i_extversion;
	int			i_extconfig;
	int			i_extcondition;

	/*
	 * Before 9.1, there are no extensions.
	 */
	if (fout->remoteVersion < 90100)
	{
		*numExtensions = 0;
		return NULL;
	}

	query = createPQExpBuffer();

	appendPQExpBufferStr(query, "SELECT x.tableoid, x.oid, "
						 "x.extname, n.nspname, x.extrelocatable, x.extversion, x.extconfig, x.extcondition "
						 "FROM pg_extension x "
						 "JOIN pg_namespace n ON n.oid = x.extnamespace");

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	extinfo = (ExtensionInfo *) pg_malloc(ntups * sizeof(ExtensionInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_extname = PQfnumber(res, "extname");
	i_nspname = PQfnumber(res, "nspname");
	i_extrelocatable = PQfnumber(res, "extrelocatable");
	i_extversion = PQfnumber(res, "extversion");
	i_extconfig = PQfnumber(res, "extconfig");
	i_extcondition = PQfnumber(res, "extcondition");

	for (i = 0; i < ntups; i++)
	{
		extinfo[i].dobj.objType = DO_EXTENSION;
		extinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		extinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&extinfo[i].dobj);
		extinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_extname));
		extinfo[i].namespace = pg_strdup(PQgetvalue(res, i, i_nspname));
		extinfo[i].relocatable = *(PQgetvalue(res, i, i_extrelocatable)) == 't';
		extinfo[i].extversion = pg_strdup(PQgetvalue(res, i, i_extversion));
		extinfo[i].extconfig = pg_strdup(PQgetvalue(res, i, i_extconfig));
		extinfo[i].extcondition = pg_strdup(PQgetvalue(res, i, i_extcondition));

		/* Decide whether we want to dump it */
		selectDumpableExtension(&(extinfo[i]), dopt);
	}

	PQclear(res);
	destroyPQExpBuffer(query);

	*numExtensions = ntups;

	return extinfo;
}