#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * plan; } ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  int /*<<< orphan*/  RI_QueryKey ;
typedef  TYPE_1__ RI_QueryHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  SPI_freeplan (int /*<<< orphan*/ *) ; 
 scalar_t__ SPI_plan_is_valid (int /*<<< orphan*/ *) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ri_InitHashTables () ; 
 int /*<<< orphan*/  ri_query_cache ; 

__attribute__((used)) static SPIPlanPtr
ri_FetchPreparedPlan(RI_QueryKey *key)
{
	RI_QueryHashEntry *entry;
	SPIPlanPtr	plan;

	/*
	 * On the first call initialize the hashtable
	 */
	if (!ri_query_cache)
		ri_InitHashTables();

	/*
	 * Lookup for the key
	 */
	entry = (RI_QueryHashEntry *) hash_search(ri_query_cache,
											  (void *) key,
											  HASH_FIND, NULL);
	if (entry == NULL)
		return NULL;

	/*
	 * Check whether the plan is still valid.  If it isn't, we don't want to
	 * simply rely on plancache.c to regenerate it; rather we should start
	 * from scratch and rebuild the query text too.  This is to cover cases
	 * such as table/column renames.  We depend on the plancache machinery to
	 * detect possible invalidations, though.
	 *
	 * CAUTION: this check is only trustworthy if the caller has already
	 * locked both FK and PK rels.
	 */
	plan = entry->plan;
	if (plan && SPI_plan_is_valid(plan))
		return plan;

	/*
	 * Otherwise we might as well flush the cached plan now, to free a little
	 * memory space before we make a new one.
	 */
	entry->plan = NULL;
	if (plan)
		SPI_freeplan(plan);

	return NULL;
}