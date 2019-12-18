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
struct TYPE_3__ {double tuples; double rows; int /*<<< orphan*/  relid; int /*<<< orphan*/  baserestrictinfo; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  JOIN_INNER ; 
 double clamp_row_est (double) ; 
 double clauselist_selectivity (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_concat_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

double
get_parameterized_baserel_size(PlannerInfo *root, RelOptInfo *rel,
							   List *param_clauses)
{
	List	   *allclauses;
	double		nrows;

	/*
	 * Estimate the number of rows returned by the parameterized scan, knowing
	 * that it will apply all the extra join clauses as well as the rel's own
	 * restriction clauses.  Note that we force the clauses to be treated as
	 * non-join clauses during selectivity estimation.
	 */
	allclauses = list_concat_copy(param_clauses, rel->baserestrictinfo);
	nrows = rel->tuples *
		clauselist_selectivity(root,
							   allclauses,
							   rel->relid,	/* do not use 0! */
							   JOIN_INNER,
							   NULL);
	nrows = clamp_row_est(nrows);
	/* For safety, make sure result is not more than the base estimate */
	if (nrows > rel->rows)
		nrows = rel->rows;
	return nrows;
}