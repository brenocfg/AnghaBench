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
struct TYPE_19__ {int /*<<< orphan*/  dump; int /*<<< orphan*/  namespace; int /*<<< orphan*/  name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_18__ {int remoteVersion; } ;
struct TYPE_17__ {int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_5__ dobj; void* tmpllexize; void* tmplinit; } ;
typedef  TYPE_2__ TSTemplateInfo ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_5__*) ; 
 int /*<<< orphan*/  DO_TSTEMPLATE ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  findNamespace (TYPE_4__*,void*) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_5__*,TYPE_4__*) ; 

TSTemplateInfo *
getTSTemplates(Archive *fout, int *numTSTemplates)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	TSTemplateInfo *tmplinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_tmplname;
	int			i_tmplnamespace;
	int			i_tmplinit;
	int			i_tmpllexize;

	/* Before 8.3, there is no built-in text search support */
	if (fout->remoteVersion < 80300)
	{
		*numTSTemplates = 0;
		return NULL;
	}

	query = createPQExpBuffer();

	appendPQExpBufferStr(query, "SELECT tableoid, oid, tmplname, "
						 "tmplnamespace, tmplinit::oid, tmpllexize::oid "
						 "FROM pg_ts_template");

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numTSTemplates = ntups;

	tmplinfo = (TSTemplateInfo *) pg_malloc(ntups * sizeof(TSTemplateInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_tmplname = PQfnumber(res, "tmplname");
	i_tmplnamespace = PQfnumber(res, "tmplnamespace");
	i_tmplinit = PQfnumber(res, "tmplinit");
	i_tmpllexize = PQfnumber(res, "tmpllexize");

	for (i = 0; i < ntups; i++)
	{
		tmplinfo[i].dobj.objType = DO_TSTEMPLATE;
		tmplinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		tmplinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&tmplinfo[i].dobj);
		tmplinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_tmplname));
		tmplinfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_tmplnamespace)));
		tmplinfo[i].tmplinit = atooid(PQgetvalue(res, i, i_tmplinit));
		tmplinfo[i].tmpllexize = atooid(PQgetvalue(res, i, i_tmpllexize));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(tmplinfo[i].dobj), fout);

		/* Text Search Templates do not currently have ACLs. */
		tmplinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return tmplinfo;
}