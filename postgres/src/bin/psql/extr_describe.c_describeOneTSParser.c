#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int default_footer; } ;
struct TYPE_10__ {int translate_header; int const* translate_columns; scalar_t__ n_translate_columns; TYPE_1__ topt; int /*<<< orphan*/ * footers; int /*<<< orphan*/  title; int /*<<< orphan*/ * nullPrint; } ;
typedef  TYPE_2__ printQueryOpt ;
struct TYPE_12__ {int /*<<< orphan*/  logfile; int /*<<< orphan*/  queryFout; TYPE_2__ popt; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PSQLexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  gettext_noop (char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_3__*) ; 
 scalar_t__ lengthof (int const*) ; 
 int /*<<< orphan*/  printQuery (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_3__*,char*,char const*,...) ; 
 TYPE_5__ pset ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_3__*) ; 

__attribute__((used)) static bool
describeOneTSParser(const char *oid, const char *nspname, const char *prsname)
{
	PQExpBufferData buf;
	PGresult   *res;
	PQExpBufferData title;
	printQueryOpt myopt = pset.popt;
	static const bool translate_columns[] = {true, false, false};

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT '%s' AS \"%s\",\n"
					  "   p.prsstart::pg_catalog.regproc AS \"%s\",\n"
					  "   pg_catalog.obj_description(p.prsstart, 'pg_proc') as \"%s\"\n"
					  " FROM pg_catalog.pg_ts_parser p\n"
					  " WHERE p.oid = '%s'\n"
					  "UNION ALL\n"
					  "SELECT '%s',\n"
					  "   p.prstoken::pg_catalog.regproc,\n"
					  "   pg_catalog.obj_description(p.prstoken, 'pg_proc')\n"
					  " FROM pg_catalog.pg_ts_parser p\n"
					  " WHERE p.oid = '%s'\n"
					  "UNION ALL\n"
					  "SELECT '%s',\n"
					  "   p.prsend::pg_catalog.regproc,\n"
					  "   pg_catalog.obj_description(p.prsend, 'pg_proc')\n"
					  " FROM pg_catalog.pg_ts_parser p\n"
					  " WHERE p.oid = '%s'\n"
					  "UNION ALL\n"
					  "SELECT '%s',\n"
					  "   p.prsheadline::pg_catalog.regproc,\n"
					  "   pg_catalog.obj_description(p.prsheadline, 'pg_proc')\n"
					  " FROM pg_catalog.pg_ts_parser p\n"
					  " WHERE p.oid = '%s'\n"
					  "UNION ALL\n"
					  "SELECT '%s',\n"
					  "   p.prslextype::pg_catalog.regproc,\n"
					  "   pg_catalog.obj_description(p.prslextype, 'pg_proc')\n"
					  " FROM pg_catalog.pg_ts_parser p\n"
					  " WHERE p.oid = '%s';",
					  gettext_noop("Start parse"),
					  gettext_noop("Method"),
					  gettext_noop("Function"),
					  gettext_noop("Description"),
					  oid,
					  gettext_noop("Get next token"),
					  oid,
					  gettext_noop("End parse"),
					  oid,
					  gettext_noop("Get headline"),
					  oid,
					  gettext_noop("Get token types"),
					  oid);

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	initPQExpBuffer(&title);
	if (nspname)
		printfPQExpBuffer(&title, _("Text search parser \"%s.%s\""),
						  nspname, prsname);
	else
		printfPQExpBuffer(&title, _("Text search parser \"%s\""), prsname);
	myopt.title = title.data;
	myopt.footers = NULL;
	myopt.topt.default_footer = false;
	myopt.translate_header = true;
	myopt.translate_columns = translate_columns;
	myopt.n_translate_columns = lengthof(translate_columns);

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	PQclear(res);

	initPQExpBuffer(&buf);

	printfPQExpBuffer(&buf,
					  "SELECT t.alias as \"%s\",\n"
					  "  t.description as \"%s\"\n"
					  "FROM pg_catalog.ts_token_type( '%s'::pg_catalog.oid ) as t\n"
					  "ORDER BY 1;",
					  gettext_noop("Token name"),
					  gettext_noop("Description"),
					  oid);

	res = PSQLexec(buf.data);
	termPQExpBuffer(&buf);
	if (!res)
		return false;

	myopt.nullPrint = NULL;
	if (nspname)
		printfPQExpBuffer(&title, _("Token types for parser \"%s.%s\""),
						  nspname, prsname);
	else
		printfPQExpBuffer(&title, _("Token types for parser \"%s\""), prsname);
	myopt.title = title.data;
	myopt.footers = NULL;
	myopt.topt.default_footer = true;
	myopt.translate_header = true;
	myopt.translate_columns = NULL;
	myopt.n_translate_columns = 0;

	printQuery(res, &myopt, pset.queryFout, false, pset.logfile);

	termPQExpBuffer(&title);
	PQclear(res);
	return true;
}