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
struct TYPE_4__ {int cursor_options; int num_custom_plans; double total_custom_cost; double generic_cost; scalar_t__ is_oneshot; } ;
typedef  int /*<<< orphan*/ * ParamListInfo ;
typedef  TYPE_1__ CachedPlanSource ;

/* Variables and functions */
 int CURSOR_OPT_CUSTOM_PLAN ; 
 int CURSOR_OPT_GENERIC_PLAN ; 
 scalar_t__ IsTransactionStmtPlan (TYPE_1__*) ; 
 scalar_t__ PLAN_CACHE_MODE_FORCE_CUSTOM_PLAN ; 
 scalar_t__ PLAN_CACHE_MODE_FORCE_GENERIC_PLAN ; 
 scalar_t__ plan_cache_mode ; 

__attribute__((used)) static bool
choose_custom_plan(CachedPlanSource *plansource, ParamListInfo boundParams)
{
	double		avg_custom_cost;

	/* One-shot plans will always be considered custom */
	if (plansource->is_oneshot)
		return true;

	/* Otherwise, never any point in a custom plan if there's no parameters */
	if (boundParams == NULL)
		return false;
	/* ... nor for transaction control statements */
	if (IsTransactionStmtPlan(plansource))
		return false;

	/* Let settings force the decision */
	if (plan_cache_mode == PLAN_CACHE_MODE_FORCE_GENERIC_PLAN)
		return false;
	if (plan_cache_mode == PLAN_CACHE_MODE_FORCE_CUSTOM_PLAN)
		return true;

	/* See if caller wants to force the decision */
	if (plansource->cursor_options & CURSOR_OPT_GENERIC_PLAN)
		return false;
	if (plansource->cursor_options & CURSOR_OPT_CUSTOM_PLAN)
		return true;

	/* Generate custom plans until we have done at least 5 (arbitrary) */
	if (plansource->num_custom_plans < 5)
		return true;

	avg_custom_cost = plansource->total_custom_cost / plansource->num_custom_plans;

	/*
	 * Prefer generic plan if it's less expensive than the average custom
	 * plan.  (Because we include a charge for cost of planning in the
	 * custom-plan costs, this means the generic plan only has to be less
	 * expensive than the execution cost plus replan cost of the custom
	 * plans.)
	 *
	 * Note that if generic_cost is -1 (indicating we've not yet determined
	 * the generic plan cost), we'll always prefer generic at this point.
	 */
	if (plansource->generic_cost < avg_custom_cost)
		return false;

	return true;
}