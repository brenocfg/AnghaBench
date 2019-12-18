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
struct TYPE_3__ {int /*<<< orphan*/  es_query_cxt; int /*<<< orphan*/ * es_partition_directory; int /*<<< orphan*/ * es_jit; scalar_t__ es_exprcontexts; } ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  TYPE_1__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyPartitionDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeExprContext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jit_release_context (int /*<<< orphan*/ *) ; 
 scalar_t__ linitial (scalar_t__) ; 

void
FreeExecutorState(EState *estate)
{
	/*
	 * Shut down and free any remaining ExprContexts.  We do this explicitly
	 * to ensure that any remaining shutdown callbacks get called (since they
	 * might need to release resources that aren't simply memory within the
	 * per-query memory context).
	 */
	while (estate->es_exprcontexts)
	{
		/*
		 * XXX: seems there ought to be a faster way to implement this than
		 * repeated list_delete(), no?
		 */
		FreeExprContext((ExprContext *) linitial(estate->es_exprcontexts),
						true);
		/* FreeExprContext removed the list link for us */
	}

	/* release JIT context, if allocated */
	if (estate->es_jit)
	{
		jit_release_context(estate->es_jit);
		estate->es_jit = NULL;
	}

	/* release partition directory, if allocated */
	if (estate->es_partition_directory)
	{
		DestroyPartitionDirectory(estate->es_partition_directory);
		estate->es_partition_directory = NULL;
	}

	/*
	 * Free the per-query memory context, thereby releasing all working
	 * memory, including the EState node itself.
	 */
	MemoryContextDelete(estate->es_query_cxt);
}