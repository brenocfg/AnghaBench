#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  set_args ;
struct TYPE_32__ {int /*<<< orphan*/  readonly_func; scalar_t__* datums; } ;
struct TYPE_31__ {int /*<<< orphan*/ * plan; } ;
struct TYPE_30__ {int into; int /*<<< orphan*/ * target; int /*<<< orphan*/ * sqlstmt; int /*<<< orphan*/  lineno; int /*<<< orphan*/  cmd_type; } ;
struct TYPE_29__ {size_t curvar; int /*<<< orphan*/ * argquery; int /*<<< orphan*/  lineno; } ;
struct TYPE_28__ {size_t cursor_explicit_argrow; int /*<<< orphan*/  cursor_options; TYPE_5__* cursor_explicit_expr; int /*<<< orphan*/  value; int /*<<< orphan*/  isnull; } ;
struct TYPE_27__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* Portal ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  PLpgSQL_variable ;
typedef  TYPE_2__ PLpgSQL_var ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt_forq ;
typedef  TYPE_3__ PLpgSQL_stmt_forc ;
typedef  TYPE_4__ PLpgSQL_stmt_execsql ;
typedef  TYPE_5__ PLpgSQL_expr ;
typedef  TYPE_6__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (TYPE_5__*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_CURSOR ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 scalar_t__ PLPGSQL_RC_OK ; 
 int /*<<< orphan*/  PLPGSQL_STMT_EXECSQL ; 
 int /*<<< orphan*/  SPI_cursor_close (TYPE_1__*) ; 
 int /*<<< orphan*/ * SPI_cursor_find (char*) ; 
 TYPE_1__* SPI_cursor_open_with_paramlist (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_result ; 
 int /*<<< orphan*/  SPI_result_code_string (int /*<<< orphan*/ ) ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_simple_var (TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  assign_text_var (TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_6__*) ; 
 int exec_for_query (TYPE_6__*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  exec_prepare_plan (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_stmt_execsql (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * get_stmt_mcontext (TYPE_6__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_param_list (TYPE_6__*,TYPE_5__*) ; 

__attribute__((used)) static int
exec_stmt_forc(PLpgSQL_execstate *estate, PLpgSQL_stmt_forc *stmt)
{
	PLpgSQL_var *curvar;
	MemoryContext stmt_mcontext = NULL;
	char	   *curname = NULL;
	PLpgSQL_expr *query;
	ParamListInfo paramLI;
	Portal		portal;
	int			rc;

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
	 * Open the cursor just like an OPEN command
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
	Assert(query);

	if (query->plan == NULL)
		exec_prepare_plan(estate, query, curvar->cursor_options, true);

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

	/*
	 * Clean up before entering exec_for_query
	 */
	exec_eval_cleanup(estate);
	if (stmt_mcontext)
		MemoryContextReset(stmt_mcontext);

	/*
	 * Execute the loop.  We can't prefetch because the cursor is accessible
	 * to the user, for instance via UPDATE WHERE CURRENT OF within the loop.
	 */
	rc = exec_for_query(estate, (PLpgSQL_stmt_forq *) stmt, portal, false);

	/* ----------
	 * Close portal, and restore cursor variable if it was initially NULL.
	 * ----------
	 */
	SPI_cursor_close(portal);

	if (curname == NULL)
		assign_simple_var(estate, curvar, (Datum) 0, true, false);

	return rc;
}