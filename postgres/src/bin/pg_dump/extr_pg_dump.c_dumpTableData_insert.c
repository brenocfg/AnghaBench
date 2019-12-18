#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__* attgenerated; scalar_t__ needs_override; scalar_t__ ispartition; } ;
typedef  TYPE_1__ TableInfo ;
struct TYPE_23__ {scalar_t__ filtercond; TYPE_1__* tdtable; } ;
typedef  TYPE_2__ TableDataInfo ;
struct TYPE_26__ {TYPE_4__* dopt; } ;
struct TYPE_25__ {int dump_inserts; scalar_t__ do_nothing; scalar_t__ column_inserts; scalar_t__ load_via_partition_root; } ;
struct TYPE_24__ {char* data; } ;
typedef  TYPE_3__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ DumpOptions ;
typedef  TYPE_5__ Archive ;

/* Variables and functions */
#define  BITOID 137 
#define  BOOLOID 136 
 int /*<<< orphan*/ * ExecuteSqlQuery (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecuteSqlStatement (TYPE_5__*,char*) ; 
#define  FLOAT4OID 135 
#define  FLOAT8OID 134 
#define  INT2OID 133 
#define  INT4OID 132 
#define  INT8OID 131 
#define  NUMERICOID 130 
#define  OIDOID 129 
 int /*<<< orphan*/  PGRES_TUPLES_OK ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfname (int /*<<< orphan*/ *,int) ; 
 int PQftype (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PQgetisnull (int /*<<< orphan*/ *,int,int) ; 
 char const* PQgetvalue (int /*<<< orphan*/ *,int,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
#define  VARBITOID 128 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_3__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  appendStringLiteralAH (TYPE_3__*,char const*,TYPE_5__*) ; 
 int /*<<< orphan*/  archprintf (TYPE_5__*,char*,char const*) ; 
 int /*<<< orphan*/  archputs (char const*,TYPE_5__*) ; 
 TYPE_3__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_3__*) ; 
 char* fmtId (int /*<<< orphan*/ ) ; 
 scalar_t__ fmtQualifiedDumpable (TYPE_1__*) ; 
 TYPE_1__* getRootTableInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 

__attribute__((used)) static int
dumpTableData_insert(Archive *fout, void *dcontext)
{
	TableDataInfo *tdinfo = (TableDataInfo *) dcontext;
	TableInfo  *tbinfo = tdinfo->tdtable;
	DumpOptions *dopt = fout->dopt;
	PQExpBuffer q = createPQExpBuffer();
	PQExpBuffer insertStmt = NULL;
	PGresult   *res;
	int			nfields;
	int			rows_per_statement = dopt->dump_inserts;
	int			rows_this_statement = 0;

	appendPQExpBuffer(q, "DECLARE _pg_dump_cursor CURSOR FOR "
					  "SELECT * FROM ONLY %s",
					  fmtQualifiedDumpable(tbinfo));
	if (tdinfo->filtercond)
		appendPQExpBuffer(q, " %s", tdinfo->filtercond);

	ExecuteSqlStatement(fout, q->data);

	while (1)
	{
		res = ExecuteSqlQuery(fout, "FETCH 100 FROM _pg_dump_cursor",
							  PGRES_TUPLES_OK);
		nfields = PQnfields(res);

		/*
		 * First time through, we build as much of the INSERT statement as
		 * possible in "insertStmt", which we can then just print for each
		 * statement. If the table happens to have zero columns then this will
		 * be a complete statement, otherwise it will end in "VALUES" and be
		 * ready to have the row's column values printed.
		 */
		if (insertStmt == NULL)
		{
			TableInfo  *targettab;

			insertStmt = createPQExpBuffer();

			/*
			 * When load-via-partition-root is set, get the root table name
			 * for the partition table, so that we can reload data through the
			 * root table.
			 */
			if (dopt->load_via_partition_root && tbinfo->ispartition)
				targettab = getRootTableInfo(tbinfo);
			else
				targettab = tbinfo;

			appendPQExpBuffer(insertStmt, "INSERT INTO %s ",
							  fmtQualifiedDumpable(targettab));

			/* corner case for zero-column table */
			if (nfields == 0)
			{
				appendPQExpBufferStr(insertStmt, "DEFAULT VALUES;\n");
			}
			else
			{
				/* append the list of column names if required */
				if (dopt->column_inserts)
				{
					appendPQExpBufferChar(insertStmt, '(');
					for (int field = 0; field < nfields; field++)
					{
						if (field > 0)
							appendPQExpBufferStr(insertStmt, ", ");
						appendPQExpBufferStr(insertStmt,
											 fmtId(PQfname(res, field)));
					}
					appendPQExpBufferStr(insertStmt, ") ");
				}

				if (tbinfo->needs_override)
					appendPQExpBufferStr(insertStmt, "OVERRIDING SYSTEM VALUE ");

				appendPQExpBufferStr(insertStmt, "VALUES");
			}
		}

		for (int tuple = 0; tuple < PQntuples(res); tuple++)
		{
			/* Write the INSERT if not in the middle of a multi-row INSERT. */
			if (rows_this_statement == 0)
				archputs(insertStmt->data, fout);

			/*
			 * If it is zero-column table then we've already written the
			 * complete statement, which will mean we've disobeyed
			 * --rows-per-insert when it's set greater than 1.  We do support
			 * a way to make this multi-row with: SELECT UNION ALL SELECT
			 * UNION ALL ... but that's non-standard so we should avoid it
			 * given that using INSERTs is mostly only ever needed for
			 * cross-database exports.
			 */
			if (nfields == 0)
				continue;

			/* Emit a row heading */
			if (rows_per_statement == 1)
				archputs(" (", fout);
			else if (rows_this_statement > 0)
				archputs(",\n\t(", fout);
			else
				archputs("\n\t(", fout);

			for (int field = 0; field < nfields; field++)
			{
				if (field > 0)
					archputs(", ", fout);
				if (tbinfo->attgenerated[field])
				{
					archputs("DEFAULT", fout);
					continue;
				}
				if (PQgetisnull(res, tuple, field))
				{
					archputs("NULL", fout);
					continue;
				}

				/* XXX This code is partially duplicated in ruleutils.c */
				switch (PQftype(res, field))
				{
					case INT2OID:
					case INT4OID:
					case INT8OID:
					case OIDOID:
					case FLOAT4OID:
					case FLOAT8OID:
					case NUMERICOID:
						{
							/*
							 * These types are printed without quotes unless
							 * they contain values that aren't accepted by the
							 * scanner unquoted (e.g., 'NaN').  Note that
							 * strtod() and friends might accept NaN, so we
							 * can't use that to test.
							 *
							 * In reality we only need to defend against
							 * infinity and NaN, so we need not get too crazy
							 * about pattern matching here.
							 */
							const char *s = PQgetvalue(res, tuple, field);

							if (strspn(s, "0123456789 +-eE.") == strlen(s))
								archputs(s, fout);
							else
								archprintf(fout, "'%s'", s);
						}
						break;

					case BITOID:
					case VARBITOID:
						archprintf(fout, "B'%s'",
								   PQgetvalue(res, tuple, field));
						break;

					case BOOLOID:
						if (strcmp(PQgetvalue(res, tuple, field), "t") == 0)
							archputs("true", fout);
						else
							archputs("false", fout);
						break;

					default:
						/* All other types are printed as string literals. */
						resetPQExpBuffer(q);
						appendStringLiteralAH(q,
											  PQgetvalue(res, tuple, field),
											  fout);
						archputs(q->data, fout);
						break;
				}
			}

			/* Terminate the row ... */
			archputs(")", fout);

			/* ... and the statement, if the target no. of rows is reached */
			if (++rows_this_statement >= rows_per_statement)
			{
				if (dopt->do_nothing)
					archputs(" ON CONFLICT DO NOTHING;\n", fout);
				else
					archputs(";\n", fout);
				/* Reset the row counter */
				rows_this_statement = 0;
			}
		}

		if (PQntuples(res) <= 0)
		{
			PQclear(res);
			break;
		}
		PQclear(res);
	}

	/* Terminate any statements that didn't make the row count. */
	if (rows_this_statement > 0)
	{
		if (dopt->do_nothing)
			archputs(" ON CONFLICT DO NOTHING;\n", fout);
		else
			archputs(";\n", fout);
	}

	archputs("\n\n", fout);

	ExecuteSqlStatement(fout, "CLOSE _pg_dump_cursor");

	destroyPQExpBuffer(q);
	if (insertStmt != NULL)
		destroyPQExpBuffer(insertStmt);

	return 1;
}