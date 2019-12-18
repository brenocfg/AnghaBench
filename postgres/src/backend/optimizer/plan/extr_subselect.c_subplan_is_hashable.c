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
struct TYPE_3__ {double plan_rows; int /*<<< orphan*/  plan_width; } ;
typedef  TYPE_1__ Plan ;

/* Variables and functions */
 double MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeofHeapTupleHeader ; 
 long work_mem ; 

__attribute__((used)) static bool
subplan_is_hashable(Plan *plan)
{
	double		subquery_size;

	/*
	 * The estimated size of the subquery result must fit in work_mem. (Note:
	 * we use heap tuple overhead here even though the tuples will actually be
	 * stored as MinimalTuples; this provides some fudge factor for hashtable
	 * overhead.)
	 */
	subquery_size = plan->plan_rows *
		(MAXALIGN(plan->plan_width) + MAXALIGN(SizeofHeapTupleHeader));
	if (subquery_size > work_mem * 1024L)
		return false;

	return true;
}