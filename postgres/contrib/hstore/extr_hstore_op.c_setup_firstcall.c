#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int /*<<< orphan*/  tuple_desc; void* user_fctx; int /*<<< orphan*/  multi_call_memory_ctx; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HStore ;
typedef  scalar_t__ FunctionCallInfo ;
typedef  TYPE_1__ FuncCallContext ;

/* Variables and functions */
 int /*<<< orphan*/  BlessTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPEFUNC_COMPOSITE ; 
 int /*<<< orphan*/  VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_call_result_type (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setup_firstcall(FuncCallContext *funcctx, HStore *hs,
				FunctionCallInfo fcinfo)
{
	MemoryContext oldcontext;
	HStore	   *st;

	oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

	st = (HStore *) palloc(VARSIZE(hs));
	memcpy(st, hs, VARSIZE(hs));

	funcctx->user_fctx = (void *) st;

	if (fcinfo)
	{
		TupleDesc	tupdesc;

		/* Build a tuple descriptor for our result type */
		if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
			elog(ERROR, "return type must be a row type");

		funcctx->tuple_desc = BlessTupleDesc(tupdesc);
	}

	MemoryContextSwitchTo(oldcontext);
}