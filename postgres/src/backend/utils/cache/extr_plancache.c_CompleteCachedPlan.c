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
struct TYPE_4__ {scalar_t__ magic; int is_complete; int num_params; int cursor_options; int fixed_result; int is_valid; int /*<<< orphan*/  resultDesc; void* parserSetupArg; int /*<<< orphan*/  parserSetup; int /*<<< orphan*/ * param_types; int /*<<< orphan*/  search_path; int /*<<< orphan*/  rewriteRowSecurity; int /*<<< orphan*/  rewriteRoleId; int /*<<< orphan*/  dependsOnRLS; int /*<<< orphan*/  invalItems; int /*<<< orphan*/  relationOids; scalar_t__ is_oneshot; int /*<<< orphan*/ * query_list; int /*<<< orphan*/ * query_context; int /*<<< orphan*/ * context; } ;
typedef  int /*<<< orphan*/  ParserSetupHook ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ CachedPlanSource ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_START_SMALL_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHEDPLANSOURCE_MAGIC ; 
 int /*<<< orphan*/ * CurrentMemoryContext ; 
 int /*<<< orphan*/  GetOverrideSearchPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  IsTransactionStmtPlan (TYPE_1__*) ; 
 int /*<<< orphan*/  MemoryContextSetParent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PlanCacheComputeResultDesc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_query_dependencies (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  row_security ; 

void
CompleteCachedPlan(CachedPlanSource *plansource,
				   List *querytree_list,
				   MemoryContext querytree_context,
				   Oid *param_types,
				   int num_params,
				   ParserSetupHook parserSetup,
				   void *parserSetupArg,
				   int cursor_options,
				   bool fixed_result)
{
	MemoryContext source_context = plansource->context;
	MemoryContext oldcxt = CurrentMemoryContext;

	/* Assert caller is doing things in a sane order */
	Assert(plansource->magic == CACHEDPLANSOURCE_MAGIC);
	Assert(!plansource->is_complete);

	/*
	 * If caller supplied a querytree_context, reparent it underneath the
	 * CachedPlanSource's context; otherwise, create a suitable context and
	 * copy the querytree_list into it.  But no data copying should be done
	 * for one-shot plans; for those, assume the passed querytree_list is
	 * sufficiently long-lived.
	 */
	if (plansource->is_oneshot)
	{
		querytree_context = CurrentMemoryContext;
	}
	else if (querytree_context != NULL)
	{
		MemoryContextSetParent(querytree_context, source_context);
		MemoryContextSwitchTo(querytree_context);
	}
	else
	{
		/* Again, it's a good bet the querytree_context can be small */
		querytree_context = AllocSetContextCreate(source_context,
												  "CachedPlanQuery",
												  ALLOCSET_START_SMALL_SIZES);
		MemoryContextSwitchTo(querytree_context);
		querytree_list = copyObject(querytree_list);
	}

	plansource->query_context = querytree_context;
	plansource->query_list = querytree_list;

	if (!plansource->is_oneshot && !IsTransactionStmtPlan(plansource))
	{
		/*
		 * Use the planner machinery to extract dependencies.  Data is saved
		 * in query_context.  (We assume that not a lot of extra cruft is
		 * created by this call.)  We can skip this for one-shot plans, and
		 * transaction control commands have no such dependencies anyway.
		 */
		extract_query_dependencies((Node *) querytree_list,
								   &plansource->relationOids,
								   &plansource->invalItems,
								   &plansource->dependsOnRLS);

		/* Update RLS info as well. */
		plansource->rewriteRoleId = GetUserId();
		plansource->rewriteRowSecurity = row_security;

		/*
		 * Also save the current search_path in the query_context.  (This
		 * should not generate much extra cruft either, since almost certainly
		 * the path is already valid.)	Again, we don't really need this for
		 * one-shot plans; and we *must* skip this for transaction control
		 * commands, because this could result in catalog accesses.
		 */
		plansource->search_path = GetOverrideSearchPath(querytree_context);
	}

	/*
	 * Save the final parameter types (or other parameter specification data)
	 * into the source_context, as well as our other parameters.  Also save
	 * the result tuple descriptor.
	 */
	MemoryContextSwitchTo(source_context);

	if (num_params > 0)
	{
		plansource->param_types = (Oid *) palloc(num_params * sizeof(Oid));
		memcpy(plansource->param_types, param_types, num_params * sizeof(Oid));
	}
	else
		plansource->param_types = NULL;
	plansource->num_params = num_params;
	plansource->parserSetup = parserSetup;
	plansource->parserSetupArg = parserSetupArg;
	plansource->cursor_options = cursor_options;
	plansource->fixed_result = fixed_result;
	plansource->resultDesc = PlanCacheComputeResultDesc(querytree_list);

	MemoryContextSwitchTo(oldcxt);

	plansource->is_complete = true;
	plansource->is_valid = true;
}