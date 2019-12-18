#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  (* func_end ) (TYPE_2__*,TYPE_1__*) ;int /*<<< orphan*/  (* func_beg ) (TYPE_2__*,TYPE_1__*) ;} ;
struct TYPE_20__ {struct TYPE_20__* previous; TYPE_2__* arg; int /*<<< orphan*/  callback; } ;
struct TYPE_19__ {int /*<<< orphan*/ * err_text; int /*<<< orphan*/ * err_stmt; int /*<<< orphan*/ * evtrigdata; } ;
struct TYPE_18__ {scalar_t__ action; } ;
typedef  int /*<<< orphan*/  PLpgSQL_stmt ;
typedef  TYPE_1__ PLpgSQL_function ;
typedef  TYPE_2__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  EventTriggerData ;
typedef  TYPE_3__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_S_R_E_FUNCTION_EXECUTED_NO_RETURN_STATEMENT ; 
 int /*<<< orphan*/  ERROR ; 
 int PLPGSQL_RC_RETURN ; 
 int /*<<< orphan*/  copy_plpgsql_datums (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_3__* error_context_stack ; 
 int /*<<< orphan*/  exec_eval_cleanup (TYPE_2__*) ; 
 int exec_stmt (TYPE_2__*,int /*<<< orphan*/ *) ; 
 void* gettext_noop (char*) ; 
 int /*<<< orphan*/  plpgsql_destroy_econtext (TYPE_2__*) ; 
 int /*<<< orphan*/  plpgsql_estate_setup (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plpgsql_exec_error_callback ; 
 TYPE_8__** plpgsql_plugin_ptr ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,TYPE_1__*) ; 

void
plpgsql_exec_event_trigger(PLpgSQL_function *func, EventTriggerData *trigdata)
{
	PLpgSQL_execstate estate;
	ErrorContextCallback plerrcontext;
	int			rc;

	/*
	 * Setup the execution state
	 */
	plpgsql_estate_setup(&estate, func, NULL, NULL);
	estate.evtrigdata = trigdata;

	/*
	 * Setup error traceback support for ereport()
	 */
	plerrcontext.callback = plpgsql_exec_error_callback;
	plerrcontext.arg = &estate;
	plerrcontext.previous = error_context_stack;
	error_context_stack = &plerrcontext;

	/*
	 * Make local execution copies of all the datums
	 */
	estate.err_text = gettext_noop("during initialization of execution state");
	copy_plpgsql_datums(&estate, func);

	/*
	 * Let the instrumentation plugin peek at this function
	 */
	if (*plpgsql_plugin_ptr && (*plpgsql_plugin_ptr)->func_beg)
		((*plpgsql_plugin_ptr)->func_beg) (&estate, func);

	/*
	 * Now call the toplevel block of statements
	 */
	estate.err_text = NULL;
	estate.err_stmt = (PLpgSQL_stmt *) (func->action);
	rc = exec_stmt(&estate, (PLpgSQL_stmt *) func->action);
	if (rc != PLPGSQL_RC_RETURN)
	{
		estate.err_stmt = NULL;
		estate.err_text = NULL;
		ereport(ERROR,
				(errcode(ERRCODE_S_R_E_FUNCTION_EXECUTED_NO_RETURN_STATEMENT),
				 errmsg("control reached end of trigger procedure without RETURN")));
	}

	estate.err_stmt = NULL;
	estate.err_text = gettext_noop("during function exit");

	/*
	 * Let the instrumentation plugin peek at this function
	 */
	if (*plpgsql_plugin_ptr && (*plpgsql_plugin_ptr)->func_end)
		((*plpgsql_plugin_ptr)->func_end) (&estate, func);

	/* Clean up any leftover temporary memory */
	plpgsql_destroy_econtext(&estate);
	exec_eval_cleanup(&estate);
	/* stmt_mcontext will be destroyed when function's main context is */

	/*
	 * Pop the error context stack
	 */
	error_context_stack = plerrcontext.previous;

	return;
}