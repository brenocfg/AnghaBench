#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int StrategyNumber ;
typedef  int /*<<< orphan*/  NDBOX ;

/* Variables and functions */
#define  RTContainedByStrategyNumber 133 
#define  RTContainsStrategyNumber 132 
#define  RTOldContainedByStrategyNumber 131 
#define  RTOldContainsStrategyNumber 130 
#define  RTOverlapStrategyNumber 129 
#define  RTSameStrategyNumber 128 
 int /*<<< orphan*/  cube_cmp_v0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cube_contains_v0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cube_overlap_v0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
g_cube_leaf_consistent(NDBOX *key,
					   NDBOX *query,
					   StrategyNumber strategy)
{
	bool		retval;

	switch (strategy)
	{
		case RTOverlapStrategyNumber:
			retval = cube_overlap_v0(key, query);
			break;
		case RTSameStrategyNumber:
			retval = (cube_cmp_v0(key, query) == 0);
			break;
		case RTContainsStrategyNumber:
		case RTOldContainsStrategyNumber:
			retval = cube_contains_v0(key, query);
			break;
		case RTContainedByStrategyNumber:
		case RTOldContainedByStrategyNumber:
			retval = cube_contains_v0(query, key);
			break;
		default:
			retval = false;
	}
	return retval;
}