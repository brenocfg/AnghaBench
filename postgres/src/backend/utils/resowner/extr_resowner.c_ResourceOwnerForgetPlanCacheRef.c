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
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  planrefarr; } ;
typedef  TYPE_1__* ResourceOwner ;
typedef  int /*<<< orphan*/  CachedPlan ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResourceArrayRemove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ResourceOwnerForgetPlanCacheRef(ResourceOwner owner, CachedPlan *plan)
{
	if (!ResourceArrayRemove(&(owner->planrefarr), PointerGetDatum(plan)))
		elog(ERROR, "plancache reference %p is not owned by resource owner %s",
			 plan, owner->name);
}