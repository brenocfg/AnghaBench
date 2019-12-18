#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int indexcol; TYPE_2__* index; } ;
typedef  TYPE_1__ ec_member_matches_arg ;
struct TYPE_8__ {int /*<<< orphan*/  lateral_referencers; int /*<<< orphan*/  has_eclass_joins; } ;
struct TYPE_7__ {int nkeycolumns; TYPE_5__* rel; } ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ IndexOptInfo ;
typedef  int /*<<< orphan*/  IndexClauseSet ;

/* Variables and functions */
 int /*<<< orphan*/  ec_member_matches_indexcol ; 
 int /*<<< orphan*/ * generate_implied_equalities_for_column (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_clauses_to_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
match_eclass_clauses_to_index(PlannerInfo *root, IndexOptInfo *index,
							  IndexClauseSet *clauseset)
{
	int			indexcol;

	/* No work if rel is not in any such ECs */
	if (!index->rel->has_eclass_joins)
		return;

	for (indexcol = 0; indexcol < index->nkeycolumns; indexcol++)
	{
		ec_member_matches_arg arg;
		List	   *clauses;

		/* Generate clauses, skipping any that join to lateral_referencers */
		arg.index = index;
		arg.indexcol = indexcol;
		clauses = generate_implied_equalities_for_column(root,
														 index->rel,
														 ec_member_matches_indexcol,
														 (void *) &arg,
														 index->rel->lateral_referencers);

		/*
		 * We have to check whether the results actually do match the index,
		 * since for non-btree indexes the EC's equality operators might not
		 * be in the index opclass (cf ec_member_matches_indexcol).
		 */
		match_clauses_to_index(root, clauses, index, clauseset);
	}
}