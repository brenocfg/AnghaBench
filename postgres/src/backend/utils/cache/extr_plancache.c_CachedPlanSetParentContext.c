#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ magic; int is_complete; TYPE_1__* gplan; int /*<<< orphan*/  context; scalar_t__ is_oneshot; scalar_t__ is_saved; } ;
struct TYPE_4__ {scalar_t__ magic; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ CachedPlanSource ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHEDPLANSOURCE_MAGIC ; 
 scalar_t__ CACHEDPLAN_MAGIC ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MemoryContextSetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
CachedPlanSetParentContext(CachedPlanSource *plansource,
						   MemoryContext newcontext)
{
	/* Assert caller is doing things in a sane order */
	Assert(plansource->magic == CACHEDPLANSOURCE_MAGIC);
	Assert(plansource->is_complete);

	/* These seem worth real tests, though */
	if (plansource->is_saved)
		elog(ERROR, "cannot move a saved cached plan to another context");
	if (plansource->is_oneshot)
		elog(ERROR, "cannot move a one-shot cached plan to another context");

	/* OK, let the caller keep the plan where he wishes */
	MemoryContextSetParent(plansource->context, newcontext);

	/*
	 * The query_context needs no special handling, since it's a child of
	 * plansource->context.  But if there's a generic plan, it should be
	 * maintained as a sibling of plansource->context.
	 */
	if (plansource->gplan)
	{
		Assert(plansource->gplan->magic == CACHEDPLAN_MAGIC);
		MemoryContextSetParent(plansource->gplan->context, newcontext);
	}
}