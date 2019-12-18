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
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfnumber (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  atooid (int /*<<< orphan*/ ) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static void
binary_upgrade_set_pg_class_oids(Archive *fout,
								 PQExpBuffer upgrade_buffer, Oid pg_class_oid,
								 bool is_index)
{
	PQExpBuffer upgrade_query = createPQExpBuffer();
	PGresult   *upgrade_res;
	Oid			pg_class_reltoastrelid;
	Oid			pg_index_indexrelid;

	appendPQExpBuffer(upgrade_query,
					  "SELECT c.reltoastrelid, i.indexrelid "
					  "FROM pg_catalog.pg_class c LEFT JOIN "
					  "pg_catalog.pg_index i ON (c.reltoastrelid = i.indrelid AND i.indisvalid) "
					  "WHERE c.oid = '%u'::pg_catalog.oid;",
					  pg_class_oid);

	upgrade_res = ExecuteSqlQueryForSingleRow(fout, upgrade_query->data);

	pg_class_reltoastrelid = atooid(PQgetvalue(upgrade_res, 0, PQfnumber(upgrade_res, "reltoastrelid")));
	pg_index_indexrelid = atooid(PQgetvalue(upgrade_res, 0, PQfnumber(upgrade_res, "indexrelid")));

	appendPQExpBufferStr(upgrade_buffer,
						 "\n-- For binary upgrade, must preserve pg_class oids\n");

	if (!is_index)
	{
		appendPQExpBuffer(upgrade_buffer,
						  "SELECT pg_catalog.binary_upgrade_set_next_heap_pg_class_oid('%u'::pg_catalog.oid);\n",
						  pg_class_oid);
		/* only tables have toast tables, not indexes */
		if (OidIsValid(pg_class_reltoastrelid))
		{
			/*
			 * One complexity is that the table definition might not require
			 * the creation of a TOAST table, and the TOAST table might have
			 * been created long after table creation, when the table was
			 * loaded with wide data.  By setting the TOAST oid we force
			 * creation of the TOAST heap and TOAST index by the backend so we
			 * can cleanly copy the files during binary upgrade.
			 */

			appendPQExpBuffer(upgrade_buffer,
							  "SELECT pg_catalog.binary_upgrade_set_next_toast_pg_class_oid('%u'::pg_catalog.oid);\n",
							  pg_class_reltoastrelid);

			/* every toast table has an index */
			appendPQExpBuffer(upgrade_buffer,
							  "SELECT pg_catalog.binary_upgrade_set_next_index_pg_class_oid('%u'::pg_catalog.oid);\n",
							  pg_index_indexrelid);
		}
	}
	else
		appendPQExpBuffer(upgrade_buffer,
						  "SELECT pg_catalog.binary_upgrade_set_next_index_pg_class_oid('%u'::pg_catalog.oid);\n",
						  pg_class_oid);

	appendPQExpBufferChar(upgrade_buffer, '\n');

	PQclear(upgrade_res);
	destroyPQExpBuffer(upgrade_query);
}