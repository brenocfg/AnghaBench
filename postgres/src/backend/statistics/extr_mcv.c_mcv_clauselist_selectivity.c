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
struct TYPE_9__ {int nitems; TYPE_1__* items; } ;
struct TYPE_8__ {int /*<<< orphan*/  keys; int /*<<< orphan*/  statOid; } ;
struct TYPE_7__ {scalar_t__ frequency; scalar_t__ base_frequency; } ;
typedef  TYPE_2__ StatisticExtInfo ;
typedef  int /*<<< orphan*/  SpecialJoinInfo ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_3__ MCVList ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JoinType ;

/* Variables and functions */
 int* mcv_get_match_bitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 TYPE_3__* statext_mcv_load (int /*<<< orphan*/ ) ; 

Selectivity
mcv_clauselist_selectivity(PlannerInfo *root, StatisticExtInfo *stat,
						   List *clauses, int varRelid,
						   JoinType jointype, SpecialJoinInfo *sjinfo,
						   RelOptInfo *rel,
						   Selectivity *basesel, Selectivity *totalsel)
{
	int			i;
	MCVList    *mcv;
	Selectivity s = 0.0;

	/* match/mismatch bitmap for each MCV item */
	bool	   *matches = NULL;

	/* load the MCV list stored in the statistics object */
	mcv = statext_mcv_load(stat->statOid);

	/* build a match bitmap for the clauses */
	matches = mcv_get_match_bitmap(root, clauses, stat->keys, mcv, false);

	/* sum frequencies for all the matching MCV items */
	*basesel = 0.0;
	*totalsel = 0.0;
	for (i = 0; i < mcv->nitems; i++)
	{
		*totalsel += mcv->items[i].frequency;

		if (matches[i] != false)
		{
			/* XXX Shouldn't the basesel be outside the if condition? */
			*basesel += mcv->items[i].base_frequency;
			s += mcv->items[i].frequency;
		}
	}

	return s;
}