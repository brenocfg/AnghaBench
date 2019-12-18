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
struct TYPE_5__ {scalar_t__ resultDesc; } ;
struct TYPE_4__ {scalar_t__ magic; int /*<<< orphan*/  plancache_list; } ;
typedef  TYPE_1__* SPIPlanPtr ;
typedef  TYPE_2__ CachedPlanSource ;

/* Variables and functions */
 scalar_t__ SPI_ERROR_ARGUMENT ; 
 scalar_t__ SPI_result ; 
 scalar_t__ _SPI_PLAN_MAGIC ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 

bool
SPI_is_cursor_plan(SPIPlanPtr plan)
{
	CachedPlanSource *plansource;

	if (plan == NULL || plan->magic != _SPI_PLAN_MAGIC)
	{
		SPI_result = SPI_ERROR_ARGUMENT;
		return false;
	}

	if (list_length(plan->plancache_list) != 1)
	{
		SPI_result = 0;
		return false;			/* not exactly 1 pre-rewrite command */
	}
	plansource = (CachedPlanSource *) linitial(plan->plancache_list);

	/*
	 * We used to force revalidation of the cached plan here, but that seems
	 * unnecessary: invalidation could mean a change in the rowtype of the
	 * tuples returned by a plan, but not whether it returns tuples at all.
	 */
	SPI_result = 0;

	/* Does it return tuples? */
	if (plansource->resultDesc)
		return true;

	return false;
}