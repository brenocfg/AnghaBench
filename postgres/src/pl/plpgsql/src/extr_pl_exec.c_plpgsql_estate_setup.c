#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  plpgsql_CastHashKey ;
typedef  int /*<<< orphan*/  plpgsql_CastHashEntry ;
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_22__ {int /*<<< orphan*/  (* func_setup ) (TYPE_4__*,TYPE_3__*) ;int /*<<< orphan*/  assign_expr; int /*<<< orphan*/  error_callback; } ;
struct TYPE_21__ {int keysize; int entrysize; void* hcxt; } ;
struct TYPE_20__ {int retisnull; int atomic; int /*<<< orphan*/ * plugin_info; int /*<<< orphan*/ * err_text; int /*<<< orphan*/ * err_stmt; int /*<<< orphan*/ * eval_econtext; scalar_t__ eval_processed; int /*<<< orphan*/ * eval_tuptable; void* stmt_mcontext_parent; int /*<<< orphan*/ * stmt_mcontext; void* cast_hash_context; int /*<<< orphan*/ * cast_hash; int /*<<< orphan*/ * simple_eval_estate; int /*<<< orphan*/  ndatums; TYPE_14__* paramLI; void* datum_context; int /*<<< orphan*/ * datums; int /*<<< orphan*/  found_varno; TYPE_2__* rsi; int /*<<< orphan*/ * tuple_store_owner; int /*<<< orphan*/ * tuple_store_cxt; int /*<<< orphan*/ * tuple_store_desc; int /*<<< orphan*/ * tuple_store; int /*<<< orphan*/ * cur_error; int /*<<< orphan*/ * exitlabel; int /*<<< orphan*/  readonly_func; int /*<<< orphan*/  retisset; int /*<<< orphan*/  retistuple; int /*<<< orphan*/  fn_rettype; int /*<<< orphan*/  rettype; scalar_t__ retval; int /*<<< orphan*/ * evtrigdata; int /*<<< orphan*/ * trigdata; TYPE_3__* func; } ;
struct TYPE_19__ {int /*<<< orphan*/  ndatums; int /*<<< orphan*/  found_varno; int /*<<< orphan*/  fn_readonly; int /*<<< orphan*/  fn_retset; int /*<<< orphan*/  fn_retistuple; int /*<<< orphan*/  fn_rettype; TYPE_4__* cur_estate; } ;
struct TYPE_18__ {TYPE_1__* econtext; } ;
struct TYPE_17__ {int /*<<< orphan*/ * ecxt_per_query_memory; } ;
struct TYPE_16__ {int /*<<< orphan*/  numParams; int /*<<< orphan*/ * parserSetupArg; scalar_t__ parserSetup; int /*<<< orphan*/ * paramCompileArg; int /*<<< orphan*/  paramCompile; void* paramFetchArg; int /*<<< orphan*/  paramFetch; } ;
typedef  TYPE_2__ ReturnSetInfo ;
typedef  scalar_t__ ParserSetupHook ;
typedef  TYPE_3__ PLpgSQL_function ;
typedef  TYPE_4__ PLpgSQL_execstate ;
typedef  TYPE_5__ HASHCTL ;
typedef  int /*<<< orphan*/  EState ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 void* AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* CurrentMemoryContext ; 
 int /*<<< orphan*/ * CurrentResourceOwner ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  exec_assign_expr ; 
 void* hash_create (char*,int,TYPE_5__*,int) ; 
 TYPE_14__* makeParamList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plpgsql_create_econtext (TYPE_4__*) ; 
 int /*<<< orphan*/  plpgsql_exec_error_callback ; 
 int /*<<< orphan*/  plpgsql_param_compile ; 
 int /*<<< orphan*/  plpgsql_param_fetch ; 
 scalar_t__ plpgsql_parser_setup ; 
 TYPE_8__** plpgsql_plugin_ptr ; 
 void* shared_cast_context ; 
 int /*<<< orphan*/ * shared_cast_hash ; 
 int /*<<< orphan*/ * shared_simple_eval_estate ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static void
