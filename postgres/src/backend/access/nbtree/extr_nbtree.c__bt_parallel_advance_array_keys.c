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
struct TYPE_9__ {scalar_t__ btps_pageStatus; int /*<<< orphan*/  btps_mutex; int /*<<< orphan*/  btps_arrayKeyCount; int /*<<< orphan*/  btps_scanPage; } ;
struct TYPE_8__ {int /*<<< orphan*/  arrayKeyCount; } ;
struct TYPE_7__ {TYPE_1__* parallel_scan; int /*<<< orphan*/  opaque; } ;
struct TYPE_6__ {int /*<<< orphan*/  ps_offset; } ;
typedef  TYPE_1__* ParallelIndexScanDesc ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__* BTScanOpaque ;
typedef  TYPE_4__* BTParallelScanDesc ;

/* Variables and functions */
 scalar_t__ BTPARALLEL_DONE ; 
 scalar_t__ BTPARALLEL_NOT_INITIALIZED ; 
 int /*<<< orphan*/  InvalidBlockNumber ; 
 scalar_t__ OffsetToPointer (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 

void
_bt_parallel_advance_array_keys(IndexScanDesc scan)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	ParallelIndexScanDesc parallel_scan = scan->parallel_scan;
	BTParallelScanDesc btscan;

	btscan = (BTParallelScanDesc) OffsetToPointer((void *) parallel_scan,
												  parallel_scan->ps_offset);

	so->arrayKeyCount++;
	SpinLockAcquire(&btscan->btps_mutex);
	if (btscan->btps_pageStatus == BTPARALLEL_DONE)
	{
		btscan->btps_scanPage = InvalidBlockNumber;
		btscan->btps_pageStatus = BTPARALLEL_NOT_INITIALIZED;
		btscan->btps_arrayKeyCount++;
	}
	SpinLockRelease(&btscan->btps_mutex);
}