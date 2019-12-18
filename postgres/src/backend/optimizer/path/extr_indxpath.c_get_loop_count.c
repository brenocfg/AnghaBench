#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int simple_rel_array_size; TYPE_1__** simple_rel_array; } ;
struct TYPE_6__ {int relid; scalar_t__ rows; } ;
typedef  int /*<<< orphan*/ * Relids ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ IS_DUMMY_REL (TYPE_1__*) ; 
 double adjust_rowcount_for_semijoins (TYPE_2__*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int bms_next_member (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static double
get_loop_count(PlannerInfo *root, Index cur_relid, Relids outer_relids)
{
	double		result;
	int			outer_relid;

	/* For a non-parameterized path, just return 1.0 quickly */
	if (outer_relids == NULL)
		return 1.0;

	result = 0.0;
	outer_relid = -1;
	while ((outer_relid = bms_next_member(outer_relids, outer_relid)) >= 0)
	{
		RelOptInfo *outer_rel;
		double		rowcount;

		/* Paranoia: ignore bogus relid indexes */
		if (outer_relid >= root->simple_rel_array_size)
			continue;
		outer_rel = root->simple_rel_array[outer_relid];
		if (outer_rel == NULL)
			continue;
		Assert(outer_rel->relid == outer_relid);	/* sanity check on array */

		/* Other relation could be proven empty, if so ignore */
		if (IS_DUMMY_REL(outer_rel))
			continue;

		/* Otherwise, rel's rows estimate should be valid by now */
		Assert(outer_rel->rows > 0);

		/* Check to see if rel is on the inside of any semijoins */
		rowcount = adjust_rowcount_for_semijoins(root,
												 cur_relid,
												 outer_relid,
												 outer_rel->rows);

		/* Remember smallest row count estimate among the outer rels */
		if (result == 0.0 || result > rowcount)
			result = rowcount;
	}
	/* Return 1.0 if we found no valid relations (shouldn't happen) */
	return (result > 0.0) ? result : 1.0;
}