#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  statsTuple; } ;
typedef  TYPE_1__ VariableStatData ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  BoolGetDatum (int) ; 
 int /*<<< orphan*/  BooleanEqualOperator ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseVariableStats (TYPE_1__) ; 
 int /*<<< orphan*/  examine_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 double var_eq_const (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

Selectivity
boolvarsel(PlannerInfo *root, Node *arg, int varRelid)
{
	VariableStatData vardata;
	double		selec;

	examine_variable(root, arg, varRelid, &vardata);
	if (HeapTupleIsValid(vardata.statsTuple))
	{
		/*
		 * A boolean variable V is equivalent to the clause V = 't', so we
		 * compute the selectivity as if that is what we have.
		 */
		selec = var_eq_const(&vardata, BooleanEqualOperator,
							 BoolGetDatum(true), false, true, false);
	}
	else
	{
		/* Otherwise, the default estimate is 0.5 */
		selec = 0.5;
	}
	ReleaseVariableStats(vardata);
	return selec;
}