#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_11__ {int /*<<< orphan*/  readonly_func; } ;
struct TYPE_10__ {int /*<<< orphan*/ * nulls; int /*<<< orphan*/ * values; int /*<<< orphan*/ * types; int /*<<< orphan*/  nargs; } ;
typedef  TYPE_1__ PreparedParamsData ;
typedef  int /*<<< orphan*/ * Portal ;
typedef  int /*<<< orphan*/  PLpgSQL_expr ;
typedef  TYPE_2__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 char* MemoryContextStrdup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * SPI_cursor_open_with_args (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPI_result ; 
 int /*<<< orphan*/  SPI_result_code_string (int /*<<< orphan*/ ) ; 
 char* convert_value_to_string (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  exec_eval_expr (TYPE_2__*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* exec_eval_using_params (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_stmt_mcontext (TYPE_2__*) ; 

__attribute__((used)) static Portal
exec_dynquery_with_params(PLpgSQL_execstate *estate,
						  PLpgSQL_expr *dynquery,
						  List *params,
						  const char *portalname,
						  int cursorOptions)
{
	Portal		portal;
	Datum		query;
	bool		isnull;
	Oid			restype;
	int32		restypmod;
	char	   *querystr;
	MemoryContext stmt_mcontext = get_stmt_mcontext(estate);

	/*
	 * Evaluate the string expression after the EXECUTE keyword. Its result is
	 * the querystring we have to execute.
	 */
	query = exec_eval_expr(estate, dynquery, &isnull, &restype, &restypmod);
	if (isnull)
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("query string argument of EXECUTE is null")));

	/* Get the C-String representation */
	querystr = convert_value_to_string(estate, query, restype);

	/* copy it into the stmt_mcontext before we clean up */
	querystr = MemoryContextStrdup(stmt_mcontext, querystr);

	exec_eval_cleanup(estate);

	/*
	 * Open an implicit cursor for the query.  We use
	 * SPI_cursor_open_with_args even when there are no params, because this
	 * avoids making and freeing one copy of the plan.
	 */
	if (params)
	{
		PreparedParamsData *ppd;

		ppd = exec_eval_using_params(estate, params);
		portal = SPI_cursor_open_with_args(portalname,
										   querystr,
										   ppd->nargs, ppd->types,
										   ppd->values, ppd->nulls,
										   estate->readonly_func,
										   cursorOptions);
	}
	else
	{
		portal = SPI_cursor_open_with_args(portalname,
										   querystr,
										   0, NULL,
										   NULL, NULL,
										   estate->readonly_func,
										   cursorOptions);
	}

	if (portal == NULL)
		elog(ERROR, "could not open implicit cursor for query \"%s\": %s",
			 querystr, SPI_result_code_string(SPI_result));

	/* Release transient data */
	MemoryContextReset(stmt_mcontext);

	return portal;
}