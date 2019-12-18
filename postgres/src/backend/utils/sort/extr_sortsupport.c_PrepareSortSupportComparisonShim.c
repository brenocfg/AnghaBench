#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* args; } ;
struct TYPE_8__ {TYPE_5__ fcinfo; int /*<<< orphan*/  flinfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  comparator; TYPE_3__* ssup_extra; int /*<<< orphan*/  ssup_collation; int /*<<< orphan*/  ssup_cxt; } ;
struct TYPE_6__ {int isnull; } ;
typedef  TYPE_2__* SortSupport ;
typedef  TYPE_3__ SortShimExtra ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InitFunctionCallInfoData (TYPE_5__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SizeForSortShimExtra (int) ; 
 int /*<<< orphan*/  comparison_shim ; 
 int /*<<< orphan*/  fmgr_info_cxt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
PrepareSortSupportComparisonShim(Oid cmpFunc, SortSupport ssup)
{
	SortShimExtra *extra;

	extra = (SortShimExtra *) MemoryContextAlloc(ssup->ssup_cxt,
												 SizeForSortShimExtra(2));

	/* Lookup the comparison function */
	fmgr_info_cxt(cmpFunc, &extra->flinfo, ssup->ssup_cxt);

	/* We can initialize the callinfo just once and re-use it */
	InitFunctionCallInfoData(extra->fcinfo, &extra->flinfo, 2,
							 ssup->ssup_collation, NULL, NULL);
	extra->fcinfo.args[0].isnull = false;
	extra->fcinfo.args[1].isnull = false;

	ssup->ssup_extra = extra;
	ssup->comparator = comparison_shim;
}