#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__* head; } ;
struct TYPE_10__ {int /*<<< orphan*/  val; struct TYPE_10__* next; } ;
typedef  TYPE_1__ SimpleStringListCell ;
typedef  TYPE_2__ SimpleStringList ;
typedef  int /*<<< orphan*/  SimpleOidList ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  atooid (int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  simple_oid_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_schema_name_patterns(Archive *fout,
							SimpleStringList *patterns,
							SimpleOidList *oids,
							bool strict_names)
{
	PQExpBuffer query;
	PGresult   *res;
	SimpleStringListCell *cell;
	int			i;

	if (patterns->head == NULL)
		return;					/* nothing to do */

	query = createPQExpBuffer();

	/*
	 * The loop below runs multiple SELECTs might sometimes result in
	 * duplicate entries in the OID list, but we don't care.
	 */

	for (cell = patterns->head; cell; cell = cell->next)
	{
		appendPQExpBufferStr(query,
							 "SELECT oid FROM pg_catalog.pg_namespace n\n");
		processSQLNamePattern(GetConnection(fout), query, cell->val, false,
							  false, NULL, "n.nspname", NULL, NULL);

		res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);
		if (strict_names && PQntuples(res) == 0)
			fatal("no matching schemas were found for pattern \"%s\"", cell->val);

		for (i = 0; i < PQntuples(res); i++)
		{
			simple_oid_list_append(oids, atooid(PQgetvalue(res, i, 0)));
		}

		PQclear(res);
		resetPQExpBuffer(query);
	}

	destroyPQExpBuffer(query);
}