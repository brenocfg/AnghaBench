#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int translate_header; int const* translate_columns; int /*<<< orphan*/  n_translate_columns; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_1__ printQueryOpt ;
struct TYPE_12__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  db; TYPE_1__ popt; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  lengthof (int const*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
objectDescription(const char *pattern, bool showSystem)
{
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;
	static const bool translate_columns[] = {false, false, true, false};

	initPQExpBuffer(&buf);

	appendPQExpBuffer(&buf,
					  "SELECT DISTINCT tt.nspname AS \"%s\", tt.name AS \"%s\", tt.object AS \"%s\", d.description AS \"%s\"\n"
					  "FROM (\n",
					  gettext_noop("Schema"),
					  gettext_noop("Name"),
					  gettext_noop("Object"),
					  gettext_noop("Description"));

	/* Table constraint descriptions */
	appendPQExpBuffer(&buf,
					  "  SELECT pgc.oid as oid, pgc.tableoid AS tableoid,\n"
					  "  n.nspname as nspname,\n"
					  "  CAST(pgc.conname AS pg_catalog.text) as name,"
					  "  CAST('%s' AS pg_catalog.text) as object\n"
					  "  FROM pg_catalog.pg_constraint pgc\n"
					  "    JOIN pg_catalog.pg_class c "
					  "ON c.oid = pgc.conrelid\n"
					  "    LEFT JOIN pg_catalog.pg_namespace n "
					  "    ON n.oid = c.relnamespace\n",
					  gettext_noop("table constraint"));

	if (!showSystem && !pattern)
		appendPQExpBufferStr(&buf, "WHERE n.nspname <> 'pg_catalog'\n"
							 "      AND n.nspname <> 'information_schema'\n");

	processSQLNamePattern(pset.db, &buf, pattern, !showSystem && !pattern,
						  false, "n.nspname", "pgc.conname", NULL,
						  "pg_catalog.pg_table_is_visible(c.oid)");

	/* Domain constraint descriptions */
	appendPQExpBuffer(&buf,
					  "UNION ALL\n"
					  "  SELECT pgc.oid as oid, pgc.tableoid AS tableoid,\n"
					  "  n.nspname as nspname,\n"
					  "  CAST(pgc.conname AS pg_catalog.text) as name,"
					  "  CAST('%s' AS pg_catalog.text) as object\n"
					  "  FROM pg_catalog.pg_constraint pgc\n"
					  "    JOIN pg_catalog.pg_type t "
					  "ON t.oid = pgc.contypid\n"
					  "    LEFT JOIN pg_catalog.pg_namespace n "
					  "    ON n.oid = t.typnamespace\n",
					  gettext_noop("domain constraint"));

	if (!showSystem && !pattern)
		appendPQExpBufferStr(&buf, "WHERE n.nspname <> 'pg_catalog'\n"
							 "      AND n.nspname <> 'information_schema'\n");

	processSQLNamePattern(pset.db, &buf, pattern, !showSystem && !pattern,
						  false, "n.nspname", "pgc.conname", NULL,
						  "pg_catalog.pg_type_is_visible(t.oid)");


	/*
	 * pg_opclass.opcmethod only available in 8.3+
	 */
	if (pset.sversion >= 80300)
	{
		/* Operator class descriptions */
		appendPQExpBuffer(&buf,
						  "UNION ALL\n"
						  "  SELECT o.oid as oid, o.tableoid as tableoid,\n"
						  "  n.nspname as nspname,\n"
						  "  CAST(o.opcname AS pg_catalog.text) as name,\n"
						  "  CAST('%s' AS pg_catalog.text) as object\n"
						  "  FROM pg_catalog.pg_opclass o\n"
						  "    JOIN pg_catalog.pg_am am ON "
						  "o.opcmethod = am.oid\n"
						  "    JOIN pg_catalog.pg_namespace n ON "
						  "n.oid = o.opcnamespace\n",
						  gettext_noop("operator class"));

		if (!showSystem && !pattern)
			appendPQExpBufferStr(&buf, "      AND n.nspname <> 'pg_catalog'\n"
								 "      AND n.nspname <> 'information_schema'\n");

		processSQLNamePattern(pset.db, &buf, pattern, true, false,
							  "n.nspname", "o.opcname", NULL,
							  "pg_catalog.pg_opclass_is_visible(o.oid)");
	}

	/*
	 * although operator family comments have been around since 8.3,
	 * pg_opfamily_is_visible is only available in 9.2+
	 */
	if (pset.sversion >= 90200)
	{
		/* Operator family descriptions */
		appendPQExpBuffer(&buf,
						  "UNION ALL\n"
						  "  SELECT opf.oid as oid, opf.tableoid as tableoid,\n"
						  "  n.nspname as nspname,\n"
						  "  CAST(opf.opfname AS pg_catalog.text) AS name,\n"
						  "  CAST('%s' AS pg_catalog.text) as object\n"
						  "  FROM pg_catalog.pg_opfamily opf\n"
						  "    JOIN pg_catalog.pg_am am "
						  "ON opf.opfmethod = am.oid\n"
						  "    JOIN pg_catalog.pg_namespace n "
						  "ON opf.opfnamespace = n.oid\n",
						  gettext_noop("operator family"));

		if (!showSystem && !pattern)
			appendPQExpBufferStr(&buf, "      AND n.nspname <> 'pg_catalog'\n"
								 "      AND n.nspname <> 'information_schema'\n");

		processSQLNamePattern(pset.db, &buf, pattern, true, false,
							  "n.nspname", "opf.opfname", NULL,
							  "pg_catalog.pg_opfamily_is_visible(opf.oid)");
	}

	/* Rule descriptions (ignore rules for views) */
	appendPQExpBuffer(&buf,
					  "UNION ALL\n"
					  "  SELECT r.oid as oid, r.tableoid as tableoid,\n"
					  "  n.nspname as nspname,\n"
					  "  CAST(r.rulename AS pg_catalog.text) as name,"
					  "  CAST('%s' AS pg_catalog.text) as object\n"
					  "  FROM pg_catalog.pg_rewrite r\n"
					  "       JOIN pg_catalog.pg_class c ON c.oid = r.ev_class\n"
					  "       LEFT JOIN pg_catalog.pg_namespace n ON n.oid = c.relnamespace\n"
					  "  WHERE r.rulename != '_RETURN'\n",
					  gettext_noop("rule"));

	if (!showSystem && !pattern)
		appendPQExpBufferStr(&buf, "      AND n.nspname <> 'pg_catalog'\n"
							 "      AND n.nspname <> 'information_schema'\n");

	processSQLNamePattern(pset.db, &buf, pattern, true, false,
						  "n.nspname", "r.rulename", NULL,
						  "pg_catalog.pg_table_is_visible(c.oid)");

	/* Trigger descriptions */
	appendPQExpBuffer(&buf,
					  "UNION ALL\n"
					  "  SELECT t.oid as oid, t.tableoid as tableoid,\n"
					  "  n.nspname as nspname,\n"
					  "  CAST(t.tgname AS pg_catalog.text) as name,"
					  "  CAST('%s' AS pg_catalog.text) as object\n"
					  "  FROM pg_catalog.pg_trigger t\n"
					  "       JOIN pg_catalog.pg_class c ON c.oid = t.tgrelid\n"
					  "       LEFT JOIN pg_catalog.pg_namespace n ON n.oid = c.relnamespace\n",
					  gettext_noop("trigger"));

	if (!showSystem && !pattern)
		appendPQExpBufferStr(&buf, "WHERE n.nspname <> 'pg_catalog'\n"
							 "      AND n.nspname <> 'information_schema'\n");

	processSQLNamePattern(pset.db, &buf, pattern, !showSystem && !pattern, false,
						  "n.nspname", "t.tgname", NULL,
						  "pg_catalog.pg_table_is_visible(c.oid)");

	appendPQExpBufferStr(&buf,
						 ") AS tt\n"
						 "  JOIN pg_catalog.pg_description d ON (tt.oid = d.objoid AND tt.tableoid = d.classoid AND d.objsubid = 0)\n");

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2, 3;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("Object descriptions");
	myopt.translate_header = true;
	myopt.translate_columns = translate_columns;
	myopt.n_translate_columns = lengthof(translate_columns);

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}