plpgsql_estate_setup(PLpgSQL_execstate *estate,
					 PLpgSQL_function *func,
					 ReturnSetInfo *rsi,
					 EState *simple_eval_estate)
{
	HASHCTL		ctl;

	/* this link will be restored at exit from plpgsql_call_handler */
	func->cur_estate = estate;

	estate->func = func;
	estate->trigdata = NULL;
	estate->evtrigdata = NULL;

	estate->retval = (Datum) 0;
	estate->retisnull = true;
	estate->rettype = InvalidOid;

	estate->fn_rettype = func->fn_rettype;
	estate->retistuple = func->fn_retistuple;
	estate->retisset = func->fn_retset;

	estate->readonly_func = func->fn_readonly;
	estate->atomic = true;

	estate->exitlabel = NULL;
	estate->cur_error = NULL;

	estate->tuple_store = NULL;
	estate->tuple_store_desc = NULL;
	if (rsi)
	{
		estate->tuple_store_cxt = rsi->econtext->ecxt_per_query_memory;
		estate->tuple_store_owner = CurrentResourceOwner;
	}
	else
	{
		estate->tuple_store_cxt = NULL;
		estate->tuple_store_owner = NULL;
	}
	estate->rsi = rsi;

	estate->found_varno = func->found_varno;
	estate->ndatums = func->ndatums;
	estate->datums = NULL;
	/* the datums array will be filled by copy_plpgsql_datums() */
	estate->datum_context = CurrentMemoryContext;

	/* initialize our ParamListInfo with appropriate hook functions */
	estate->paramLI = makeParamList(0);
	estate->paramLI->paramFetch = plpgsql_param_fetch;
	estate->paramLI->paramFetchArg = (void *) estate;
	estate->paramLI->paramCompile = plpgsql_param_compile;
	estate->paramLI->paramCompileArg = NULL;	/* not needed */
	estate->paramLI->parserSetup = (ParserSetupHook) plpgsql_parser_setup;
	estate->paramLI->parserSetupArg = NULL; /* filled during use */
	estate->paramLI->numParams = estate->ndatums;

	/* set up for use of appropriate simple-expression EState and cast hash */
	if (simple_eval_estate)
	{
		estate->simple_eval_estate = simple_eval_estate;
		/* Private cast hash just lives in function's main context */
		memset(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(plpgsql_CastHashKey);
		ctl.entrysize = sizeof(plpgsql_CastHashEntry);
		ctl.hcxt = CurrentMemoryContext;
		estate->cast_hash = hash_create("PLpgSQL private cast cache",
										16, /* start small and extend */
										&ctl,
										HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);
		estate->cast_hash_context = CurrentMemoryContext;
	}
	else
	{
		estate->simple_eval_estate = shared_simple_eval_estate;
		/* Create the session-wide cast-info hash table if we didn't already */
		if (shared_cast_hash == NULL)
		{
			shared_cast_context = AllocSetContextCreate(TopMemoryContext,
														"PLpgSQL cast info",
														ALLOCSET_DEFAULT_SIZES);
			memset(&ctl, 0, sizeof(ctl));
			ctl.keysize = sizeof(plpgsql_CastHashKey);
			ctl.entrysize = sizeof(plpgsql_CastHashEntry);
			ctl.hcxt = shared_cast_context;
			shared_cast_hash = hash_create("PLpgSQL cast cache",
										   16,	/* start small and extend */
										   &ctl,
										   HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);
		}
		estate->cast_hash = shared_cast_hash;
		estate->cast_hash_context = shared_cast_context;
	}

	/*
	 * We start with no stmt_mcontext; one will be created only if needed.
	 * That context will be a direct child of the function's main execution
	 * context.  Additional stmt_mcontexts might be created as children of it.
	 */
	estate->stmt_mcontext = NULL;
	estate->stmt_mcontext_parent = CurrentMemoryContext;

	estate->eval_tuptable = NULL;
	estate->eval_processed = 0;
	estate->eval_econtext = NULL;

	estate->err_stmt = NULL;
	estate->err_text = NULL;

	estate->plugin_info = NULL;

	/*
	 * Create an EState and ExprContext for evaluation of simple expressions.
	 */
	plpgsql_create_econtext(estate);

	/*
	 * Let the plugin see this function before we initialize any local
	 * PL/pgSQL variables - note that we also give the plugin a few function
	 * pointers so it can call back into PL/pgSQL for doing things like
	 * variable assignments and stack traces
	 */
	if (*plpgsql_plugin_ptr)
	{
		(*plpgsql_plugin_ptr)->error_callback = plpgsql_exec_error_callback;
		(*plpgsql_plugin_ptr)->assign_expr = exec_assign_expr;

		if ((*plpgsql_plugin_ptr)->func_setup)
			((*plpgsql_plugin_ptr)->func_setup) (estate, func);
	}
}