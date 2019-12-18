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
struct TYPE_6__ {scalar_t__ query_pathkeys; } ;
struct TYPE_5__ {scalar_t__ joininfo; scalar_t__ has_eclass_joins; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;

/* Variables and functions */
 scalar_t__ NIL ; 

bool
has_useful_pathkeys(PlannerInfo *root, RelOptInfo *rel)
{
	if (rel->joininfo != NIL || rel->has_eclass_joins)
		return true;			/* might be able to use pathkeys for merging */
	if (root->query_pathkeys != NIL)
		return true;			/* might be able to use them for ordering */
	return false;				/* definitely useless */
}