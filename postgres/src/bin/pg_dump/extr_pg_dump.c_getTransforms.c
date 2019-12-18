#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int /*<<< orphan*/  name; } ;
struct TYPE_23__ {TYPE_2__ dobj; } ;
typedef  TYPE_3__ TypeInfo ;
struct TYPE_21__ {void* oid; void* tableoid; } ;
struct TYPE_28__ {int /*<<< orphan*/  name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_24__ {TYPE_8__ dobj; void* trflang; void* trftype; void* trftosql; void* trffromsql; } ;
typedef  TYPE_4__ TransformInfo ;
struct TYPE_27__ {int remoteVersion; } ;
struct TYPE_26__ {int /*<<< orphan*/  data; } ;
struct TYPE_25__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ PQExpBufferData ;
typedef  TYPE_6__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_7__ Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_8__*) ; 
 int /*<<< orphan*/  DO_TRANSFORM ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_5__*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_6__*,char*) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_6__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_6__*) ; 
 TYPE_3__* findTypeByOid (void*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_language_name (TYPE_7__*,void*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_5__*) ; 
 scalar_t__ pg_malloc (int) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_8__*,TYPE_7__*) ; 

TransformInfo *
getTransforms(Archive *fout, int *numTransforms)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	TransformInfo *transforminfo;
	int			i_tableoid;
	int			i_oid;
	int			i_trftype;
	int			i_trflang;
	int			i_trffromsql;
	int			i_trftosql;

	/* Transforms didn't exist pre-9.5 */
	if (fout->remoteVersion < 90500)
	{
		*numTransforms = 0;
		return NULL;
	}

	query = createPQExpBuffer();

	appendPQExpBufferStr(query, "SELECT tableoid, oid, "
						 "trftype, trflang, trffromsql::oid, trftosql::oid "
						 "FROM pg_transform "
						 "ORDER BY 3,4");

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);

	*numTransforms = ntups;

	transforminfo = (TransformInfo *) pg_malloc(ntups * sizeof(TransformInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_trftype = PQfnumber(res, "trftype");
	i_trflang = PQfnumber(res, "trflang");
	i_trffromsql = PQfnumber(res, "trffromsql");
	i_trftosql = PQfnumber(res, "trftosql");

	for (i = 0; i < ntups; i++)
	{
		PQExpBufferData namebuf;
		TypeInfo   *typeInfo;
		char	   *lanname;

		transforminfo[i].dobj.objType = DO_TRANSFORM;
		transforminfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		transforminfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&transforminfo[i].dobj);
		transforminfo[i].trftype = atooid(PQgetvalue(res, i, i_trftype));
		transforminfo[i].trflang = atooid(PQgetvalue(res, i, i_trflang));
		transforminfo[i].trffromsql = atooid(PQgetvalue(res, i, i_trffromsql));
		transforminfo[i].trftosql = atooid(PQgetvalue(res, i, i_trftosql));

		/*
		 * Try to name transform as concatenation of type and language name.
		 * This is only used for purposes of sorting.  If we fail to find
		 * either, the name will be an empty string.
		 */
		initPQExpBuffer(&namebuf);
		typeInfo = findTypeByOid(transforminfo[i].trftype);
		lanname = get_language_name(fout, transforminfo[i].trflang);
		if (typeInfo && lanname)
			appendPQExpBuffer(&namebuf, "%s %s",
							  typeInfo->dobj.name, lanname);
		transforminfo[i].dobj.name = namebuf.data;
		free(lanname);

		/* Decide whether we want to dump it */
		selectDumpableObject(&(transforminfo[i].dobj), fout);
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return transforminfo;
}