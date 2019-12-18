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
struct TYPE_3__ {int simple_rel_array_size; int /*<<< orphan*/ ** simple_rel_array; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_1__ PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

RelOptInfo *
find_base_rel(PlannerInfo *root, int relid)
{
	RelOptInfo *rel;

	Assert(relid > 0);

	if (relid < root->simple_rel_array_size)
	{
		rel = root->simple_rel_array[relid];
		if (rel)
			return rel;
	}

	elog(ERROR, "no relation entry for relid %d", relid);

	return NULL;				/* keep compiler quiet */
}