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
struct TYPE_3__ {char const* query_string; char const* commandTag; int fixed_result; int rewriteRowSecurity; int dependsOnRLS; int is_oneshot; int is_complete; int is_saved; int is_valid; int generic_cost; scalar_t__ num_custom_plans; scalar_t__ total_custom_cost; scalar_t__ generation; int /*<<< orphan*/ * gplan; int /*<<< orphan*/  rewriteRoleId; int /*<<< orphan*/ * query_context; int /*<<< orphan*/ * search_path; void* invalItems; void* relationOids; void* query_list; int /*<<< orphan*/  context; int /*<<< orphan*/ * resultDesc; scalar_t__ cursor_options; int /*<<< orphan*/ * parserSetupArg; int /*<<< orphan*/ * parserSetup; scalar_t__ num_params; int /*<<< orphan*/ * param_types; int /*<<< orphan*/ * raw_parse_tree; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  RawStmt ;
typedef  TYPE_1__ CachedPlanSource ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CACHEDPLANSOURCE_MAGIC ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  InvalidOid ; 
 void* NIL ; 
 scalar_t__ palloc0 (int) ; 

CachedPlanSource *
CreateOneShotCachedPlan(RawStmt *raw_parse_tree,
						const char *query_string,
						const char *commandTag)
{
	CachedPlanSource *plansource;

	Assert(query_string != NULL);	/* required as of 8.4 */

	/*
	 * Create and fill the CachedPlanSource struct within the caller's memory
	 * context.  Most fields are just left empty for the moment.
	 */
	plansource = (CachedPlanSource *) palloc0(sizeof(CachedPlanSource));
	plansource->magic = CACHEDPLANSOURCE_MAGIC;
	plansource->raw_parse_tree = raw_parse_tree;
	plansource->query_string = query_string;
	plansource->commandTag = commandTag;
	plansource->param_types = NULL;
	plansource->num_params = 0;
	plansource->parserSetup = NULL;
	plansource->parserSetupArg = NULL;
	plansource->cursor_options = 0;
	plansource->fixed_result = false;
	plansource->resultDesc = NULL;
	plansource->context = CurrentMemoryContext;
	plansource->query_list = NIL;
	plansource->relationOids = NIL;
	plansource->invalItems = NIL;
	plansource->search_path = NULL;
	plansource->query_context = NULL;
	plansource->rewriteRoleId = InvalidOid;
	plansource->rewriteRowSecurity = false;
	plansource->dependsOnRLS = false;
	plansource->gplan = NULL;
	plansource->is_oneshot = true;
	plansource->is_complete = false;
	plansource->is_saved = false;
	plansource->is_valid = false;
	plansource->generation = 0;
	plansource->generic_cost = -1;
	plansource->total_custom_cost = 0;
	plansource->num_custom_plans = 0;

	return plansource;
}