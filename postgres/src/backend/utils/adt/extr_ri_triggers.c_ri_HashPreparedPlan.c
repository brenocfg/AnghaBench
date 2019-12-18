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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ri_InitHashTables () ; 
 int /*<<< orphan*/  ri_query_cache ; 

__attribute__((used)) static void
ri_HashPreparedPlan(RI_QueryKey *key, SPIPlanPtr plan)
{
	RI_QueryHashEntry *entry;
	bool		found;

	/*
	 * On the first call initialize the hashtable
	 */
	if (!ri_query_cache)
		ri_InitHashTables();

	/*
	 * Add the new plan.  We might be overwriting an entry previously found
	 * invalid by ri_FetchPreparedPlan.
	 */
	entry = (RI_QueryHashEntry *) hash_search(ri_query_cache,
											  (void *) key,
											  HASH_ENTER, &found);
	Assert(!found || entry->plan == NULL);
	entry->plan = plan;
}