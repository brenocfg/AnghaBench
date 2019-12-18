#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_25__ {TYPE_2__* func; scalar_t__* datums; void* eval_processed; int /*<<< orphan*/  readonly_func; } ;
struct TYPE_24__ {scalar_t__ strict; TYPE_1__* target; scalar_t__ into; int /*<<< orphan*/  params; int /*<<< orphan*/  query; } ;
struct TYPE_23__ {int /*<<< orphan*/  nulls; int /*<<< orphan*/  values; int /*<<< orphan*/  types; int /*<<< orphan*/  nargs; } ;
struct TYPE_22__ {int /*<<< orphan*/  tupdesc; int /*<<< orphan*/ ** vals; } ;
struct TYPE_21__ {scalar_t__ print_strict_params; } ;
struct TYPE_20__ {size_t dno; } ;
typedef  TYPE_3__ SPITupleTable ;
typedef  TYPE_4__ PreparedParamsData ;
typedef  int /*<<< orphan*/  PLpgSQL_variable ;
typedef  TYPE_5__ PLpgSQL_stmt_dynexecute ;
typedef  TYPE_6__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_NO_DATA_FOUND ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERRCODE_TOO_MANY_ROWS ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 char* MemoryContextStrdup (int /*<<< orphan*/ ,char*) ; 
 int PLPGSQL_RC_OK ; 
#define  SPI_ERROR_COPY 139 
#define  SPI_ERROR_TRANSACTION 138 
#define  SPI_OK_DELETE 137 
#define  SPI_OK_DELETE_RETURNING 136 
#define  SPI_OK_INSERT 135 
#define  SPI_OK_INSERT_RETURNING 134 
#define  SPI_OK_REWRITTEN 133 
#define  SPI_OK_SELECT 132 
#define  SPI_OK_SELINTO 131 
#define  SPI_OK_UPDATE 130 
#define  SPI_OK_UPDATE_RETURNING 129 
#define  SPI_OK_UTILITY 128 
 int SPI_execute (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPI_execute_with_args (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_freetuptable (TYPE_3__*) ; 
 void* SPI_processed ; 
 int /*<<< orphan*/  SPI_result_code_string (int) ; 
 TYPE_3__* SPI_tuptable ; 
 char* convert_value_to_string (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_6__*) ; 
 int /*<<< orphan*/  exec_eval_expr (TYPE_6__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* exec_eval_using_params (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_move_row (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* format_preparedparamsdata (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  get_stmt_mcontext (TYPE_6__*) ; 

__attribute__((used)) static int
exec_stmt_dynexecute(PLpgSQL_execstate *estate,
					 PLpgSQL_stmt_dynexecute *stmt)
{
	Datum		query;
	bool		isnull;
	Oid			restype;
	int32		restypmod;
	char	   *querystr;
	int			exec_res;
	PreparedParamsData *ppd = NULL;
	MemoryContext stmt_mcontext = get_stmt_mcontext(estate);

	/*
	 * First we evaluate the string expression after the EXECUTE keyword. Its
	 * result is the querystring we have to execute.
	 */
	query = exec_eval_expr(estate, stmt->query, &isnull, &restype, &restypmod);
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
	 * Execute the query without preparing a saved plan.
	 */
	if (stmt->params)
	{
		ppd = exec_eval_using_params(estate, stmt->params);
		exec_res = SPI_execute_with_args(querystr,
										 ppd->nargs, ppd->types,
										 ppd->values, ppd->nulls,
										 estate->readonly_func, 0);
	}
	else
		exec_res = SPI_execute(querystr, estate->readonly_func, 0);

	switch (exec_res)
	{
		case SPI_OK_SELECT:
		case SPI_OK_INSERT:
		case SPI_OK_UPDATE:
		case SPI_OK_DELETE:
		case SPI_OK_INSERT_RETURNING:
		case SPI_OK_UPDATE_RETURNING:
		case SPI_OK_DELETE_RETURNING:
		case SPI_OK_UTILITY:
		case SPI_OK_REWRITTEN:
			break;

		case 0:

			/*
			 * Also allow a zero return, which implies the querystring
			 * contained no commands.
			 */
			break;

		case SPI_OK_SELINTO:

			/*
			 * We want to disallow SELECT INTO for now, because its behavior
			 * is not consistent with SELECT INTO in a normal plpgsql context.
			 * (We need to reimplement EXECUTE to parse the string as a
			 * plpgsql command, not just feed it to SPI_execute.)  This is not
			 * a functional limitation because CREATE TABLE AS is allowed.
			 */
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("EXECUTE of SELECT ... INTO is not implemented"),
					 errhint("You might want to use EXECUTE ... INTO or EXECUTE CREATE TABLE ... AS instead.")));
			break;

			/* Some SPI errors deserve specific error messages */
		case SPI_ERROR_COPY:
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot COPY to/from client in PL/pgSQL")));
			break;

		case SPI_ERROR_TRANSACTION:
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("EXECUTE of transaction commands is not implemented")));
			break;

		default:
			elog(ERROR, "SPI_execute failed executing query \"%s\": %s",
				 querystr, SPI_result_code_string(exec_res));
			break;
	}

	/* Save result info for GET DIAGNOSTICS */
	estate->eval_processed = SPI_processed;

	/* Process INTO if present */
	if (stmt->into)
	{
		SPITupleTable *tuptab = SPI_tuptable;
		uint64		n = SPI_processed;
		PLpgSQL_variable *target;

		/* If the statement did not return a tuple table, complain */
		if (tuptab == NULL)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("INTO used with a command that cannot return data")));

		/* Fetch target's datum entry */
		target = (PLpgSQL_variable *) estate->datums[stmt->target->dno];

		/*
		 * If SELECT ... INTO specified STRICT, and the query didn't find
		 * exactly one row, throw an error.  If STRICT was not specified, then
		 * allow the query to find any number of rows.
		 */
		if (n == 0)
		{
			if (stmt->strict)
			{
				char	   *errdetail;

				if (estate->func->print_strict_params)
					errdetail = format_preparedparamsdata(estate, ppd);
				else
					errdetail = NULL;

				ereport(ERROR,
						(errcode(ERRCODE_NO_DATA_FOUND),
						 errmsg("query returned no rows"),
						 errdetail ? errdetail_internal("parameters: %s", errdetail) : 0));
			}
			/* set the target to NULL(s) */
			exec_move_row(estate, target, NULL, tuptab->tupdesc);
		}
		else
		{
			if (n > 1 && stmt->strict)
			{
				char	   *errdetail;

				if (estate->func->print_strict_params)
					errdetail = format_preparedparamsdata(estate, ppd);
				else
					errdetail = NULL;

				ereport(ERROR,
						(errcode(ERRCODE_TOO_MANY_ROWS),
						 errmsg("query returned more than one row"),
						 errdetail ? errdetail_internal("parameters: %s", errdetail) : 0));
			}

			/* Put the first result row into the target */
			exec_move_row(estate, target, tuptab->vals[0], tuptab->tupdesc);
		}
		/* clean up after exec_move_row() */
		exec_eval_cleanup(estate);
	}
	else
	{
		/*
		 * It might be a good idea to raise an error if the query returned
		 * tuples that are being ignored, but historically we have not done
		 * that.
		 */
	}

	/* Release any result from SPI_execute, as well as transient data */
	SPI_freetuptable(SPI_tuptable);
	MemoryContextReset(stmt_mcontext);

	return PLPGSQL_RC_OK;
}