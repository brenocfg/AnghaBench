#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ec_relids; int /*<<< orphan*/  ec_members; } ;
struct TYPE_8__ {int /*<<< orphan*/  eq_classes; } ;
struct TYPE_7__ {int /*<<< orphan*/  relids; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;
typedef  TYPE_3__ EquivalenceClass ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  bms_is_subset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * get_eclass_indexes_for_relids (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ ,int) ; 

bool
has_relevant_eclass_joinclause(PlannerInfo *root, RelOptInfo *rel1)
{
	Bitmapset  *matched_ecs;
	int			i;

	/* Examine only eclasses mentioning rel1 */
	matched_ecs = get_eclass_indexes_for_relids(root, rel1->relids);

	i = -1;
	while ((i = bms_next_member(matched_ecs, i)) >= 0)
	{
		EquivalenceClass *ec = (EquivalenceClass *) list_nth(root->eq_classes,
															 i);

		/*
		 * Won't generate joinclauses if single-member (this test covers the
		 * volatile case too)
		 */
		if (list_length(ec->ec_members) <= 1)
			continue;

		/*
		 * Per the comment in have_relevant_eclass_joinclause, it's sufficient
		 * to find an EC that mentions both this rel and some other rel.
		 */
		if (!bms_is_subset(ec->ec_relids, rel1->relids))
			return true;
	}

	return false;
}