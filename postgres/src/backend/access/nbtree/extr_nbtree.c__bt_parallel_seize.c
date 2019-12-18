#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ btps_pageStatus; scalar_t__ btps_arrayKeyCount; int /*<<< orphan*/  btps_cv; int /*<<< orphan*/  btps_mutex; int /*<<< orphan*/  btps_scanPage; } ;
struct TYPE_8__ {scalar_t__ arrayKeyCount; } ;
struct TYPE_7__ {TYPE_1__* parallel_scan; int /*<<< orphan*/  opaque; } ;
struct TYPE_6__ {int /*<<< orphan*/  ps_offset; } ;
typedef  TYPE_1__* ParallelIndexScanDesc ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  TYPE_3__* BTScanOpaque ;
typedef  TYPE_4__* BTParallelScanDesc ;
typedef  scalar_t__ BTPS_State ;

/* Variables and functions */
 scalar_t__ BTPARALLEL_ADVANCING ; 
 scalar_t__ BTPARALLEL_DONE ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/  ConditionVariableSleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ OffsetToPointer (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_NONE ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAIT_EVENT_BTREE_PAGE ; 

bool
_bt_parallel_seize(IndexScanDesc scan, BlockNumber *pageno)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	BTPS_State	pageStatus;
	bool		exit_loop = false;
	bool		status = true;
	ParallelIndexScanDesc parallel_scan = scan->parallel_scan;
	BTParallelScanDesc btscan;

	*pageno = P_NONE;

	btscan = (BTParallelScanDesc) OffsetToPointer((void *) parallel_scan,
												  parallel_scan->ps_offset);

	while (1)
	{
		SpinLockAcquire(&btscan->btps_mutex);
		pageStatus = btscan->btps_pageStatus;

		if (so->arrayKeyCount < btscan->btps_arrayKeyCount)
		{
			/* Parallel scan has already advanced to a new set of scankeys. */
			status = false;
		}
		else if (pageStatus == BTPARALLEL_DONE)
		{
			/*
			 * We're done with this set of scankeys.  This may be the end, or
			 * there could be more sets to try.
			 */
			status = false;
		}
		else if (pageStatus != BTPARALLEL_ADVANCING)
		{
			/*
			 * We have successfully seized control of the scan for the purpose
			 * of advancing it to a new page!
			 */
			btscan->btps_pageStatus = BTPARALLEL_ADVANCING;
			*pageno = btscan->btps_scanPage;
			exit_loop = true;
		}
		SpinLockRelease(&btscan->btps_mutex);
		if (exit_loop || !status)
			break;
		ConditionVariableSleep(&btscan->btps_cv, WAIT_EVENT_BTREE_PAGE);
	}
	ConditionVariableCancelSleep();

	return status;
}