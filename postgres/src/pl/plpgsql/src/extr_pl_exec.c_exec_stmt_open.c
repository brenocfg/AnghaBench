#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  set_args ;
struct TYPE_28__ {int /*<<< orphan*/  readonly_func; scalar_t__* datums; } ;
struct TYPE_27__ {int /*<<< orphan*/ * plan; } ;
struct TYPE_26__ {int into; int /*<<< orphan*/ * target; int /*<<< orphan*/ * sqlstmt; int /*<<< orphan*/  lineno; int /*<<< orphan*/  cmd_type; } ;
struct TYPE_25__ {size_t curvar; int /*<<< orphan*/ * argquery; int /*<<< orphan*/  lineno; int /*<<< orphan*/  cursor_options; int /*<<< orphan*/  params; int /*<<< orphan*/ * dynquery; TYPE_5__* query; } ;
struct TYPE_24__ {size_t cursor_explicit_argrow; int /*<<< orphan*/  cursor_options; TYPE_5__* cursor_explicit_expr; int /*<<< orphan*/  value; int /*<<< orphan*/  isnull; } ;
struct TYPE_23__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* Portal ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  PLpgSQL_variable ;
typedef  TYPE_2__ PLpgSQL_var ;
typedef  TYPE_3__ PLpgSQL_stmt_open ;
typedef  TYPE_4__ PLpgSQL_stmt_execsql ;
typedef  TYPE_5__ PLpgSQL_expr ;
typedef  TYPE_6__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/ * MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DUPLICATE_CURSOR ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int PLPGSQL_RC_OK ; 
 int /*<<< orphan*/  PLPGSQL_STMT_EXECSQL ; 
 int /*<<< orphan*/ * SPI_cursor_find (char*) ; 
 TYPE_1__* SPI_cursor_open_with_paramlist (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_result ; 
 int /*<<< orphan*/  SPI_result_code_string (int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_text_var (TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_1__* exec_dynquery_with_params (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_6__*) ; 
 int /*<<< orphan*/  exec_prepare_plan (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int exec_stmt_execsql (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * get_stmt_mcontext (TYPE_6__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_param_list (TYPE_6__*,TYPE_5__*) ; 

__attribute__((used)) static int
exec_stmt_open(PLpgSQL_execstate *estate, PLpgSQL_stmt_open *stmt)
{
	PLpgSQL_var *curvar;
	MemoryContext stmt_mcontext = NULL;
	char	   *curname = NULL;
	PLpgSQL_expr *query;
	Portal		portal;
	ParamListInfo paramLI;

	/* ----------
	 * Get the cursor variable and if it has an assigned name, check
	 * that it's not in use currently.
	 * ----------
	 */
	curvar = (PLpgSQL_var *) (estate->datums[stmt->curvar]);
	if (!curvar->isnull)
	{
		MemoryContext oldcontext;

		/* We only need stmt_mcontext to hold the cursor name string */
		stmt_mcontext = get_stmt_mcontext(estate);
		oldcontext = MemoryContextSwitchTo(stmt_mcontext);
		curname = TextDatumGetCString(curvar->value);
		MemoryContextSwitchTo(oldcontext);

		if (SPI_cursor_find(curname) != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_CURSOR),
					 errmsg("cursor \"%s\" already in use", curname)));
	}

	/* ----------
	 * Process the OPEN according to it's type.
	 * ----------
	 */
	if (stmt->query != NULL)
	{
		/* ----------
		 * This is an OPEN refcursor FOR SELECT ...
		 *
		 * We just make sure the query is planned. The real work is
		 * done downstairs.
		 * ----------
		 */
		query = stmt->query;
		if (query->plan == NULL)
			exec_prepare_plan(estate, query, stmt->cursor_options, true);
	}
	else if (stmt->dynquery != NULL)
	{
		/* ----------
		 * This is an OPEN refcursor FOR EXECUTE ...
		 * ----------
		 */
		portal = exec_dynquery_with_params(estate,
										   stmt->dynquery,
										   stmt->params,
										   curname,
										   stmt->cursor_options);

		/*
		 * If cursor variable was NULL, store the generated portal name in it.
		 * Note: exec_dynquery_with_params already reset the stmt_mcontext, so
		 * curname is a dangling pointer here; but testing it for nullness is
		 * OK.
		 */
		if (curname == NULL)
			assign_text_var(estate, curvar, portal->name);

		return PLPGSQL_RC_OK;
	}
	else
	{
		/* ----------
		 * This is an OPEN cursor
		 *
		 * Note: parser should already have checked that statement supplies
		 * args iff cursor needs them, but we check again to be safe.
		 * ----------
		 */
		if (stmt->argquery != NULL)
		{
			/* ----------
			 * OPEN CURSOR with args.  We fake a SELECT ... INTO ...
			 * statement to evaluate the args and put 'em into the
			 * internal row.
			 * ----------
			 */
			PLpgSQL_stmt_execsql set_args;

			if (curvar->cursor_explicit_argrow < 0)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("arguments given for cursor without arguments")));

			memset(&set_args, 0, sizeof(set_args));
			set_args.cmd_type = PLPGSQL_STMT_EXECSQL;
			set_args.lineno = stmt->lineno;
			set_args.sqlstmt = stmt->argquery;
			set_args.into = true;
			/* XXX historically this has not been STRICT */
			set_args.target = (PLpgSQL_variable *)
				(estate->datums[curvar->cursor_explicit_argrow]);

			if (exec_stmt_execsql(estate, &set_args) != PLPGSQL_RC_OK)
				elog(ERROR, "open cursor failed during argument processing");
		}
		else
		{
			if (curvar->cursor_explicit_argrow >= 0)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("arguments required for cursor")));
		}

		query = curvar->cursor_explicit_expr;
		if (query->plan == NULL)
			exec_prepare_plan(estate, query, curvar->cursor_options, true);
	}

	/*
	 * Set up ParamListInfo for this query
	 */
	paramLI = setup_param_list(estate, query);

	/*
	 * Open the cursor (the paramlist will get copied into the portal)
	 */
	portal = SPI_cursor_open_with_paramlist(curname, query->plan,
											paramLI,
											estate->readonly_func);
	if (portal == NULL)
		elog(ERROR, "could not open cursor: %s",
			 SPI_result_code_string(SPI_result));

	/*
	 * If cursor variable was NULL, store the generated portal name in it
	 */
	if (curname == NULL)
		assign_text_var(estate, curvar, portal->name);

	/* If we had any transient data, clean it up */
	exec_eval_cleanup(estate);
	if (stmt_mcontext)
		MemoryContextReset(stmt_mcontext);

	return PLPGSQL_RC_OK;
}