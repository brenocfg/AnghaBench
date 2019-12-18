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
struct TYPE_4__ {scalar_t__ rtekind; scalar_t__ statlist; } ;
typedef  int /*<<< orphan*/  SpecialJoinInfo ;
typedef  double Selectivity ;
typedef  TYPE_1__ RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JoinType ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 scalar_t__ NIL ; 
 scalar_t__ RTE_RELATION ; 
 double clauselist_selectivity_simple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* find_single_rel_for_clauses (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double statext_clauselist_selectivity (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 

Selectivity
clauselist_selectivity(PlannerInfo *root,
					   List *clauses,
					   int varRelid,
					   JoinType jointype,
					   SpecialJoinInfo *sjinfo)
{
	Selectivity s1 = 1.0;
	RelOptInfo *rel;
	Bitmapset  *estimatedclauses = NULL;

	/*
	 * Determine if these clauses reference a single relation.  If so, and if
	 * it has extended statistics, try to apply those.
	 */
	rel = find_single_rel_for_clauses(root, clauses);
	if (rel && rel->rtekind == RTE_RELATION && rel->statlist != NIL)
	{
		/*
		 * Estimate as many clauses as possible using extended statistics.
		 *
		 * 'estimatedclauses' tracks the 0-based list position index of
		 * clauses that we've estimated using extended statistics, and that
		 * should be ignored.
		 */
		s1 *= statext_clauselist_selectivity(root, clauses, varRelid,
											 jointype, sjinfo, rel,
											 &estimatedclauses);
	}

	/*
	 * Apply normal selectivity estimates for the remaining clauses, passing
	 * 'estimatedclauses' so that it skips already estimated ones.
	 */
	return s1 * clauselist_selectivity_simple(root, clauses, varRelid,
											  jointype, sjinfo,
											  estimatedclauses);
}