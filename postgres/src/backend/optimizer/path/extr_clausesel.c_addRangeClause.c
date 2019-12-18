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
struct TYPE_3__ {int have_lobound; scalar_t__ lobound; int have_hibound; scalar_t__ hibound; struct TYPE_3__* next; int /*<<< orphan*/ * var; } ;
typedef  scalar_t__ Selectivity ;
typedef  TYPE_1__ RangeQueryClause ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_leftop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_rightop (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
addRangeClause(RangeQueryClause **rqlist, Node *clause,
			   bool varonleft, bool isLTsel, Selectivity s2)
{
	RangeQueryClause *rqelem;
	Node	   *var;
	bool		is_lobound;

	if (varonleft)
	{
		var = get_leftop((Expr *) clause);
		is_lobound = !isLTsel;	/* x < something is high bound */
	}
	else
	{
		var = get_rightop((Expr *) clause);
		is_lobound = isLTsel;	/* something < x is low bound */
	}

	for (rqelem = *rqlist; rqelem; rqelem = rqelem->next)
	{
		/*
		 * We use full equal() here because the "var" might be a function of
		 * one or more attributes of the same relation...
		 */
		if (!equal(var, rqelem->var))
			continue;
		/* Found the right group to put this clause in */
		if (is_lobound)
		{
			if (!rqelem->have_lobound)
			{
				rqelem->have_lobound = true;
				rqelem->lobound = s2;
			}
			else
			{

				/*------
				 * We have found two similar clauses, such as
				 * x < y AND x <= z.
				 * Keep only the more restrictive one.
				 *------
				 */
				if (rqelem->lobound > s2)
					rqelem->lobound = s2;
			}
		}
		else
		{
			if (!rqelem->have_hibound)
			{
				rqelem->have_hibound = true;
				rqelem->hibound = s2;
			}
			else
			{

				/*------
				 * We have found two similar clauses, such as
				 * x > y AND x >= z.
				 * Keep only the more restrictive one.
				 *------
				 */
				if (rqelem->hibound > s2)
					rqelem->hibound = s2;
			}
		}
		return;
	}

	/* No matching var found, so make a new clause-pair data structure */
	rqelem = (RangeQueryClause *) palloc(sizeof(RangeQueryClause));
	rqelem->var = var;
	if (is_lobound)
	{
		rqelem->have_lobound = true;
		rqelem->have_hibound = false;
		rqelem->lobound = s2;
	}
	else
	{
		rqelem->have_lobound = false;
		rqelem->have_hibound = true;
		rqelem->hibound = s2;
	}
	rqelem->next = *rqlist;
	*rqlist = rqelem;
}