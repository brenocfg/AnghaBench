#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * user_fctx; int /*<<< orphan*/  multi_call_memory_ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  ListCell ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JsonbValue ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  TYPE_1__ JsonValueList ;
typedef  int /*<<< orphan*/  JsonPath ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  TYPE_2__ FuncCallContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * JsonValueListGetList (TYPE_1__*) ; 
 int /*<<< orphan*/  JsonbPGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsonbValueToJsonb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int PG_GETARG_BOOL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_JSONB_P_COPY (int) ; 
 int /*<<< orphan*/ * PG_GETARG_JSONPATH_P_COPY (int) ; 
 TYPE_2__* SRF_FIRSTCALL_INIT () ; 
 scalar_t__ SRF_IS_FIRSTCALL () ; 
 TYPE_2__* SRF_PERCALL_SETUP () ; 
 int /*<<< orphan*/  SRF_RETURN_DONE (TYPE_2__*) ; 
 int /*<<< orphan*/  SRF_RETURN_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  executeJsonPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * lfirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_delete_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Datum
jsonb_path_query_internal(FunctionCallInfo fcinfo, bool tz)
{
	FuncCallContext *funcctx;
	List	   *found;
	JsonbValue *v;
	ListCell   *c;

	if (SRF_IS_FIRSTCALL())
	{
		JsonPath   *jp;
		Jsonb	   *jb;
		MemoryContext oldcontext;
		Jsonb	   *vars;
		bool		silent;
		JsonValueList found = {0};

		funcctx = SRF_FIRSTCALL_INIT();
		oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

		jb = PG_GETARG_JSONB_P_COPY(0);
		jp = PG_GETARG_JSONPATH_P_COPY(1);
		vars = PG_GETARG_JSONB_P_COPY(2);
		silent = PG_GETARG_BOOL(3);

		(void) executeJsonPath(jp, vars, jb, !silent, &found, tz);

		funcctx->user_fctx = JsonValueListGetList(&found);

		MemoryContextSwitchTo(oldcontext);
	}

	funcctx = SRF_PERCALL_SETUP();
	found = funcctx->user_fctx;

	c = list_head(found);

	if (c == NULL)
		SRF_RETURN_DONE(funcctx);

	v = lfirst(c);
	funcctx->user_fctx = list_delete_first(found);

	SRF_RETURN_NEXT(funcctx, JsonbPGetDatum(JsonbValueToJsonb(v)));
}