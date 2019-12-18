#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* oid; void* tableoid; } ;
struct TYPE_13__ {int /*<<< orphan*/  dump; int /*<<< orphan*/  namespace; void* name; TYPE_1__ catId; int /*<<< orphan*/  objType; } ;
struct TYPE_12__ {TYPE_4__ dobj; void* rolname; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_3__ ConvInfo ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  AssignDumpId (TYPE_4__*) ; 
 int /*<<< orphan*/  DO_CONVERSION ; 
 int /*<<< orphan*/  DUMP_COMPONENT_ACL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_2__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  findNamespace (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ pg_malloc (int) ; 
 void* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selectDumpableObject (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  username_subquery ; 

ConvInfo *
getConversions(Archive *fout, int *numConversions)
{
	PGresult   *res;
	int			ntups;
	int			i;
	PQExpBuffer query;
	ConvInfo   *convinfo;
	int			i_tableoid;
	int			i_oid;
	int			i_conname;
	int			i_connamespace;
	int			i_rolname;

	query = createPQExpBuffer();

	/*
	 * find all conversions, including builtin conversions; we filter out
	 * system-defined conversions at dump-out time.
	 */

	appendPQExpBuffer(query, "SELECT tableoid, oid, conname, "
					  "connamespace, "
					  "(%s conowner) AS rolname "
					  "FROM pg_conversion",
					  username_subquery);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	ntups = PQntuples(res);
	*numConversions = ntups;

	convinfo = (ConvInfo *) pg_malloc(ntups * sizeof(ConvInfo));

	i_tableoid = PQfnumber(res, "tableoid");
	i_oid = PQfnumber(res, "oid");
	i_conname = PQfnumber(res, "conname");
	i_connamespace = PQfnumber(res, "connamespace");
	i_rolname = PQfnumber(res, "rolname");

	for (i = 0; i < ntups; i++)
	{
		convinfo[i].dobj.objType = DO_CONVERSION;
		convinfo[i].dobj.catId.tableoid = atooid(PQgetvalue(res, i, i_tableoid));
		convinfo[i].dobj.catId.oid = atooid(PQgetvalue(res, i, i_oid));
		AssignDumpId(&convinfo[i].dobj);
		convinfo[i].dobj.name = pg_strdup(PQgetvalue(res, i, i_conname));
		convinfo[i].dobj.namespace =
			findNamespace(fout,
						  atooid(PQgetvalue(res, i, i_connamespace)));
		convinfo[i].rolname = pg_strdup(PQgetvalue(res, i, i_rolname));

		/* Decide whether we want to dump it */
		selectDumpableObject(&(convinfo[i].dobj), fout);

		/* Conversions do not currently have ACLs. */
		convinfo[i].dobj.dump &= ~DUMP_COMPONENT_ACL;
	}

	PQclear(res);

	destroyPQExpBuffer(query);

	return convinfo;
}