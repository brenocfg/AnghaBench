#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  oid; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; TYPE_1__ catId; } ;
struct TYPE_13__ {TYPE_2__ dobj; } ;
typedef  TYPE_3__ TableInfo ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_4__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQgetlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendBinaryPQExpBuffer (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_4__*) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PQExpBuffer
createViewAsClause(Archive *fout, TableInfo *tbinfo)
{
	PQExpBuffer query = createPQExpBuffer();
	PQExpBuffer result = createPQExpBuffer();
	PGresult   *res;
	int			len;

	/* Fetch the view definition */
	appendPQExpBuffer(query,
					  "SELECT pg_catalog.pg_get_viewdef('%u'::pg_catalog.oid) AS viewdef",
					  tbinfo->dobj.catId.oid);

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	if (PQntuples(res) != 1)
	{
		if (PQntuples(res) < 1)
			fatal("query to obtain definition of view \"%s\" returned no data",
				  tbinfo->dobj.name);
		else
			fatal("query to obtain definition of view \"%s\" returned more than one definition",
				  tbinfo->dobj.name);
	}

	len = PQgetlength(res, 0, 0);

	if (len == 0)
		fatal("definition of view \"%s\" appears to be empty (length zero)",
			  tbinfo->dobj.name);

	/* Strip off the trailing semicolon so that other things may follow. */
	Assert(PQgetvalue(res, 0, 0)[len - 1] == ';');
	appendBinaryPQExpBuffer(result, PQgetvalue(res, 0, 0), len - 1);

	PQclear(res);
	destroyPQExpBuffer(query);

	return result;
}