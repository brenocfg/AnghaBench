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
struct TYPE_16__ {TYPE_5__ dobj; void* prslextype; void* prsheadline; void* prsend; void* prstoken; void* prsstart; } ;
typedef  TYPE_2__ TSParserInfo ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_5__*) ; 
 int /*<<< orphan*/  DO_TSPARSER ; 
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

TSParserInfo *
getTSParsers(Archive *fout, int *numTSParsers)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	TSParserInfo *prsinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_prsname;
	int			i_prsnamespace;
	int			i_prsstart;
	int			i_prstoken;
	int			i_prsend;
	int			i_prsheadline;
	int			i_prslextype;

	/* Before 8.3, there is no built-in text search support */
	if (fout->remoteVersion < 80300)
	{
		*numTSParsers = 0;
		return NULL;
	}

	query = createPQExpBuffer();

	/*
	 * find all text search objects, including builtin ones; we filter out
	 * system-defined objects at dump-out time.
	 */

	appendPQExpBufferStr(query, "SELECT tableoid, oid, prsname, prsnamespace, "
						 "prsstart::oid, prstoken::oid, "
						 "prsend::oid, prsheadline::oid, prslextype::oid "
						 "FROM pg_ts_parser");

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numTSParsers = ntups;

	prsinfo = (TSParserInfo *) pg_malloc(ntups * sizeof(TSParserInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_prsname = PQfnumber(res, "prsname");
	i_prsnamespace = PQfnumber(res, "prsnamespace");
	i_prsstart = PQfnumber(res, "prsstart");
	i_prstoken = PQfnumber(res, "prstoken");
	i_prsend = PQfnumber(res, "prsend");
	i_prsheadline = PQfnumber(res, "prsheadline");
	i_prslextype = PQfnumber(res, "prslextype");

	for (i = 0; i < ntups; i++)
	{
		prsinfo[i].dobj.objType = DO_TSPARSER;
		prsinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		prsinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&prsinfo[i].dobj);
		prsinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_prsname));
		prsinfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_prsnamespace)));
		prsinfo[i].prsstart = atooid(PQgetvalue(res, i, i_prsstart));
		prsinfo[i].prstoken = atooid(PQgetvalue(res, i, i_prstoken));
		prsinfo[i].prsend = atooid(PQgetvalue(res, i, i_prsend));
		prsinfo[i].prsheadline = atooid(PQgetvalue(res, i, i_prsheadline));
		prsinfo[i].prslextype = atooid(PQgetvalue(res, i, i_prslextype));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(prsinfo[i].dobj), fout);

		/* Text Search Parsers do not currently have ACLs. */
		prsinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return prsinfo;
}