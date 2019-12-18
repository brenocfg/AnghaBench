#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_9__ {int /*<<< orphan*/  attinmeta; int /*<<< orphan*/  tuple_desc; int /*<<< orphan*/  multi_call_memory_ctx; void* user_fctx; } ;
struct TYPE_8__ {struct TYPE_8__* left; } ;
struct TYPE_7__ {int maxdepth; size_t stackpos; TYPE_2__** stack; TYPE_2__* root; } ;
typedef  TYPE_1__ TSVectorStat ;
typedef  TYPE_2__ StatEntry ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  FunctionCallInfo ;
typedef  TYPE_3__ FuncCallContext ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BlessTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  INT4OID ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TupleDescGetAttInMetadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__** palloc0 (int) ; 

__attribute__((used)) static void
ts_setup_firstcall(FunctionCallInfo fcinfo, FuncCallContext *funcctx,
				   TSVectorStat *stat)
{
	TupleDesc	tupdesc;
	MemoryContext oldcontext;
	StatEntry  *node;

	funcctx->user_fctx = (void *) stat;

	oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

	stat->stack = palloc0(sizeof(StatEntry *) * (stat->maxdepth + 1));
	stat->stackpos = 0;

	node = stat->root;
	/* find leftmost value */
	if (node == NULL)
		stat->stack[stat->stackpos] = NULL;
	else
		for (;;)
		{
			stat->stack[stat->stackpos] = node;
			if (node->left)
			{
				stat->stackpos++;
				node = node->left;
			}
			else
				break;
		}
	Assert(stat->stackpos <= stat->maxdepth);

	tupdesc = CreateTemplateTupleDesc(3);
	TupleDescInitEntry(tupdesc, (AttrNumber) 1, "word",
					   TEXTOID, -1, 0);
	TupleDescInitEntry(tupdesc, (AttrNumber) 2, "ndoc",
					   INT4OID, -1, 0);
	TupleDescInitEntry(tupdesc, (AttrNumber) 3, "nentry",
					   INT4OID, -1, 0);
	funcctx->tuple_desc = BlessTupleDesc(tupdesc);
	funcctx->attinmeta = TupleDescGetAttInMetadata(tupdesc);

	MemoryContextSwitchTo(oldcontext);
}