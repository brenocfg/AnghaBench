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
struct TYPE_4__ {scalar_t__ magic; int is_complete; int is_oneshot; int num_params; int is_saved; int /*<<< orphan*/  num_custom_plans; int /*<<< orphan*/  total_custom_cost; int /*<<< orphan*/  generic_cost; int /*<<< orphan*/  generation; int /*<<< orphan*/  is_valid; int /*<<< orphan*/ * gplan; int /*<<< orphan*/  dependsOnRLS; int /*<<< orphan*/  rewriteRowSecurity; int /*<<< orphan*/  rewriteRoleId; void* query_context; scalar_t__ search_path; void* invalItems; void* relationOids; void* query_list; void* context; int /*<<< orphan*/ * resultDesc; int /*<<< orphan*/  fixed_result; int /*<<< orphan*/  cursor_options; int /*<<< orphan*/  parserSetupArg; int /*<<< orphan*/  parserSetup; int /*<<< orphan*/ * param_types; int /*<<< orphan*/  commandTag; int /*<<< orphan*/  query_string; void* raw_parse_tree; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  void* MemoryContext ;
typedef  TYPE_1__ CachedPlanSource ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_START_SMALL_SIZES ; 
 void* AllocSetContextCreate (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHEDPLANSOURCE_MAGIC ; 
 scalar_t__ CopyOverrideSearchPath (scalar_t__) ; 
 int /*<<< orphan*/ * CreateTupleDescCopy (int /*<<< orphan*/ *) ; 
 void* CurrentMemoryContext ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSetIdentifier (void*,int /*<<< orphan*/ ) ; 
 void* MemoryContextSwitchTo (void*) ; 
 void* copyObject (void*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 

CachedPlanSource *
CopyCachedPlan(CachedPlanSource *plansource)
{
	CachedPlanSource *newsource;
	MemoryContext source_context;
	MemoryContext querytree_context;
	MemoryContext oldcxt;

	Assert(plansource->magic == CACHEDPLANSOURCE_MAGIC);
	Assert(plansource->is_complete);

	/*
	 * One-shot plans can't be copied, because we haven't taken care that
	 * parsing/planning didn't scribble on the raw parse tree or querytrees.
	 */
	if (plansource->is_oneshot)
		elog(ERROR, "cannot copy a one-shot cached plan");

	source_context = AllocSetContextCreate(CurrentMemoryContext,
										   "CachedPlanSource",
										   ALLOCSET_START_SMALL_SIZES);

	oldcxt = MemoryContextSwitchTo(source_context);

	newsource = (CachedPlanSource *) palloc0(sizeof(CachedPlanSource));
	newsource->magic = CACHEDPLANSOURCE_MAGIC;
	newsource->raw_parse_tree = copyObject(plansource->raw_parse_tree);
	newsource->query_string = pstrdup(plansource->query_string);
	MemoryContextSetIdentifier(source_context, newsource->query_string);
	newsource->commandTag = plansource->commandTag;
	if (plansource->num_params > 0)
	{
		newsource->param_types = (Oid *)
			palloc(plansource->num_params * sizeof(Oid));
		memcpy(newsource->param_types, plansource->param_types,
			   plansource->num_params * sizeof(Oid));
	}
	else
		newsource->param_types = NULL;
	newsource->num_params = plansource->num_params;
	newsource->parserSetup = plansource->parserSetup;
	newsource->parserSetupArg = plansource->parserSetupArg;
	newsource->cursor_options = plansource->cursor_options;
	newsource->fixed_result = plansource->fixed_result;
	if (plansource->resultDesc)
		newsource->resultDesc = CreateTupleDescCopy(plansource->resultDesc);
	else
		newsource->resultDesc = NULL;
	newsource->context = source_context;

	querytree_context = AllocSetContextCreate(source_context,
											  "CachedPlanQuery",
											  ALLOCSET_START_SMALL_SIZES);
	MemoryContextSwitchTo(querytree_context);
	newsource->query_list = copyObject(plansource->query_list);
	newsource->relationOids = copyObject(plansource->relationOids);
	newsource->invalItems = copyObject(plansource->invalItems);
	if (plansource->search_path)
		newsource->search_path = CopyOverrideSearchPath(plansource->search_path);
	newsource->query_context = querytree_context;
	newsource->rewriteRoleId = plansource->rewriteRoleId;
	newsource->rewriteRowSecurity = plansource->rewriteRowSecurity;
	newsource->dependsOnRLS = plansource->dependsOnRLS;

	newsource->gplan = NULL;

	newsource->is_oneshot = false;
	newsource->is_complete = true;
	newsource->is_saved = false;
	newsource->is_valid = plansource->is_valid;
	newsource->generation = plansource->generation;

	/* We may as well copy any acquired cost knowledge */
	newsource->generic_cost = plansource->generic_cost;
	newsource->total_custom_cost = plansource->total_custom_cost;
	newsource->num_custom_plans = plansource->num_custom_plans;

	MemoryContextSwitchTo(oldcxt);

	return newsource;
}