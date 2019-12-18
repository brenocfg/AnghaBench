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
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sverbuf ;
struct TYPE_12__ {int translate_header; int const* translate_columns; void* n_translate_columns; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_1__ printQueryOpt ;
struct TYPE_14__ {int sversion; int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; int /*<<< orphan*/  db; TYPE_1__ popt; } ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  formatPGVersionNumber (int,int,char*,int) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 void* lengthof (int const*) ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int /*<<< orphan*/  printACLColumn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processSQLNamePattern (int /*<<< orphan*/ ,TYPE_2__*,char const*,int,int,char*,char*,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__ pset ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strspn (char const*,char*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

bool
describeFunctions(const char *functypes, const char *pattern, bool verbose, bool showSystem)
{
	bool		showAggregate = strchr(functypes, 'a') != NULL;
	bool		showNormal = strchr(functypes, 'n') != NULL;
	bool		showProcedure = strchr(functypes, 'p') != NULL;
	bool		showTrigger = strchr(functypes, 't') != NULL;
	bool		showWindow = strchr(functypes, 'w') != NULL;
	bool		have_where;
	PQExpBufferData buf;
	PGresult   *res;
	printQueryOpt myopt = pset.popt;
	static const bool translate_columns[] = {false, false, false, false, true, true, true, false, true, false, false, false, false};

	/* No "Parallel" column before 9.6 */
	static const bool translate_columns_pre_96[] = {false, false, false, false, true, true, false, true, false, false, false, false};

	if (strlen(functypes) != strspn(functypes, "anptwS+"))
	{
		pg_log_error("\\df only takes [anptwS+] as options");
		return true;
	}

	if (showProcedure && pset.sversion < 110000)
	{
		char		sverbuf[32];

		pg_log_error("\\df does not take a \"%c\" option with server version %s",
					 'p',
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	if (showWindow && pset.sversion < 80400)
	{
		char		sverbuf[32];

		pg_log_error("\\df does not take a \"%c\" option with server version %s",
					 'w',
					 formatPGVersionNumber(pset.sversion, false,
										   sverbuf, sizeof(sverbuf)));
		return true;
	}

	if (!showAggregate && !showNormal && !showProcedure && !showTrigger && !showWindow)
	{
		showAggregate = showNormal = showTrigger = true;
		if (pset.sversion >= 110000)
			showProcedure = true;
		if (pset.sversion >= 80400)
			showWindow = true;
	}

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT n.nspname as \"%s\",\n"
					  "  p.proname as \"%s\",\n",
					  gettext_noop("Schema"),
					  gettext_noop("Name"));

	if (pset.sversion >= 110000)
		appendPQExpBuffer(&buf,
						  "  pg_catalog.pg_get_function_result(p.oid) as \"%s\",\n"
						  "  pg_catalog.pg_get_function_arguments(p.oid) as \"%s\",\n"
						  " CASE p.prokind\n"
						  "  WHEN 'a' THEN '%s'\n"
						  "  WHEN 'w' THEN '%s'\n"
						  "  WHEN 'p' THEN '%s'\n"
						  "  ELSE '%s'\n"
						  " END as \"%s\"",
						  gettext_noop("Result data type"),
						  gettext_noop("Argument data types"),
		/* translator: "agg" is short for "aggregate" */
						  gettext_noop("agg"),
						  gettext_noop("window"),
						  gettext_noop("proc"),
						  gettext_noop("func"),
						  gettext_noop("Type"));
	else if (pset.sversion >= 80400)
		appendPQExpBuffer(&buf,
						  "  pg_catalog.pg_get_function_result(p.oid) as \"%s\",\n"
						  "  pg_catalog.pg_get_function_arguments(p.oid) as \"%s\",\n"
						  " CASE\n"
						  "  WHEN p.proisagg THEN '%s'\n"
						  "  WHEN p.proiswindow THEN '%s'\n"
						  "  WHEN p.prorettype = 'pg_catalog.trigger'::pg_catalog.regtype THEN '%s'\n"
						  "  ELSE '%s'\n"
						  " END as \"%s\"",
						  gettext_noop("Result data type"),
						  gettext_noop("Argument data types"),
		/* translator: "agg" is short for "aggregate" */
						  gettext_noop("agg"),
						  gettext_noop("window"),
						  gettext_noop("trigger"),
						  gettext_noop("func"),
						  gettext_noop("Type"));
	else if (pset.sversion >= 80100)
		appendPQExpBuffer(&buf,
						  "  CASE WHEN p.proretset THEN 'SETOF ' ELSE '' END ||\n"
						  "  pg_catalog.format_type(p.prorettype, NULL) as \"%s\",\n"
						  "  CASE WHEN proallargtypes IS NOT NULL THEN\n"
						  "    pg_catalog.array_to_string(ARRAY(\n"
						  "      SELECT\n"
						  "        CASE\n"
						  "          WHEN p.proargmodes[s.i] = 'i' THEN ''\n"
						  "          WHEN p.proargmodes[s.i] = 'o' THEN 'OUT '\n"
						  "          WHEN p.proargmodes[s.i] = 'b' THEN 'INOUT '\n"
						  "          WHEN p.proargmodes[s.i] = 'v' THEN 'VARIADIC '\n"
						  "        END ||\n"
						  "        CASE\n"
						  "          WHEN COALESCE(p.proargnames[s.i], '') = '' THEN ''\n"
						  "          ELSE p.proargnames[s.i] || ' '\n"
						  "        END ||\n"
						  "        pg_catalog.format_type(p.proallargtypes[s.i], NULL)\n"
						  "      FROM\n"
						  "        pg_catalog.generate_series(1, pg_catalog.array_upper(p.proallargtypes, 1)) AS s(i)\n"
						  "    ), ', ')\n"
						  "  ELSE\n"
						  "    pg_catalog.array_to_string(ARRAY(\n"
						  "      SELECT\n"
						  "        CASE\n"
						  "          WHEN COALESCE(p.proargnames[s.i+1], '') = '' THEN ''\n"
						  "          ELSE p.proargnames[s.i+1] || ' '\n"
						  "          END ||\n"
						  "        pg_catalog.format_type(p.proargtypes[s.i], NULL)\n"
						  "      FROM\n"
						  "        pg_catalog.generate_series(0, pg_catalog.array_upper(p.proargtypes, 1)) AS s(i)\n"
						  "    ), ', ')\n"
						  "  END AS \"%s\",\n"
						  "  CASE\n"
						  "    WHEN p.proisagg THEN '%s'\n"
						  "    WHEN p.prorettype = 'pg_catalog.trigger'::pg_catalog.regtype THEN '%s'\n"
						  "    ELSE '%s'\n"
						  "  END AS \"%s\"",
						  gettext_noop("Result data type"),
						  gettext_noop("Argument data types"),
		/* translator: "agg" is short for "aggregate" */
						  gettext_noop("agg"),
						  gettext_noop("trigger"),
						  gettext_noop("func"),
						  gettext_noop("Type"));
	else
		appendPQExpBuffer(&buf,
						  "  CASE WHEN p.proretset THEN 'SETOF ' ELSE '' END ||\n"
						  "  pg_catalog.format_type(p.prorettype, NULL) as \"%s\",\n"
						  "  pg_catalog.oidvectortypes(p.proargtypes) as \"%s\",\n"
						  "  CASE\n"
						  "    WHEN p.proisagg THEN '%s'\n"
						  "    WHEN p.prorettype = 'pg_catalog.trigger'::pg_catalog.regtype THEN '%s'\n"
						  "    ELSE '%s'\n"
						  "  END AS \"%s\"",
						  gettext_noop("Result data type"),
						  gettext_noop("Argument data types"),
		/* translator: "agg" is short for "aggregate" */
						  gettext_noop("agg"),
						  gettext_noop("trigger"),
						  gettext_noop("func"),
						  gettext_noop("Type"));

	if (verbose)
	{
		appendPQExpBuffer(&buf,
						  ",\n CASE\n"
						  "  WHEN p.provolatile = 'i' THEN '%s'\n"
						  "  WHEN p.provolatile = 's' THEN '%s'\n"
						  "  WHEN p.provolatile = 'v' THEN '%s'\n"
						  " END as \"%s\"",
						  gettext_noop("immutable"),
						  gettext_noop("stable"),
						  gettext_noop("volatile"),
						  gettext_noop("Volatility"));
		if (pset.sversion >= 90600)
			appendPQExpBuffer(&buf,
							  ",\n CASE\n"
							  "  WHEN p.proparallel = 'r' THEN '%s'\n"
							  "  WHEN p.proparallel = 's' THEN '%s'\n"
							  "  WHEN p.proparallel = 'u' THEN '%s'\n"
							  " END as \"%s\"",
							  gettext_noop("restricted"),
							  gettext_noop("safe"),
							  gettext_noop("unsafe"),
							  gettext_noop("Parallel"));
		appendPQExpBuffer(&buf,
						  ",\n pg_catalog.pg_get_userbyid(p.proowner) as \"%s\""
						  ",\n CASE WHEN prosecdef THEN '%s' ELSE '%s' END AS \"%s\"",
						  gettext_noop("Owner"),
						  gettext_noop("definer"),
						  gettext_noop("invoker"),
						  gettext_noop("Security"));
		appendPQExpBufferStr(&buf, ",\n ");
		printACLColumn(&buf, "p.proacl");
		appendPQExpBuffer(&buf,
						  ",\n l.lanname as \"%s\""
						  ",\n p.prosrc as \"%s\""
						  ",\n pg_catalog.obj_description(p.oid, 'pg_proc') as \"%s\"",
						  gettext_noop("Language"),
						  gettext_noop("Source code"),
						  gettext_noop("Description"));
	}

	appendPQExpBufferStr(&buf,
						 "\nFROM pg_catalog.pg_proc p"
						 "\n     LEFT JOIN pg_catalog.pg_namespace n ON n.oid = p.pronamespace\n");

	if (verbose)
		appendPQExpBufferStr(&buf,
							 "     LEFT JOIN pg_catalog.pg_language l ON l.oid = p.prolang\n");

	have_where = false;

	/* filter by function type, if requested */
	if (showNormal && showAggregate && showProcedure && showTrigger && showWindow)
		 /* Do nothing */ ;
	else if (showNormal)
	{
		if (!showAggregate)
		{
			if (have_where)
				appendPQExpBufferStr(&buf, "      AND ");
			else
			{
				appendPQExpBufferStr(&buf, "WHERE ");
				have_where = true;
			}
			if (pset.sversion >= 110000)
				appendPQExpBufferStr(&buf, "p.prokind <> 'a'\n");
			else
				appendPQExpBufferStr(&buf, "NOT p.proisagg\n");
		}
		if (!showProcedure && pset.sversion >= 110000)
		{
			if (have_where)
				appendPQExpBufferStr(&buf, "      AND ");
			else
			{
				appendPQExpBufferStr(&buf, "WHERE ");
				have_where = true;
			}
			appendPQExpBufferStr(&buf, "p.prokind <> 'p'\n");
		}
		if (!showTrigger)
		{
			if (have_where)
				appendPQExpBufferStr(&buf, "      AND ");
			else
			{
				appendPQExpBufferStr(&buf, "WHERE ");
				have_where = true;
			}
			appendPQExpBufferStr(&buf, "p.prorettype <> 'pg_catalog.trigger'::pg_catalog.regtype\n");
		}
		if (!showWindow && pset.sversion >= 80400)
		{
			if (have_where)
				appendPQExpBufferStr(&buf, "      AND ");
			else
			{
				appendPQExpBufferStr(&buf, "WHERE ");
				have_where = true;
			}
			if (pset.sversion >= 110000)
				appendPQExpBufferStr(&buf, "p.prokind <> 'w'\n");
			else
				appendPQExpBufferStr(&buf, "NOT p.proiswindow\n");
		}
	}
	else
	{
		bool		needs_or = false;

		appendPQExpBufferStr(&buf, "WHERE (\n       ");
		have_where = true;
		/* Note: at least one of these must be true ... */
		if (showAggregate)
		{
			if (pset.sversion >= 110000)
				appendPQExpBufferStr(&buf, "p.prokind = 'a'\n");
			else
				appendPQExpBufferStr(&buf, "p.proisagg\n");
			needs_or = true;
		}
		if (showTrigger)
		{
			if (needs_or)
				appendPQExpBufferStr(&buf, "       OR ");
			appendPQExpBufferStr(&buf,
								 "p.prorettype = 'pg_catalog.trigger'::pg_catalog.regtype\n");
			needs_or = true;
		}
		if (showProcedure)
		{
			if (needs_or)
				appendPQExpBufferStr(&buf, "       OR ");
			appendPQExpBufferStr(&buf, "p.prokind = 'p'\n");
			needs_or = true;
		}
		if (showWindow)
		{
			if (needs_or)
				appendPQExpBufferStr(&buf, "       OR ");
			if (pset.sversion >= 110000)
				appendPQExpBufferStr(&buf, "p.prokind = 'w'\n");
			else
				appendPQExpBufferStr(&buf, "p.proiswindow\n");
			needs_or = true;
		}
		appendPQExpBufferStr(&buf, "      )\n");
	}

	processSQLNamePattern(pset.db, &buf, pattern, have_where, false,
						  "n.nspname", "p.proname", NULL,
						  "pg_catalog.pg_function_is_visible(p.oid)");

	if (!showSystem && !pattern)
		appendPQExpBufferStr(&buf, "      AND n.nspname <> 'pg_catalog'\n"
							 "      AND n.nspname <> 'information_schema'\n");

	appendPQExpBufferStr(&buf, "ORDER BY 1, 2, 4;");

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	myopt.title = _("List of functions");
	myopt.translate_header = true;
	if (pset.sversion >= 90600)
	{
		myopt.translate_columns = translate_columns;
		myopt.n_translate_columns = lengthof(translate_columns);
	}
	else
	{
		myopt.translate_columns = translate_columns_pre_96;
		myopt.n_translate_columns = lengthof(translate_columns_pre_96);
	}

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);
	return true;
}