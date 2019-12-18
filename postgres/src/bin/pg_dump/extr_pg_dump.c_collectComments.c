#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  objsubid; void* objoid; void* classoid; int /*<<< orphan*/  descr; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_2__ CommentItem ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 void* atooid (int /*<<< orphan*/ ) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 scalar_t__ pg_malloc (int) ; 

__attribute__((used)) static int
collectComments(Archive *fout, CommentItem **items)
{
	PGresult   *res;
	PQExpBuffer query;
	int			i_description;
	int			i_classoid;
	int			i_objoid;
	int			i_objsubid;
	int			ntups;
	int			i;
	CommentItem *comments;

	query = createPQExpBuffer();

	appendPQExpBufferStr(query, "SELECT description, classoid, objoid, objsubid "
						 "FROM pg_catalog.pg_description "
						 "ORDER BY classoid, objoid, objsubid");

	res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);

	/* Construct lookup table containing OIDs in numeric form */

	i_description = PQfnumber(res, "description");
	i_classoid = PQfnumber(res, "classoid");
	i_objoid = PQfnumber(res, "objoid");
	i_objsubid = PQfnumber(res, "objsubid");

	ntups = PQntuples(res);

	comments = (CommentItem *) pg_malloc(ntups * sizeof(CommentItem));

	for (i = 0; i < ntups; i++)
	{
		comments[i].descr = PQgetvalue(res, i, i_description);
		comments[i].classoid = atooid(PQgetvalue(res, i, i_classoid));
		comments[i].objoid = atooid(PQgetvalue(res, i, i_objoid));
		comments[i].objsubid = atoi(PQgetvalue(res, i, i_objsubid));
	}

	/* Do NOT free the PGresult since we are keeping pointers into it */
	destroyPQExpBuffer(query);

	*items = comments;
	return ntups;
}