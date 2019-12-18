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
struct TYPE_6__ {scalar_t__ magic; } ;
struct TYPE_5__ {TYPE_2__* gplan; } ;
typedef  TYPE_1__ CachedPlanSource ;
typedef  TYPE_2__ CachedPlan ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHEDPLAN_MAGIC ; 
 int /*<<< orphan*/  ReleaseCachedPlan (TYPE_2__*,int) ; 

__attribute__((used)) static void
ReleaseGenericPlan(CachedPlanSource *plansource)
{
	/* Be paranoid about the possibility that ReleaseCachedPlan fails */
	if (plansource->gplan)
	{
		CachedPlan *plan = plansource->gplan;

		Assert(plan->magic == CACHEDPLAN_MAGIC);
		plansource->gplan = NULL;
		ReleaseCachedPlan(plan, false);
	}
}