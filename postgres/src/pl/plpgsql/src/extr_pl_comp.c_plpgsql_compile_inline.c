#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_12__ {char* arg; struct TYPE_12__* previous; int /*<<< orphan*/  callback; } ;
struct TYPE_11__ {int out_param_varno; scalar_t__ fn_rettype; int fn_retset; int fn_retistuple; int fn_retisdomain; int fn_retbyval; int fn_rettyplen; int fn_readonly; scalar_t__ fn_nargs; int /*<<< orphan*/  action; int /*<<< orphan*/  found_varno; int /*<<< orphan*/  fn_prokind; scalar_t__ nstatements; scalar_t__ extra_errors; scalar_t__ extra_warnings; int /*<<< orphan*/  print_strict_params; int /*<<< orphan*/  resolve_option; int /*<<< orphan*/ * fn_cxt; int /*<<< orphan*/  fn_input_collation; int /*<<< orphan*/  fn_is_trigger; int /*<<< orphan*/  fn_signature; } ;
struct TYPE_10__ {int /*<<< orphan*/  dno; } ;
typedef  TYPE_1__ PLpgSQL_variable ;
typedef  TYPE_2__ PLpgSQL_function ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  TYPE_3__ ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BOOLOID ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PLPGSQL_LABEL_BLOCK ; 
 int /*<<< orphan*/  PLPGSQL_NOT_TRIGGER ; 
 int /*<<< orphan*/  PROKIND_FUNCTION ; 
 scalar_t__ VOIDOID ; 
 int /*<<< orphan*/  add_dummy_return (TYPE_2__*) ; 
 int check_function_bodies ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__* error_context_stack ; 
 scalar_t__ palloc0 (int) ; 
 int plpgsql_DumpExecTree ; 
 int /*<<< orphan*/  plpgsql_build_datatype (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* plpgsql_build_variable (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int plpgsql_check_syntax ; 
 int /*<<< orphan*/  plpgsql_compile_error_callback ; 
 int /*<<< orphan*/ * plpgsql_compile_tmp_cxt ; 
 TYPE_2__* plpgsql_curr_compile ; 
 char* plpgsql_error_funcname ; 
 int /*<<< orphan*/  plpgsql_finish_datums (TYPE_2__*) ; 
 int /*<<< orphan*/  plpgsql_ns_init () ; 
 int /*<<< orphan*/  plpgsql_ns_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plpgsql_parse_result ; 
 int /*<<< orphan*/  plpgsql_print_strict_params ; 
 int /*<<< orphan*/  plpgsql_scanner_finish () ; 
 int /*<<< orphan*/  plpgsql_scanner_init (char*) ; 
 int /*<<< orphan*/  plpgsql_start_datums () ; 
 int /*<<< orphan*/  plpgsql_variable_conflict ; 
 int plpgsql_yyparse () ; 
 int /*<<< orphan*/  pstrdup (char*) ; 

PLpgSQL_function *
plpgsql_compile_inline(char *proc_source)
{
	char	   *func_name = "inline_code_block";
	PLpgSQL_function *function;
	ErrorContextCallback plerrcontext;
	PLpgSQL_variable *var;
	int			parse_rc;
	MemoryContext func_cxt;

	/*
	 * Setup the scanner input and error info.  We assume that this function
	 * cannot be invoked recursively, so there's no need to save and restore
	 * the static variables used here.
	 */
	plpgsql_scanner_init(proc_source);

	plpgsql_error_funcname = func_name;

	/*
	 * Setup error traceback support for ereport()
	 */
	plerrcontext.callback = plpgsql_compile_error_callback;
	plerrcontext.arg = proc_source;
	plerrcontext.previous = error_context_stack;
	error_context_stack = &plerrcontext;

	/* Do extra syntax checking if check_function_bodies is on */
	plpgsql_check_syntax = check_function_bodies;

	/* Function struct does not live past current statement */
	function = (PLpgSQL_function *) palloc0(sizeof(PLpgSQL_function));

	plpgsql_curr_compile = function;

	/*
	 * All the rest of the compile-time storage (e.g. parse tree) is kept in
	 * its own memory context, so it can be reclaimed easily.
	 */
	func_cxt = AllocSetContextCreate(CurrentMemoryContext,
									 "PL/pgSQL inline code context",
									 ALLOCSET_DEFAULT_SIZES);
	plpgsql_compile_tmp_cxt = MemoryContextSwitchTo(func_cxt);

	function->fn_signature = pstrdup(func_name);
	function->fn_is_trigger = PLPGSQL_NOT_TRIGGER;
	function->fn_input_collation = InvalidOid;
	function->fn_cxt = func_cxt;
	function->out_param_varno = -1; /* set up for no OUT param */
	function->resolve_option = plpgsql_variable_conflict;
	function->print_strict_params = plpgsql_print_strict_params;

	/*
	 * don't do extra validation for inline code as we don't want to add spam
	 * at runtime
	 */
	function->extra_warnings = 0;
	function->extra_errors = 0;

	function->nstatements = 0;

	plpgsql_ns_init();
	plpgsql_ns_push(func_name, PLPGSQL_LABEL_BLOCK);
	plpgsql_DumpExecTree = false;
	plpgsql_start_datums();

	/* Set up as though in a function returning VOID */
	function->fn_rettype = VOIDOID;
	function->fn_retset = false;
	function->fn_retistuple = false;
	function->fn_retisdomain = false;
	function->fn_prokind = PROKIND_FUNCTION;
	/* a bit of hardwired knowledge about type VOID here */
	function->fn_retbyval = true;
	function->fn_rettyplen = sizeof(int32);

	/*
	 * Remember if function is STABLE/IMMUTABLE.  XXX would it be better to
	 * set this true inside a read-only transaction?  Not clear.
	 */
	function->fn_readonly = false;

	/*
	 * Create the magic FOUND variable.
	 */
	var = plpgsql_build_variable("found", 0,
								 plpgsql_build_datatype(BOOLOID,
														-1,
														InvalidOid,
														NULL),
								 true);
	function->found_varno = var->dno;

	/*
	 * Now parse the function's text
	 */
	parse_rc = plpgsql_yyparse();
	if (parse_rc != 0)
		elog(ERROR, "plpgsql parser returned %d", parse_rc);
	function->action = plpgsql_parse_result;

	plpgsql_scanner_finish();

	/*
	 * If it returns VOID (always true at the moment), we allow control to
	 * fall off the end without an explicit RETURN statement.
	 */
	if (function->fn_rettype == VOIDOID)
		add_dummy_return(function);

	/*
	 * Complete the function's info
	 */
	function->fn_nargs = 0;

	plpgsql_finish_datums(function);

	/*
	 * Pop the error context stack
	 */
	error_context_stack = plerrcontext.previous;
	plpgsql_error_funcname = NULL;

	plpgsql_check_syntax = false;

	MemoryContextSwitchTo(plpgsql_compile_tmp_cxt);
	plpgsql_compile_tmp_cxt = NULL;
	return function;
}