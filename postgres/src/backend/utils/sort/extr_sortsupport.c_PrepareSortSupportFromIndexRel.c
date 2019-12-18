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
typedef  scalar_t__ int16 ;
struct TYPE_9__ {TYPE_1__* rd_rel; int /*<<< orphan*/ * rd_opcintype; int /*<<< orphan*/ * rd_opfamily; } ;
struct TYPE_8__ {int ssup_attno; int ssup_reverse; int /*<<< orphan*/ * comparator; } ;
struct TYPE_7__ {scalar_t__ relam; } ;
typedef  TYPE_2__* SortSupport ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ BTGreaterStrategyNumber ; 
 scalar_t__ BTLessStrategyNumber ; 
 scalar_t__ BTREE_AM_OID ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FinishSortSupportFunction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
PrepareSortSupportFromIndexRel(Relation indexRel, int16 strategy,
							   SortSupport ssup)
{
	Oid			opfamily = indexRel->rd_opfamily[ssup->ssup_attno - 1];
	Oid			opcintype = indexRel->rd_opcintype[ssup->ssup_attno - 1];

	Assert(ssup->comparator == NULL);

	if (indexRel->rd_rel->relam != BTREE_AM_OID)
		elog(ERROR, "unexpected non-btree AM: %u", indexRel->rd_rel->relam);
	if (strategy != BTGreaterStrategyNumber &&
		strategy != BTLessStrategyNumber)
		elog(ERROR, "unexpected sort support strategy: %d", strategy);
	ssup->ssup_reverse = (strategy == BTGreaterStrategyNumber);

	FinishSortSupportFunction(opfamily, opcintype, ssup);
}