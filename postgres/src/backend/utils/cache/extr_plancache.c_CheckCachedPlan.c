#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ magic; int is_valid; scalar_t__ planRoleId; scalar_t__ refcount; int /*<<< orphan*/  stmt_list; int /*<<< orphan*/  saved_xmin; scalar_t__ dependsOnRole; int /*<<< orphan*/  is_oneshot; } ;
struct TYPE_5__ {int is_valid; TYPE_2__* gplan; } ;
typedef  TYPE_1__ CachedPlanSource ;
typedef  TYPE_2__ CachedPlan ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireExecutorLocks (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHEDPLAN_MAGIC ; 
 scalar_t__ GetUserId () ; 
 int /*<<< orphan*/  ReleaseGenericPlan (TYPE_1__*) ; 
 int /*<<< orphan*/  TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionXmin ; 

__attribute__((used)) static bool
CheckCachedPlan(CachedPlanSource *plansource)
{
	CachedPlan *plan = plansource->gplan;

	/* Assert that caller checked the querytree */
	Assert(plansource->is_valid);

	/* If there's no generic plan, just say "false" */
	if (!plan)
		return false;

	Assert(plan->magic == CACHEDPLAN_MAGIC);
	/* Generic plans are never one-shot */
	Assert(!plan->is_oneshot);

	/*
	 * If plan isn't valid for current role, we can't use it.
	 */
	if (plan->is_valid && plan->dependsOnRole &&
		plan->planRoleId != GetUserId())
		plan->is_valid = false;

	/*
	 * If it appears valid, acquire locks and recheck; this is much the same
	 * logic as in RevalidateCachedQuery, but for a plan.
	 */
	if (plan->is_valid)
	{
		/*
		 * Plan must have positive refcount because it is referenced by
		 * plansource; so no need to fear it disappears under us here.
		 */
		Assert(plan->refcount > 0);

		AcquireExecutorLocks(plan->stmt_list, true);

		/*
		 * If plan was transient, check to see if TransactionXmin has
		 * advanced, and if so invalidate it.
		 */
		if (plan->is_valid &&
			TransactionIdIsValid(plan->saved_xmin) &&
			!TransactionIdEquals(plan->saved_xmin, TransactionXmin))
			plan->is_valid = false;

		/*
		 * By now, if any invalidation has happened, the inval callback
		 * functions will have marked the plan invalid.
		 */
		if (plan->is_valid)
		{
			/* Successfully revalidated and locked the query. */
			return true;
		}

		/* Oops, the race case happened.  Release useless locks. */
		AcquireExecutorLocks(plan->stmt_list, false);
	}

	/*
	 * Plan has been invalidated, so unlink it from the parent and release it.
	 */
	ReleaseGenericPlan(plansource);

	return false;
}