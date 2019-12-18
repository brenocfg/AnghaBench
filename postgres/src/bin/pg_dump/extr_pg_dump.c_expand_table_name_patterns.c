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
 int /*<<< orphan*/  ALWAYS_SECURE_SEARCH_PATH_SQL ; 
 int /*<<< orphan*/ * ExecuteSqlQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecuteSqlStatement (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RELKIND_FOREIGN_TABLE ; 
 int /*<<< orphan*/  RELKIND_MATVIEW ; 
 int /*<<< orphan*/  RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  RELKIND_RELATION ; 
 int /*<<< orphan*/  RELKIND_SEQUENCE ; 
 int /*<<< orphan*/  RELKIND_VIEW ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atooid (int /*<<< orphan*/ ) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  simple_oid_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_table_name_patterns(Archive *fout,
						   SimpleStringList *patterns, SimpleOidList *oids,
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
	 * this might sometimes result in duplicate entries in the OID list, but
	 * we don't care.
	 */

	for (cell = patterns->head; cell; cell = cell->next)
	{
		/*
		 * Query must remain ABSOLUTELY devoid of unqualified names.  This
		 * would be unnecessary given a pg_table_is_visible() variant taking a
		 * search_path argument.
		 */
		appendPQExpBuffer(query,
						  "SELECT c.oid"
						  "\nFROM pg_catalog.pg_class c"
						  "\n     LEFT JOIN pg_catalog.pg_namespace n"
						  "\n     ON n.oid OPERATOR(pg_catalog.=) c.relnamespace"
						  "\nWHERE c.relkind OPERATOR(pg_catalog.=) ANY"
						  "\n    (array['%c', '%c', '%c', '%c', '%c', '%c'])\n",
						  RELKIND_RELATION, RELKIND_SEQUENCE, RELKIND_VIEW,
						  RELKIND_MATVIEW, RELKIND_FOREIGN_TABLE,
						  RELKIND_PARTITIONED_TABLE);
		processSQLNamePattern(GetConnection(fout), query, cell->val, true,
							  false, "n.nspname", "c.relname", NULL,
							  "pg_catalog.pg_table_is_visible(c.oid)");

		ExecuteSqlStatement(fout, "RESET search_path");
		res = ExecuteSqlQuery(fout, query->data, PGRES_TUPLES_OK);
		PQclear(ExecuteSqlQueryForSingleRow(fout,
											ALWAYS_SECURE_SEARCH_PATH_SQL));
		if (strict_names && PQntuples(res) == 0)
			fatal("no matching tables were found for pattern \"%s\"", cell->val);

		for (i = 0; i < PQntuples(res); i++)
		{
			simple_oid_list_append(oids, atooid(PQgetvalue(res, i, 0)));
		}

		PQclear(res);
		resetPQExpBuffer(query);
	}

	destroyPQExpBuffer(query);
}