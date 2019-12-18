#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_7__ {scalar_t__ deltaLen; int /*<<< orphan*/  delta; } ;
struct TYPE_6__ {int pd_lower; int pd_upper; } ;
typedef  TYPE_1__* PageHeader ;
typedef  TYPE_2__ PageData ;
typedef  scalar_t__ Page ;
typedef  TYPE_3__ PGAlignedBlock ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ XLOG_DEBUG ; 
 int /*<<< orphan*/  applyPageRedo (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  computeRegionDelta (TYPE_2__*,scalar_t__,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void
computeDelta(PageData *pageData, Page curpage, Page targetpage)
{
	int			targetLower = ((PageHeader) targetpage)->pd_lower,
				targetUpper = ((PageHeader) targetpage)->pd_upper,
				curLower = ((PageHeader) curpage)->pd_lower,
				curUpper = ((PageHeader) curpage)->pd_upper;

	pageData->deltaLen = 0;

	/* Compute delta records for lower part of page ... */
	computeRegionDelta(pageData, curpage, targetpage,
					   0, targetLower,
					   0, curLower);
	/* ... and for upper part, ignoring what's between */
	computeRegionDelta(pageData, curpage, targetpage,
					   targetUpper, BLCKSZ,
					   curUpper, BLCKSZ);

	/*
	 * If xlog debug is enabled, then check produced delta.  Result of delta
	 * application to curpage should be equivalent to targetpage.
	 */
#ifdef WAL_DEBUG
	if (XLOG_DEBUG)
	{
		PGAlignedBlock tmp;

		memcpy(tmp.data, curpage, BLCKSZ);
		applyPageRedo(tmp.data, pageData->delta, pageData->deltaLen);
		if (memcmp(tmp.data, targetpage, targetLower) != 0 ||
			memcmp(tmp.data + targetUpper, targetpage + targetUpper,
				   BLCKSZ - targetUpper) != 0)
			elog(ERROR, "result of generic xlog apply does not match");
	}
#endif
}