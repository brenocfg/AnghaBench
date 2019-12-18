#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecuteSqlQueryForSingleRow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetisnull (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELKIND_PARTITIONED_TABLE ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  atooid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binary_upgrade_set_type_oids_by_type_oid (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static bool
binary_upgrade_set_type_oids_by_rel_oid(Archive *fout,
										PQExpBuffer upgrade_buffer,
										Oid pg_rel_oid)
{
	PQExpBuffer upgrade_query = createPQExpBuffer();
	PGresult   *upgrade_res;
	Oid			pg_type_oid;
	bool		toast_set = false;

	/*
	 * We only support old >= 8.3 for binary upgrades.
	 *
	 * We purposefully ignore toast OIDs for partitioned tables; the reason is
	 * that versions 10 and 11 have them, but 12 does not, so emitting them
	 * causes the upgrade to fail.
	 */
	appendPQExpBuffer(upgrade_query,
					  "SELECT c.reltype AS crel, t.reltype AS trel "
					  "FROM pg_catalog.pg_class c "
					  "LEFT JOIN pg_catalog.pg_class t ON "
					  "  (c.reltoastrelid = t.oid AND c.relkind <> '%c') "
					  "WHERE c.oid = '%u'::pg_catalog.oid;",
					  RELKIND_PARTITIONED_TABLE, pg_rel_oid);

	upgrade_res = ExecuteSqlQueryForSingleRow(fout, upgrade_query->data);

	pg_type_oid = atooid(PQgetvalue(upgrade_res, 0, PQfnumber(upgrade_res, "crel")));

	binary_upgrade_set_type_oids_by_type_oid(fout, upgrade_buffer,
											 pg_type_oid, false);

	if (!PQgetisnull(upgrade_res, 0, PQfnumber(upgrade_res, "trel")))
	{
		/* Toast tables do not have pg_type array rows */
		Oid			pg_type_toast_oid = atooid(PQgetvalue(upgrade_res, 0,
														  PQfnumber(upgrade_res, "trel")));

		appendPQExpBufferStr(upgrade_buffer, "\n-- For binary upgrade, must preserve pg_type toast oid\n");
		appendPQExpBuffer(upgrade_buffer,
						  "SELECT pg_catalog.binary_upgrade_set_next_toast_pg_type_oid('%u'::pg_catalog.oid);\n\n",
						  pg_type_toast_oid);

		toast_set = true;
	}

	PQclear(upgrade_res);
	destroyPQExpBuffer(upgrade_query);

	return toast_set;
}