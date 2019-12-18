#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ relid; double tuples; int /*<<< orphan*/  baserestrictinfo; int /*<<< orphan*/  baserestrictcost; int /*<<< orphan*/  rows; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  JOIN_INNER ; 
 int /*<<< orphan*/  clamp_row_est (double) ; 
 double clauselist_selectivity (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cost_qual_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rel_width (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
set_baserel_size_estimates(PlannerInfo *root, RelOptInfo *rel)
{
	double		nrows;

	/* Should only be applied to base relations */
	Assert(rel->relid > 0);

	nrows = rel->tuples *
		clauselist_selectivity(root,
							   rel->baserestrictinfo,
							   0,
							   JOIN_INNER,
							   NULL);

	rel->rows = clamp_row_est(nrows);

	cost_qual_eval(&rel->baserestrictcost, rel->baserestrictinfo, root);

	set_rel_width(root, rel);
}