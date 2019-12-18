#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nworkers; int /*<<< orphan*/  node; int /*<<< orphan*/  estimator; int /*<<< orphan*/  error_context_stack; void* function_name; void* library_name; int /*<<< orphan*/  subid; } ;
typedef  TYPE_1__ ParallelContext ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int IsInParallelMode () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopTransactionContext ; 
 int /*<<< orphan*/  dlist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_context_stack ; 
 TYPE_1__* palloc0 (int) ; 
 int /*<<< orphan*/  pcxt_list ; 
 void* pstrdup (char const*) ; 
 int /*<<< orphan*/  shm_toc_initialize_estimator (int /*<<< orphan*/ *) ; 

ParallelContext *
CreateParallelContext(const char *library_name, const char *function_name,
					  int nworkers)
{
	MemoryContext oldcontext;
	ParallelContext *pcxt;

	/* It is unsafe to create a parallel context if not in parallel mode. */
	Assert(IsInParallelMode());

	/* Number of workers should be non-negative. */
	Assert(nworkers >= 0);

	/* We might be running in a short-lived memory context. */
	oldcontext = MemoryContextSwitchTo(TopTransactionContext);

	/* Initialize a new ParallelContext. */
	pcxt = palloc0(sizeof(ParallelContext));
	pcxt->subid = GetCurrentSubTransactionId();
	pcxt->nworkers = nworkers;
	pcxt->library_name = pstrdup(library_name);
	pcxt->function_name = pstrdup(function_name);
	pcxt->error_context_stack = error_context_stack;
	shm_toc_initialize_estimator(&pcxt->estimator);
	dlist_push_head(&pcxt_list, &pcxt->node);

	/* Restore previous memory context. */
	MemoryContextSwitchTo(oldcontext);

	return pcxt;
}