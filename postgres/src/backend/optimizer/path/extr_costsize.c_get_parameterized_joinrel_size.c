#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rows; int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {double rows; } ;
typedef  int /*<<< orphan*/  SpecialJoinInfo ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_2__ Path ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 double calc_joinrel_size_estimate (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

double
get_parameterized_joinrel_size(PlannerInfo *root, RelOptInfo *rel,
							   Path *outer_path,
							   Path *inner_path,
							   SpecialJoinInfo *sjinfo,
							   List *restrict_clauses)
{
	double		nrows;

	/*
	 * Estimate the number of rows returned by the parameterized join as the
	 * sizes of the input paths times the selectivity of the clauses that have
	 * ended up at this join node.
	 *
	 * As with set_joinrel_size_estimates, the rowcount estimate could depend
	 * on the pair of input paths provided, though ideally we'd get the same
	 * estimate for any pair with the same parameterization.
	 */
	nrows = calc_joinrel_size_estimate(root,
									   rel,
									   outer_path->parent,
									   inner_path->parent,
									   outer_path->rows,
									   inner_path->rows,
									   sjinfo,
									   restrict_clauses);
	/* For safety, make sure result is not more than the base estimate */
	if (nrows > rel->rows)
		nrows = rel->rows;
	return nrows;
}