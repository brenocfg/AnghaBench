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
struct TYPE_6__ {int /*<<< orphan*/  lateral_referencers; int /*<<< orphan*/  relid; } ;
struct TYPE_5__ {int /*<<< orphan*/  clause_relids; int /*<<< orphan*/  nullable_relids; int /*<<< orphan*/  outer_relids; } ;
typedef  TYPE_1__ RestrictInfo ;
typedef  TYPE_2__ RelOptInfo ;

/* Variables and functions */
 scalar_t__ bms_is_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bms_overlap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
join_clause_is_movable_to(RestrictInfo *rinfo, RelOptInfo *baserel)
{
	/* Clause must physically reference target rel */
	if (!bms_is_member(baserel->relid, rinfo->clause_relids))
		return false;

	/* Cannot move an outer-join clause into the join's outer side */
	if (bms_is_member(baserel->relid, rinfo->outer_relids))
		return false;

	/* Target rel must not be nullable below the clause */
	if (bms_is_member(baserel->relid, rinfo->nullable_relids))
		return false;

	/* Clause must not use any rels with LATERAL references to this rel */
	if (bms_overlap(baserel->lateral_referencers, rinfo->clause_relids))
		return false;

	return true;
}