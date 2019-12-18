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
typedef  scalar_t__ int16 ;
struct TYPE_4__ {int ssup_reverse; int /*<<< orphan*/ * comparator; } ;
typedef  TYPE_1__* SortSupport ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ BTGreaterStrategyNumber ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FinishSortSupportFunction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ordering_op_properties (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 

void
PrepareSortSupportFromOrderingOp(Oid orderingOp, SortSupport ssup)
{
	Oid			opfamily;
	Oid			opcintype;
	int16		strategy;

	Assert(ssup->comparator == NULL);

	/* Find the operator in pg_amop */
	if (!get_ordering_op_properties(orderingOp, &opfamily, &opcintype,
									&strategy))
		elog(ERROR, "operator %u is not a valid ordering operator",
			 orderingOp);
	ssup->ssup_reverse = (strategy == BTGreaterStrategyNumber);

	FinishSortSupportFunction(opfamily, opcintype, ssup);
}