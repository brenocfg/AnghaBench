#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ssup; } ;
struct TYPE_5__ {int ssup_nulls_first; int /*<<< orphan*/  ssup_collation; int /*<<< orphan*/  ssup_cxt; } ;
typedef  TYPE_1__* SortSupport ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__* MultiSortSupport ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  PrepareSortSupportFromOrderingOp (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
multi_sort_add_dimension(MultiSortSupport mss, int sortdim,
						 Oid oper, Oid collation)
{
	SortSupport ssup = &mss->ssup[sortdim];

	ssup->ssup_cxt = CurrentMemoryContext;
	ssup->ssup_collation = collation;
	ssup->ssup_nulls_first = false;

	PrepareSortSupportFromOrderingOp(oper, ssup);
}